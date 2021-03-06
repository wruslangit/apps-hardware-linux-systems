//============================================================================
// Name        : using-gcc93-boost.cpp
// Author      : wruslan
// Date		   : Sun Mar 15 15:57:27 +08 2020
// Version     : 1.0
// Copyright   : Bismillah Hirrahma Nirrahim.
// Description : C++, Ansi-style
//============================================================================
/*
SUMMARY

This C++ code is a success demonstration of combining the following techniques:

	(1) Uniform random integers and uniform random doubles
	(2) Thread-safe and lock-free dynamic queue (FIFO) using the Boost library
	(3) Multi-threading in MPMC mode (multi-producer multi-consumer threads)
	(4) Real-time multi-threading using the Preempt-RT POSIX system environment.

BRIEF DESCRIPTION

 * (1) Generate uniform long integers in the range (-x1, +x2). The generator
 * 		function was tested for uniform randomness quality. The same was
 * 		done for uniform random doubles. Excellent.
 *
 * (2) Create a dynamic queue using the boost library. A queue is a FIFO
 * 		(First-In First-Out) data structure. A dynamic queue automatically
 * 		expands and shrinks to cater for running operations.
 *
 * (3) Create two(2) producer pthreads preempt-RT to push random integers into
 * 		the dynamic queue. The number of integers to put into the dynamic queue
 * 		may be 100 times larger than the initial size of the queue. Excellent.
 *
 * (4) Create two(2) consumer pthreads preempt-RT to pop (process) queue data.
 * 		The process is simple, i.e. to sum the integers in MPMC mode into a
 * 		common sum atomic shared variable. MPMC is Multi-Producer Multi Consumer
 * 		threading protocol. To ensure correctness of the sum, we populated the
 * 		same random integers into a separate second queue as a record queue.
 * 		This second queue is maintained (elements added only) and used to run
 * 		a serial sum. This sum value is in agreement with the sum obtained by
 * 		the parallel consumer threads. Excellent.
 *
 * (5) The four(4) threads, comprising 2 producer and 2 consumer threads, run
 * 		simultaneously. This is MPMC. Time tracing in nanosecond time-stamps
 * 		was built into the code to analyze the MPMC parallel running threads.
 * 		To get full time-stamp details displayed, go to the source code and
 * 		un-comment the printf() statements accordingly. Very verbose. It is
 * 		recommended that this is done a little bit at a time.
 *
 * (6) All threads are POSIX or pthreads. Normal pthreads do not run in real-time
 * 		mode. This code is made to run real-time pthreads using the preemptive
 * 		real-time environment provided by the operating system.
 *
 * (7) The operating system: uname -a
 * 		Hardware machine: sgi-ub1604-lts-64b
 * 		Linux version: 4.4.208-rt191 #1 SMP PREEMPT RT (Real-Time extension)
 * 		Build: Mon Jan 20 21:53:39 +08 2020 x86_64 x86_64 x86_64 GNU/Linux
 *
 * (8) Linux Distribution: lsb_release -a
 * 		LSB Version:	core-9.20160110ubuntu0.2-amd64: etc.
 * 		Distributor ID:	Ubuntu
 * 		Description:	Ubuntu 16.04.6 LTS
 * 		Release:	16.04
 * 		Codename:	xenial
 *
 * Wassalam.
 * WRY
 *
//============================================================================

Examples:
Reference: https://theboostcpplibraries.com/boost.lockfree
Reference: https://theboostcpplibraries.com/boost.atomic

	// FIXED QUEUE
	std::atomic<long int> queuesize{20};
	boost::lockfree::queue<long int, fixed_sized<true>> the_queue{queuesize};
	// DYNAMIC QUEUE
	boost::lockfree::queue<long int> the_queue{queuesize};
	std::atomic<long int> queuesum{0};

	// FIXED STACK
	std::atomic<long int> stacksize{20};
	boost::lockfree::stack<long int, fixed_sized<true>> the_stack{stacksize};
	// DYNAMIC STACK
	boost::lockfree::stack<long int> the_stack{stacksize};
	std::atomic<long int> stacksum{0};

===========================================================
	wruslan@sgi-ub1604-lts-64b:~/apps2/eclipse-wks2/using-gcc93-boost/Debug$ gcc -v
	Using built-in specs.
	COLLECT_GCC=gcc
	COLLECT_LTO_WRAPPER=/usr/local/libexec/gcc/x86_64-pc-linux-gnu/9.3.0/lto-wrapper
	Target: x86_64-pc-linux-gnu
	Configured with: ./configure
	Thread model: posix
	gcc version 9.3.0 (GCC)

	wruslan@sgi-ub1604-lts-64b:~/apps2/eclipse-wks2/using-gcc93-boost/Debug$ g++ -v
	Using built-in specs.
	COLLECT_GCC=g++
	COLLECT_LTO_WRAPPER=/usr/local/libexec/gcc/x86_64-pc-linux-gnu/9.3.0/lto-wrapper
	Target: x86_64-pc-linux-gnu
	Configured with: ./configure
	Thread model: posix
	gcc version 9.3.0 (GCC)

===========================================================
	Eclipse IDE for Scientific Computing
	Version: 2019-12 (4.14.0)
	Build id: 20191212-1212
	OS: Linux, v.4.4.208-rt191, x86_64 / gtk 3.18.9, WebKit 2.20.5
	Java version: 13.0.2

	COMPILER and LINKER SETTINGS in Eclipse IDE:

	(1) Project -> Properties -> C/C++ Build -> Settings -> GCC C++ Compiler
		-> Dialect -> Language standard -> ISO C++11 (-std=c++0x)
		-> Apply and Close

	(2) Project -> Properties -> C/C++ Build -> Settings -> GCC C++ Compiler
		-> Includes -> include paths (-l) -> + (Add..) -> File system...
		-> /home/wruslan/apps3/boost -> OK
		-> Apply and Close

	(3) Project -> Properties -> C/C++ Build -> Settings -> GCC C++ Linker
		-> Libraries -> Libraries (-l)
		-> + (Add..) -> pthread -> OK
		-> + (Add..) -> rt -> OK
		-> + (Add..) -> m -> OK
		-> Apply and Close

===========================================================
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>     // For srand() and rand(), scanf(),
using namespace std;

#include "dtstamp/dtstamp.hpp"
#include "random_int_dbl/random_int_dbl.hpp"
#include "random_int_dyn_queue/random_int_dyn_queue.hpp"

// ========================================================
int main(int argc, char* argv[]) {
// ========================================================
	WRY_starting_salutation();

printf("=============================================================\n");
	start_timer(1);
	DTStamp();
	printf("CHECK 1: Check environment, date, time and clock.\n");
	display_date_only();
	current_working_directory();
	DTStamp(); printf("Current runfile  : %s \n", argv[0]);
	display_resolution_date_time();
	stop_timer(1);

printf("=============================================================\n");
	start_timer(2);
	DTStamp();
	printf("CHECK 2.1: Display generation of uniform random integers.\n");
	long int int_count = 10;		// Number of randoms to generate
	long int int_min = -1001;		// Min value of random integer
	long int int_max = +2001;		// Max value of random integer
	srand((unsigned)time(NULL));
	display_random_integers(int_count, int_min, int_max);

	DTStamp();
	printf("CHECK 2.2: Check randomness of generated of uniform random integers.\n");
	int int_bins_check = 20;			// Number of bins to collect randoms
	long int int_count_check = 100000;	// Number of randoms to generate
	long int int_min_check = -15011;
	long int int_max_check = +27013;
	srand((unsigned)time(NULL));
	check_randomness_of_integers(int_bins_check, int_count_check, int_min_check, int_max_check);
	stop_timer(2);

printf("=============================================================\n");
	start_timer(3);
	DTStamp();
	printf("CHECK 3.1: Display generation of uniform random doubles.\n");
	long int dbl_count = 10;		// Number of randoms to generate
	double   dbl_min = -1001.44445;		// Min value of random integer
	double   dbl_max = +2001.66665;		// Max value of random integer
	srand((unsigned)time(NULL));
	display_random_doubles(dbl_count, dbl_min, dbl_max);

	DTStamp();
	printf("CHECK 3.2: Check randomness of generated of uniform random doubles.\n");
	int dbl_bins_check = 10;			// Number of bins to collect randoms
	long int dbl_count_check = 200000;	// Number of randoms to generate
	double   dbl_min_check = -15011.78424;
	double   dbl_max_check = +17013.53314;
	srand((unsigned)time(NULL));
	check_randomness_of_doubles(dbl_bins_check, dbl_count_check, dbl_min_check, dbl_max_check);
	stop_timer(3);

printf("=============================================================\n");
	start_timer(4);
	DTStamp();
	printf("QUEUE: Pass and sum random integers using dynamic queue implementation MPMC mode.\n");
	execute_create_pthreads();
	execute_join_pthreads();
	recordedqueue_serial_sum_check_and_fulldisplay();
	queue_result_MPMC_pthreaded_sum();
	stop_timer(4);

printf("=============================================================\n");

	total_program_duration();
	WRY_ending_salutation();

return (0);
}
// ========================================================
/*
5:01:30 **** Incremental Build of configuration Debug for project using-gcc93-boost ****
make all
Building file: ../src/using-gcc93-boost.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/usr/local/lib/gcc/x86_64-pc-linux-gnu/9.3.0/include -I/home/wruslan/apps3/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/using-gcc93-boost.d" -MT"src/using-gcc93-boost.o" -o "src/using-gcc93-boost.o" "../src/using-gcc93-boost.cpp"
Finished building: ../src/using-gcc93-boost.cpp

Building target: using-gcc93-boost
Invoking: GCC C++ Linker
g++  -o "using-gcc93-boost"  ./src/random_int_dyn_queue/random_int_dyn_queue.o  ./src/random_int_dbl/random_int_dbl.o  ./src/dtstamp/dtstamp.o  ./src/using-gcc93-boost.o   -lpthread -lrt -lm
Finished building target: using-gcc93-boost


15:01:31 Build Finished. 0 errors, 0 warnings. (took 1s.457ms)

===========================================================
wruslan@sgi-ub1604-lts-64b:~/apps2/eclipse-wks2/using-gcc93-boost/Debug$ sudo ./using-gcc93-boost
2020-03-15 15:02:41.200283398 	Starting in main(), Bismillah 3 times WRY.
2020-03-15 15:02:41.200305717 	Program started.

=============================================================
2020-03-15 15:02:41.200345157 	Timer 1 start.
2020-03-15 15:02:41.200356938 	CHECK 1: Check environment, date, time and clock.
2020-03-15 15:02:41.200375307 	Current date and time: Sun Mar 15, 2020 15:02:41
2020-03-15 15:02:41.200392184 	Current directory: /home/wruslan/apps2/eclipse-wks2/using-gcc93-boost/Debug
2020-03-15 15:02:41.200406176 	Current runfile  : ./using-gcc93-boost
2020-03-15 15:02:41.200422046 	Clock time resolution 	= 1 nanoseconds
2020-03-15 15:02:41.200440078 	Timer 1 stop. Duration (timer start-to-stop) = 0.000095932 seconds.

=============================================================
2020-03-15 15:02:41.200463304 	Timer 2 start.
2020-03-15 15:02:41.200474188 	CHECK 2.1: Display generation of uniform random integers.
j = 0 Uniform random_integer between (-1001, 2001) = 1393
j = 1 Uniform random_integer between (-1001, 2001) = 417
j = 2 Uniform random_integer between (-1001, 2001) = 200
j = 3 Uniform random_integer between (-1001, 2001) = 237
j = 4 Uniform random_integer between (-1001, 2001) = 832
j = 5 Uniform random_integer between (-1001, 2001) = 1919
j = 6 Uniform random_integer between (-1001, 2001) = -353
j = 7 Uniform random_integer between (-1001, 2001) = -12
j = 8 Uniform random_integer between (-1001, 2001) = 1644
j = 9 Uniform random_integer between (-1001, 2001) = 607

 SUCCESS: Above are the 10 generated uniform random integers between (-1001, 2001).

2020-03-15 15:02:41.200549813 	CHECK 2.2: Check randomness of generated of uniform random integers.
Random integers in range[-15011, -12909) = 	bin_count[0] = 4996 	cumulative check_bin_count = 4996
Random integers in range[-12909, -10807) = 	bin_count[1] = 4960 	cumulative check_bin_count = 9956
Random integers in range[-10807, -8705) = 	bin_count[2] = 5058 	cumulative check_bin_count = 15014
Random integers in range[-8705, -6603) = 	bin_count[3] = 4991 	cumulative check_bin_count = 20005
Random integers in range[-6603, -4501) = 	bin_count[4] = 4998 	cumulative check_bin_count = 25003
Random integers in range[-4501, -2399) = 	bin_count[5] = 5037 	cumulative check_bin_count = 30040
Random integers in range[-2399, -297) = 	bin_count[6] = 4990 	cumulative check_bin_count = 35030
Random integers in range[-297, 1805) = 	bin_count[7] = 4942 	cumulative check_bin_count = 39972
Random integers in range[1805, 3907) = 	bin_count[8] = 5037 	cumulative check_bin_count = 45009
Random integers in range[3907, 6009) = 	bin_count[9] = 5049 	cumulative check_bin_count = 50058
Random integers in range[6009, 8111) = 	bin_count[10] = 4994 	cumulative check_bin_count = 55052
Random integers in range[8111, 10213) = 	bin_count[11] = 4929 	cumulative check_bin_count = 59981
Random integers in range[10213, 12315) = 	bin_count[12] = 4988 	cumulative check_bin_count = 64969
Random integers in range[12315, 14417) = 	bin_count[13] = 4900 	cumulative check_bin_count = 69869
Random integers in range[14417, 16519) = 	bin_count[14] = 5091 	cumulative check_bin_count = 74960
Random integers in range[16519, 18621) = 	bin_count[15] = 4930 	cumulative check_bin_count = 79890
Random integers in range[18621, 20723) = 	bin_count[16] = 5117 	cumulative check_bin_count = 85007
Random integers in range[20723, 22825) = 	bin_count[17] = 5068 	cumulative check_bin_count = 90075
Random integers in range[22825, 24927) = 	bin_count[18] = 4954 	cumulative check_bin_count = 95029
Random integers in range[24927, 27029) = 	bin_count[19] = 4971 	cumulative check_bin_count = 100000

 SUCCESS: Above are the 100000 uniform random integers in the range(-15011, 27013) accounted for in the 20 bins.

2020-03-15 15:02:41.215102628 	Timer 2 stop. Duration (timer start-to-stop) = 0.014636117 seconds.

=============================================================
2020-03-15 15:02:41.215117655 	Timer 3 start.
2020-03-15 15:02:41.215126784 	CHECK 3.1: Display generation of uniform random doubles.
j = 0 Uniform random_doubles between (-1001.444450, 2001.666650) = -563.525259
j = 1 Uniform random_doubles between (-1001.444450, 2001.666650) = 1024.285115
j = 2 Uniform random_doubles between (-1001.444450, 2001.666650) = 383.563216
j = 3 Uniform random_doubles between (-1001.444450, 2001.666650) = 571.705076
j = 4 Uniform random_doubles between (-1001.444450, 2001.666650) = -473.980686
j = 5 Uniform random_doubles between (-1001.444450, 2001.666650) = -796.157738
j = 6 Uniform random_doubles between (-1001.444450, 2001.666650) = 1048.200584
j = 7 Uniform random_doubles between (-1001.444450, 2001.666650) = 1670.090003
j = 8 Uniform random_doubles between (-1001.444450, 2001.666650) = -250.200117
j = 9 Uniform random_doubles between (-1001.444450, 2001.666650) = -453.154253

 SUCCESS: Above are the 10 generated uniform random doubles between (-1001.444450, 2001.666650).

2020-03-15 15:02:41.215207803 	CHECK 3.2: Check randomness of generated of uniform random doubles.
Random doubles in range[-15011.784240, -11809.252502) = 	bin_count[0] = 20087 	cumulative check_bin_count = 20087
Random doubles in range[-11809.252502, -8606.720764) = 	bin_count[1] = 20039 	cumulative check_bin_count = 40126
Random doubles in range[-8606.720764, -5404.189026) = 	bin_count[2] = 19829 	cumulative check_bin_count = 59955
Random doubles in range[-5404.189026, -2201.657288) = 	bin_count[3] = 19995 	cumulative check_bin_count = 79950
Random doubles in range[-2201.657288, 1000.874450) = 	bin_count[4] = 20227 	cumulative check_bin_count = 100177
Random doubles in range[1000.874450, 4203.406188) = 	bin_count[5] = 20038 	cumulative check_bin_count = 120215
Random doubles in range[4203.406188, 7405.937926) = 	bin_count[6] = 19819 	cumulative check_bin_count = 140034
Random doubles in range[7405.937926, 10608.469664) = 	bin_count[7] = 20141 	cumulative check_bin_count = 160175
Random doubles in range[10608.469664, 13811.001402) = 	bin_count[8] = 20069 	cumulative check_bin_count = 180244
Random doubles in range[13811.001402, 17013.533140) = 	bin_count[9] = 19756 	cumulative check_bin_count = 200000

 SUCCESS: Above are the 200000 uniform random doubles in the range(-15011.784240, 17013.533140) accounted for in the 10 bins.

2020-03-15 15:02:41.235453615 	Timer 3 stop. Duration (timer start-to-stop) = 0.020333564 seconds.

=============================================================
2020-03-15 15:02:41.235468222 	Timer 4 start.
2020-03-15 15:02:41.235476967 	QUEUE: Pass and sum random integers using dynamic queue implementation MPMC mode.
2020-03-15 15:02:41.236631251 	(1) Success: mlockall memory current/future success. ret_lock 	= 0
2020-03-15 15:02:41.236654803 	(2) Success: pthread init attributes success. ret_pth_init 	= 0
2020-03-15 15:02:41.236676100 	(3) Success: pthread setstacksize success. ret_stacksize 	= 0
2020-03-15 15:02:41.236689956 	(4) Success: pthread setschedpolicy success. ret_schedpolicy 	= 0
2020-03-15 15:02:41.236709855 	(5) Success: pthread setschedparam priority success. ret_param_sched_priority 	= 0
2020-03-15 15:02:41.236722473 	(6) Success: pthread setsinheritsched success. ret_inheritsched = 0
2020-03-15 15:02:41.236804545 	(7) Success: pthread create pthread_producer_01 success. pthread_create_check 	= 0
2020-03-15 15:02:41.236873202 	(7) Success: pthread create pthread_producer_02 success. pthread_create_check 	= 0
2020-03-15 15:02:41.236941408 	(7) Success: pthread create pthread_consumer_01 success. pthread_create_check 	= 0
2020-03-15 15:02:41.237009192 	(7) Success: pthread create pthread_consumer_02 success. pthread_create_check 	= 0
2020-03-15 15:02:45.413834485 	(8) Success: pthread join   pthread_producer_01 success. pthread_join_check 	= 0
2020-03-15 15:02:45.413876043 	(8) Success: pthread join   pthread_producer_02 success. pthread_join_check 	= 0
2020-03-15 15:02:45.413892519 	(8) Success: pthread join   pthread_consumer_01 success. pthread_join_check 	= 0
2020-03-15 15:02:45.413907699 	(8) Success: pthread join   pthread_consumer_02 success. pthread_join_check 	= 0
2020-03-15 15:02:48.591717658 	RESULT. Initial queue size defined for dynamically adjustable queue    = 1000
2020-03-15 15:02:48.591790359 	RESULT. Actual queue entries processed(summed) in the_recorded_queue   = 50000
2020-03-15 15:02:48.591804162 	RESULT. The simple sequential queue sum_check: the_recorded_queue_sum  = 273841
2020-03-15 15:02:48.591819000 	RESULT. The MultiProducer-MultiConsumer MPMC thread sum: the_queue_sum = 273841
2020-03-15 15:02:48.591833975 	Timer 4 stop. Duration (timer start-to-stop) = 7.356365285 seconds.

=============================================================
2020-03-15 15:02:48.591865271 	Total program run duration   = 7.391670980 seconds.

2020-03-15 15:02:48.591877417 	Program ended.
2020-03-15 15:02:48.591889903 	Ending in main(), Alhamdulillah 3 times WRY.
wruslan@sgi-ub1604-lts-64b:~/apps2/eclipse-wks2/using-gcc93-boost/Debug$

*/
// ========================================================

