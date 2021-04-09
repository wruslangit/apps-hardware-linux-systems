//============================================================================
// Name        : pthread-rt-barrier-dyn-queue.cpp
// Author      : wruslan
// Version     :
// Copyright   : Jazakullah kair Ubuntu 18.04 LTS
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
 *
 *
*/
// ========================================================
// C program headers
#include <stdio.h>

// C++ program headers
#include <iostream>
using namespace std;

// WRY Date-Time stamp nanosecond display
#include "dtstamp/dtstamp.hpp"

// WRY Realtime pthread with barriers
#include "pthread-rt-barrier/pthread_rt_barrier.hpp"

// WRY Uniform Random number generators (integers, doubles)
#include "random_int_dbl/random_int_dbl.hpp"

// WRY Random doubles Pthread-RT POSIX Dynamic Queue
#include "random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.hpp"


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
		long int dbl_count = 10;			// Number of randoms to generate
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
		start_timer(5);
		DTStamp();
		printf("PTHREAD_BARRIER: Test barrier_init, barrier_wait and barrier_destroy for POSIX threads.\n");
		execute_pthread_barrier();
		stop_timer(5);

total_program_duration();
WRY_ending_salutation();
return (0);
}
// ========================================================
/*
=============================
COMPILE AND LINK
=============================
21:48:56 **** Build of configuration Debug for project pthread-rt-barrier-dyn-queue ****
make all
Building file: ../src/random_int_dbl/random_int_dbl.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/home/wruslan/apps2/boost_1_72_0/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/random_int_dbl/random_int_dbl.d" -MT"src/random_int_dbl/random_int_dbl.o" -o "src/random_int_dbl/random_int_dbl.o" "../src/random_int_dbl/random_int_dbl.cpp"
Finished building: ../src/random_int_dbl/random_int_dbl.cpp

Building file: ../src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/home/wruslan/apps2/boost_1_72_0/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.d" -MT"src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.o" -o "src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.o" "../src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.cpp"
../src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.cpp:61:56: warning: narrowing conversion of ‘the_queue_size.std::atomic<long int>::<anonymous>.std::__atomic_base<long int>::operator std::__atomic_base<long int>::__int_type()’ from ‘std::__atomic_base<long int>::__int_type’ {aka ‘long int’} to ‘boost::lockfree::queue<double>::size_type’ {aka ‘long unsigned int’} [-Wnarrowing]
   61 | boost::lockfree::queue<double> the_queue{the_queue_size};
      |                                                        ^
../src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.cpp:65:65: warning: narrowing conversion of ‘the_queue_size.std::atomic<long int>::<anonymous>.std::__atomic_base<long int>::operator std::__atomic_base<long int>::__int_type()’ from ‘std::__atomic_base<long int>::__int_type’ {aka ‘long int’} to ‘boost::lockfree::queue<double>::size_type’ {aka ‘long unsigned int’} [-Wnarrowing]
   65 | boost::lockfree::queue<double> the_recorded_queue{the_queue_size};
      |                                                                 ^
Finished building: ../src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.cpp

Building file: ../src/pthread-rt-barrier/pthread_rt_barrier.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/home/wruslan/apps2/boost_1_72_0/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/pthread-rt-barrier/pthread_rt_barrier.d" -MT"src/pthread-rt-barrier/pthread_rt_barrier.o" -o "src/pthread-rt-barrier/pthread_rt_barrier.o" "../src/pthread-rt-barrier/pthread_rt_barrier.cpp"
Finished building: ../src/pthread-rt-barrier/pthread_rt_barrier.cpp

Building file: ../src/dtstamp/dtstamp.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/home/wruslan/apps2/boost_1_72_0/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/dtstamp/dtstamp.d" -MT"src/dtstamp/dtstamp.o" -o "src/dtstamp/dtstamp.o" "../src/dtstamp/dtstamp.cpp"
Finished building: ../src/dtstamp/dtstamp.cpp

Building file: ../src/pthread-rt-barrier-dyn-queue.cpp
Invoking: GCC C++ Compiler
g++ -std=c++0x -I/home/wruslan/apps2/boost_1_72_0/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/pthread-rt-barrier-dyn-queue.d" -MT"src/pthread-rt-barrier-dyn-queue.o" -o "src/pthread-rt-barrier-dyn-queue.o" "../src/pthread-rt-barrier-dyn-queue.cpp"
Finished building: ../src/pthread-rt-barrier-dyn-queue.cpp

Building target: pthread-rt-barrier-dyn-queue
Invoking: GCC C++ Linker
g++  -o "pthread-rt-barrier-dyn-queue"  ./src/random_int_dbl/random_int_dbl.o  ./src/random-dbl-pthread-rt-dyn-queue/random_dbl_pthread_rt_dyn_queue.o  ./src/pthread-rt-barrier/pthread_rt_barrier.o  ./src/dtstamp/dtstamp.o  ./src/pthread-rt-barrier-dyn-queue.o   -lpthread -liconv -lrt -lm
Finished building target: pthread-rt-barrier-dyn-queue


21:49:00 Build Finished. 0 errors, 2 warnings. (took 4s.250ms)

============================
EXECUTE WITH SUDO
=============================
wruslan@Bluewks-Ub1804-rt38-64b:~/apps2/eclipse-wks4/Debug$ sudo ./pthread-rt-barrier-dyn-queue
[sudo] password for wruslan:
2020-03-20 21:41:20.938776544 	Starting in main(), Bismillah 3 times WRY.
2020-03-20 21:41:20.938805147 	Program started.

=============================================================
2020-03-20 21:41:20.938826696 	Timer 1 start.
2020-03-20 21:41:20.938845348 	CHECK 1: Check environment, date, time and clock.
2020-03-20 21:41:20.938862353 	Current date and time: Fri Mar 20, 2020 21:41:20
2020-03-20 21:41:20.938876994 	Current directory: /home/wruslan/apps2/eclipse-wks4/Debug
2020-03-20 21:41:20.938888523 	Current runfile  : ./pthread-rt-barrier-dyn-queue
2020-03-20 21:41:20.938901497 	Clock time resolution 	= 1 nanoseconds
2020-03-20 21:41:20.938919334 	Timer 1 stop. Duration (timer start-to-stop) = 0.000094681 seconds.

=============================================================
2020-03-20 21:41:20.938933414 	Timer 2 start.
2020-03-20 21:41:20.938942705 	CHECK 2.1: Display generation of uniform random integers.
j = 0 Uniform random_integer between (-1001, 2001) = -452
j = 1 Uniform random_integer between (-1001, 2001) = -935
j = 2 Uniform random_integer between (-1001, 2001) = 646
j = 3 Uniform random_integer between (-1001, 2001) = 845
j = 4 Uniform random_integer between (-1001, 2001) = 1762
j = 5 Uniform random_integer between (-1001, 2001) = 28
j = 6 Uniform random_integer between (-1001, 2001) = -971
j = 7 Uniform random_integer between (-1001, 2001) = 1947
j = 8 Uniform random_integer between (-1001, 2001) = -839
j = 9 Uniform random_integer between (-1001, 2001) = 1330

SUCCESS: Above are the 10 generated uniform random integers between (-1001, 2001).

2020-03-20 21:41:20.939006486 	CHECK 2.2: Check randomness of generated of uniform random integers.
Random integers in range[-15011, -12909) = 	bin_count[0] = 5072 	cumulative check_bin_count = 5072
Random integers in range[-12909, -10807) = 	bin_count[1] = 4943 	cumulative check_bin_count = 10015
Random integers in range[-10807, -8705) = 	bin_count[2] = 4882 	cumulative check_bin_count = 14897
Random integers in range[-8705, -6603) = 	bin_count[3] = 4952 	cumulative check_bin_count = 19849
Random integers in range[-6603, -4501) = 	bin_count[4] = 5097 	cumulative check_bin_count = 24946
Random integers in range[-4501, -2399) = 	bin_count[5] = 5057 	cumulative check_bin_count = 30003
Random integers in range[-2399, -297) = 	bin_count[6] = 5131 	cumulative check_bin_count = 35134
Random integers in range[-297, 1805) = 	bin_count[7] = 4867 	cumulative check_bin_count = 40001
Random integers in range[1805, 3907) = 	bin_count[8] = 5016 	cumulative check_bin_count = 45017
Random integers in range[3907, 6009) = 	bin_count[9] = 5068 	cumulative check_bin_count = 50085
Random integers in range[6009, 8111) = 	bin_count[10] = 5091 	cumulative check_bin_count = 55176
Random integers in range[8111, 10213) = 	bin_count[11] = 5072 	cumulative check_bin_count = 60248
Random integers in range[10213, 12315) = 	bin_count[12] = 4970 	cumulative check_bin_count = 65218
Random integers in range[12315, 14417) = 	bin_count[13] = 5023 	cumulative check_bin_count = 70241
Random integers in range[14417, 16519) = 	bin_count[14] = 4839 	cumulative check_bin_count = 75080
Random integers in range[16519, 18621) = 	bin_count[15] = 4962 	cumulative check_bin_count = 80042
Random integers in range[18621, 20723) = 	bin_count[16] = 5042 	cumulative check_bin_count = 85084
Random integers in range[20723, 22825) = 	bin_count[17] = 5047 	cumulative check_bin_count = 90131
Random integers in range[22825, 24927) = 	bin_count[18] = 4887 	cumulative check_bin_count = 95018
Random integers in range[24927, 27029) = 	bin_count[19] = 4982 	cumulative check_bin_count = 100000

SUCCESS: Above are the 100000 uniform random integers in the range(-15011, 27013) accounted for in the 20 bins.

2020-03-20 21:41:20.952971832 	Timer 2 stop. Duration (timer start-to-stop) = 0.014031209 seconds.

=============================================================
2020-03-20 21:41:20.952991912 	Timer 3 start.
2020-03-20 21:41:20.953001599 	CHECK 3.1: Display generation of uniform random doubles.
j = 0 Uniform random_doubles between (-1001.444450, 2001.666650) = 1302.109603
j = 1 Uniform random_doubles between (-1001.444450, 2001.666650) = 1239.158499
j = 2 Uniform random_doubles between (-1001.444450, 2001.666650) = 1706.920808
j = 3 Uniform random_doubles between (-1001.444450, 2001.666650) = 229.204378
j = 4 Uniform random_doubles between (-1001.444450, 2001.666650) = -499.848044
j = 5 Uniform random_doubles between (-1001.444450, 2001.666650) = 1182.011184
j = 6 Uniform random_doubles between (-1001.444450, 2001.666650) = 1922.587261
j = 7 Uniform random_doubles between (-1001.444450, 2001.666650) = 873.655422
j = 8 Uniform random_doubles between (-1001.444450, 2001.666650) = 1512.173320
j = 9 Uniform random_doubles between (-1001.444450, 2001.666650) = 59.106659

SUCCESS: Above are the 10 generated uniform random doubles between (-1001.444450, 2001.666650).

2020-03-20 21:41:20.953095143 	CHECK 3.2: Check randomness of generated of uniform random doubles.
Random doubles in range[-15011.784240, -11809.252502) = 	bin_count[0] = 19998 	cumulative check_bin_count = 19998
Random doubles in range[-11809.252502, -8606.720764) = 	bin_count[1] = 20026 	cumulative check_bin_count = 40024
Random doubles in range[-8606.720764, -5404.189026) = 	bin_count[2] = 19779 	cumulative check_bin_count = 59803
Random doubles in range[-5404.189026, -2201.657288) = 	bin_count[3] = 19910 	cumulative check_bin_count = 79713
Random doubles in range[-2201.657288, 1000.874450) = 	bin_count[4] = 19785 	cumulative check_bin_count = 99498
Random doubles in range[1000.874450, 4203.406188) = 	bin_count[5] = 20091 	cumulative check_bin_count = 119589
Random doubles in range[4203.406188, 7405.937926) = 	bin_count[6] = 20132 	cumulative check_bin_count = 139721
Random doubles in range[7405.937926, 10608.469664) = 	bin_count[7] = 20008 	cumulative check_bin_count = 159729
Random doubles in range[10608.469664, 13811.001402) = 	bin_count[8] = 19924 	cumulative check_bin_count = 179653
Random doubles in range[13811.001402, 17013.533140) = 	bin_count[9] = 20347 	cumulative check_bin_count = 200000

SUCCESS: Above are the 200000 uniform random doubles in the range(-15011.784240, 17013.533140) accounted for in the 10 bins.

2020-03-20 21:41:20.968333016 	Timer 3 stop. Duration (timer start-to-stop) = 0.015335506 seconds.

=============================================================
2020-03-20 21:41:20.968351046 	Timer 4 start.
2020-03-20 21:41:20.968359652 	QUEUE: Pass and sum random integers using dynamic queue implementation MPMC mode.
2020-03-20 21:41:21.060517650 	(1) Success: mlockall memory current/future success. ret_lock 	= 0
2020-03-20 21:41:21.060549295 	(2) Success: pthread init attributes success. ret_pth_init 	= 0
2020-03-20 21:41:21.060560381 	(3) Success: pthread setstacksize success. ret_stacksize 	= 0
2020-03-20 21:41:21.060574742 	(4) Success: pthread setschedpolicy success. ret_schedpolicy 	= 0
2020-03-20 21:41:21.060591838 	(5) Success: pthread setschedparam priority success. ret_param_sched_priority 	= 0
2020-03-20 21:41:21.060605700 	(6) Success: pthread setsinheritsched success. ret_inheritsched = 0
2020-03-20 21:41:21.060806870 	(7) Success: pthread create pthread_producer_01 success. pthread_create_check 	= 0
2020-03-20 21:41:21.061093978 	(7) Success: pthread create pthread_producer_02 success. pthread_create_check 	= 0
2020-03-20 21:41:21.061393960 	(7) Success: pthread create pthread_consumer_01 success. pthread_create_check 	= 0
2020-03-20 21:41:21.061655456 	(7) Success: pthread create pthread_consumer_02 success. pthread_create_check 	= 0
2020-03-20 21:41:22.593894275 	(8) Success: pthread join   pthread_producer_01 success. pthread_join_check 	= 0
2020-03-20 21:41:22.593928986 	(8) Success: pthread join   pthread_producer_02 success. pthread_join_check 	= 0
2020-03-20 21:41:22.593946696 	(8) Success: pthread join   pthread_consumer_01 success. pthread_join_check 	= 0
2020-03-20 21:41:22.593966736 	(8) Success: pthread join   pthread_consumer_02 success. pthread_join_check 	= 0
2020-03-20 21:41:23.131017987 	RESULT. Initial queue size defined for dynamically adjustable queue    = 1000
2020-03-20 21:41:23.131088585 	RESULT. Actual queue entries processed(summed) in the_recorded_queue   = 7000
2020-03-20 21:41:23.131106598 	RESULT. The simple sequential queue sum_check: the_recorded_queue_sum  = -875.761
2020-03-20 21:41:23.131149240 	RESULT. The MultiProducer-MultiConsumer MPMC thread sum: the_queue_sum = -875.761

2020-03-20 21:41:23.131192282 	SUCCESS. Parallel MPMC threaded_sum is equal to sequential sum_check.

2020-03-20 21:41:23.131213631 	Timer 4 stop. Duration (timer start-to-stop) = 2.162859796 seconds.

=============================================================
2020-03-20 21:41:23.131251792 	Timer 5 start.
2020-03-20 21:41:23.131269617 	PTHREAD_BARRIER: Test barrier_init, barrier_wait and barrier_destroy for POSIX threads.
2020-03-20 21:41:23.131290640 	INITIALIZE: pthread_barrier_init 	PID:25364 Barrier for 9 threads initialized in main().
2020-03-20 21:41:23.177817640 	CREATE: pthread_create thread:0 	PID:25364 in main().
2020-03-20 21:41:23.177857380 	Started run thread:0 in threadFn()	TID:25369 Run is to wait for 14 seconds.
2020-03-20 21:41:23.218922406 	CREATE: pthread_create thread:1 	PID:25364 in main().
2020-03-20 21:41:23.218942554 	Started run thread:1 in threadFn()	TID:25370 Run is to wait for 23 seconds.
2020-03-20 21:41:23.260293761 	CREATE: pthread_create thread:2 	PID:25364 in main().
2020-03-20 21:41:23.303040810 	Started run thread:2 in threadFn()	TID:25371 Run is to wait for 12 seconds.
2020-03-20 21:41:23.303842564 	Started run thread:3 in threadFn()	TID:25372 Run is to wait for 21 seconds.
2020-03-20 21:41:23.303883397 	CREATE: pthread_create thread:3 	PID:25364 in main().
2020-03-20 21:41:23.346719155 	CREATE: pthread_create thread:4 	PID:25364 in main().
2020-03-20 21:41:23.348236540 	Started run thread:4 in threadFn()	TID:25373 Run is to wait for 16 seconds.
2020-03-20 21:41:23.389128819 	CREATE: pthread_create thread:5 	PID:25364 in main().
2020-03-20 21:41:23.390166221 	Started run thread:5 in threadFn()	TID:25374 Run is to wait for 24 seconds.
2020-03-20 21:41:23.431938820 	CREATE: pthread_create thread:6 	PID:25364 in main().
2020-03-20 21:41:23.433275183 	Started run thread:6 in threadFn()	TID:25375 Run is to wait for 8 seconds.
2020-03-20 21:41:23.474824510 	CREATE: pthread_create thread:7 	PID:25364 in main().
2020-03-20 21:41:23.475560976 	Started run thread:7 in threadFn()	TID:25376 Run is to wait for 24 seconds.
2020-03-20 21:41:31.433463955 	Finished run thread:6 in threadFn()	TID:25375 Run duration = 8.001516048 seconds.
2020-03-20 21:41:35.303216598 	Finished run thread:2 in threadFn()	TID:25371 Run duration = 12.042867181 seconds.
2020-03-20 21:41:37.178057516 	Finished run thread:0 in threadFn()	TID:25369 Run duration = 14.000184629 seconds.
2020-03-20 21:41:39.348418655 	Finished run thread:4 in threadFn()	TID:25373 Run duration = 16.001683774 seconds.
2020-03-20 21:41:44.304027771 	Finished run thread:3 in threadFn()	TID:25372 Run duration = 21.002179300 seconds.
2020-03-20 21:41:46.219136944 	Finished run thread:1 in threadFn()	TID:25370 Run duration = 23.000180437 seconds.
2020-03-20 21:41:47.390321161 	Finished run thread:5 in threadFn()	TID:25374 Run duration = 24.001152529 seconds.
2020-03-20 21:41:47.475733346 	Finished run thread:7 in threadFn()	TID:25376 Run duration = 24.000858856 seconds.
2020-03-20 21:41:47.475788117 	Thread:7 waiting at barrier 		TID:25376 waiting in threadFn().
2020-03-20 21:41:47.475849608 	Thread:6 waiting at barrier 		TID:25375 waiting in threadFn().
2020-03-20 21:41:47.475872811 	Thread:0 waiting at barrier 		TID:25369 waiting in threadFn().
2020-03-20 21:41:47.475901038 	Thread:1 waiting at barrier 		TID:25370 waiting in threadFn().
2020-03-20 21:41:47.475930827 	Thread:4 waiting at barrier 		TID:25373 waiting in threadFn().
2020-03-20 21:41:47.475947461 	Thread:5 waiting at barrier 		TID:25374 waiting in threadFn().
2020-03-20 21:41:47.475995069 	Thread:2 waiting at barrier 		TID:25371 waiting in threadFn().
2020-03-20 21:41:47.476031781   Thread:3 waiting at barrier 		TID:25372 waiting in threadFn().
2020-03-20 21:41:47.476071262 	Main() is waiting at barrier 		PID:25364 in main().
2020-03-20 21:41:47.476102695 	JOIN: pthread_join thread:0 		PID:25364 in main().
2020-03-20 21:41:47.476119125 	JOIN: pthread_join thread:1 		PID:25364 in main().
2020-03-20 21:41:47.476138380 	JOIN: pthread_join thread:2 		PID:25364 in main().
2020-03-20 21:41:47.476155728 	JOIN: pthread_join thread:3 		PID:25364 in main().
2020-03-20 21:41:47.482106316 	JOIN: pthread_join thread:4 		PID:25364 in main().
2020-03-20 21:41:47.486914659 	JOIN: pthread_join thread:5 		PID:25364 in main().
2020-03-20 21:41:47.490557740 	JOIN: pthread_join thread:6 		PID:25364 in main().
2020-03-20 21:41:47.494385911 	JOIN: pthread_join thread:7 		PID:25364 in main().
2020-03-20 21:41:47.494402519 	DESTROY: pthread_barrier_destroy 	PID:25364 Barrier for 9 threads destroyed in main().
2020-03-20 21:41:47.494412202 	Timer 5 stop. Duration (timer start-to-stop) = 24.363163406 seconds.

2020-03-20 21:41:47.494472867 	Total program run duration   = 26.555716630 seconds.

2020-03-20 21:41:47.494493422 	Program ended.
2020-03-20 21:41:47.494501494 	Ending in main(), Alhamdulillah 3 times WRY.
wruslan@Bluewks-Ub1804-rt38-64b:~/apps2/eclipse-wks4/Debug$

*/
// ========================================================
