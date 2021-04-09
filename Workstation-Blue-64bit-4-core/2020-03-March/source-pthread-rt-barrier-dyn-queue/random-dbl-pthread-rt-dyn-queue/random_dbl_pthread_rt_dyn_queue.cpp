/*
 * random_dbl_pthread_rt_dyn_queue.cpp
 *
 *  Created on: Mar 20, 2020
 *      Author: wruslan
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>	// Use POSIX thread instead of <thread> C++11
#include <sched.h>
#include <limits.h>
#include <sys/mman.h>
#include <error.h>

#include <stdint.h>     // For intptr_t
#include <sys/types.h>  // For getpid() and getppid()
#include <unistd.h>     // For getpid() and getppid()
#include <sys/syscall.h> //For long tid = syscall(SYS_gettid);

#include "../dtstamp/dtstamp.hpp"
#include "../random_int_dbl/random_int_dbl.hpp"

// ==========================================================
// GLOBALS Used for pthreads settings
// ==========================================================
struct sched_param 	param;
pthread_attr_t 		attr;

int ret_lock, ret_pthread_init;
int ret_stacksize, ret_schedpolicy;
int ret_param_sched_priority, ret_inheritsched;

// ============================================================
// GLOBALS FOR boost queue MULTIPLE-PRODUCER, MULTIPLE-CONSUMER
// ============================================================
pthread_t  pthread_producer_01, pthread_producer_02;
pthread_t  pthread_consumer_01, pthread_consumer_02;

int ret_create_producer_01, ret_create_producer_02;
int ret_create_consumer_01, ret_create_consumer_02;

int ret_join_producer_01, ret_join_producer_02;
int ret_join_consumer_01, ret_join_consumer_02;

// ========================================================
// FOR STACK IMPLEMENTATION
// ========================================================
#include <boost/lockfree/queue.hpp>
// #include <boost/lockfree/stack.hpp>
#include <atomic>
#include <iostream>
using namespace boost::lockfree;

std::atomic<long int> the_queue_size{1000};

// FIXED SIZE QUEUE
// boost::lockfree::queue<long int, fixed_sized<true>> the_queue{the_queue_size};

// DYNAMICALLY SIZE ADJUSTED QUEUE
boost::lockfree::queue<double> the_queue{the_queue_size};
std::atomic<double> the_queue_sum{0};

// DYNAMICALLY SIZE ADJUSTED QUEUE
boost::lockfree::queue<double> the_recorded_queue{the_queue_size};
std::atomic<double> the_recorded_queue_sum{0};

// ========================================================
void *produce_01(void *data) {
// ========================================================
  srand((unsigned)time(NULL));
  //long int 	random_int1;
  double 	random_dbl1;

  for (long int i = 1; i <= 3000; ++i) {

	random_dbl1 = random_double(-50, +50);
	sleep_usec(10);

	the_queue.push(random_dbl1);
	the_recorded_queue.push(random_dbl1);  // KEPT AS RECORD WILL NOT POP OUT.

    // sleep_msec(10);  //SLEEP SOLVED TIMING PROBLEM
    sleep_usec(10);  //SLEEP SOLVED PROBLEM OF SUM (Tested with quesize = 60001)

    // UnComment the two lines below to turn ON detailed tracing
    // DTStamp();
    // printf("Running PRODUCER thread-id TID:%ld. Producer loopno = %ld \t random_dbl1 = %ld \n", syscall(SYS_gettid), i, random_dbl1);
  }

return NULL;
}

// ========================================================
void *produce_02(void *data) {
// ========================================================
	srand((unsigned)time(NULL));
	// long int 	random_int2;
	double	random_dbl2;

  for (long int i = 3001; i <= 7000; ++i) {

	random_dbl2 = random_double(-10, +10);
	sleep_usec(10);

	the_queue.push(random_dbl2);
	the_recorded_queue.push(random_dbl2);  // KEPT AS RECORD WILL NOT POP OUT.

    // sleep_msec(10);  //SLEEP SOLVED TIMING PROBLEM
    sleep_usec(10);  //SLEEP SOLVED PROBLEM OF SUM (Tested with quesize = 60001)

    // UnComment the two lines below to turn ON detailed tracing
    // DTStamp();
  	// printf("Running PRODUCER thread-id TID:%ld. Producer loopno = %ld \t random_int2 = %ld \n", syscall(SYS_gettid), i, random_int2);
  }

return NULL;
}

// ========================================================
void *consume(void *data) {
// ========================================================

  // long int entry;
  // long int threaded_sum = the_queue_sum;

  double entry;
  double threaded_sum = the_queue_sum;
  threaded_sum = threaded_sum + 0.0; 	// TO AVOID WARNING UNUSED ....

  while (the_queue.pop(entry)) {
    the_queue_sum = the_queue_sum + entry;  // Takes time so need sleep()
    threaded_sum = the_queue_sum;

   // Both sleep settings work
   // sleep_msec(10);  //SLEEP SOLVED PROBLEM OF SUM (Tested with quesize = 10001)
   sleep_usec(10);  //SLEEP SOLVED PROBLEM OF SUM (Tested with quesize = 60001)

   // UnComment the two lines below to turn ON detailed tracing
   // DTStamp();
   // printf("Running CONSUMER thread-id TID:%ld. Consumer value = %ld  \tSum = %ld \n", syscall(SYS_gettid), i, threaded_sum);
  }

return NULL;
}
// ========================================================
void recordedqueue_serial_sum_check_and_fulldisplay(void) {
// ========================================================
	double entry2;
	// long int entry2;
	long int n = 1;

	while (the_recorded_queue.pop(entry2)) {

		the_recorded_queue_sum = the_recorded_queue_sum + entry2;
		sleep_usec(10);

		// FULL DISPLAY: Uncomment line below to turn ON detailed the_recorded_stack display
		// DTStamp(); std::cout << "Display queue entry number " << n << " \t value = " << entry2 << std::endl;

		n += 1;
	}

	DTStamp(); std::cout << "RESULT. Initial queue size defined for dynamically adjustable queue    = " << the_queue_size << std::endl;
	DTStamp(); printf("RESULT. Actual queue entries processed(summed) in the_recorded_queue   = %ld \n", (n-1));
	DTStamp(); std::cout << "RESULT. The simple sequential queue sum_check: the_recorded_queue_sum  = " << the_recorded_queue_sum << std::endl;
}
// ========================================================
void execute_pthread_settings(void) {
// ========================================================

   // (1) Lock memory
	ret_lock = mlockall(MCL_CURRENT|MCL_FUTURE);
    if(ret_lock == -1) {
            DTStamp(); printf("(1) %m: mlockall memory current/future failed. ret_lock \t= %d \n", ret_lock);
            DTStamp(); printf("MUST RUN AS ROOT USING sudo ./XXX \n");
            exit(1);
    } else {
			DTStamp(); printf("(1) %m: mlockall memory current/future success. ret_lock \t= %d \n", ret_lock);
	}

    // (2) Initialize pthread attributes (default values)
    ret_pthread_init = pthread_attr_init(&attr);
    if (ret_pthread_init) {
        DTStamp(); printf("(2) %m: pthread init attributes failed. ret_pth_init \t= %d \n", ret_pthread_init);
    } else {
		DTStamp(); printf("(2) %m: pthread init attributes success. ret_pth_init \t= %d \n", ret_pthread_init);
	}

    // (3) Set a specific stack size
    ret_stacksize = pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    if (ret_stacksize) {
        DTStamp(); printf("(3) %m: pthread setstacksize failed. ret_stacksize \t= %d \n", ret_stacksize);
    } else {
		DTStamp(); printf("(3) %m: pthread setstacksize success. ret_stacksize \t= %d \n", ret_stacksize);
	}

    // (4) Set scheduler policy
    ret_schedpolicy = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret_schedpolicy) {
        DTStamp(); printf("(4) %m: pthread setschedpolicy failed. ret_schedpolicy \t= %d \n", ret_schedpolicy);
    } else {
		DTStamp(); printf("(4) %m: pthread setschedpolicy success. ret_schedpolicy \t= %d \n", ret_schedpolicy);
	}

	// (5) Set priority of pthread
    param.sched_priority = 80;
    ret_param_sched_priority = pthread_attr_setschedparam(&attr, &param);
    if (ret_param_sched_priority) {
        DTStamp(); printf("(5) %m: pthread setschedparam priority failed. ret_param_sched_priority \t= %d \n", ret_param_sched_priority);
    } else {
		DTStamp(); printf("(5) %m: pthread setschedparam priority success. ret_param_sched_priority \t= %d \n", ret_param_sched_priority);
	}

    // (6) Use scheduling parameters of attr
    ret_inheritsched  = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if ( ret_inheritsched) {
		DTStamp(); printf("(6) %m: pthread setsinheritsched failed. ret_inheritsched = %d \n", ret_inheritsched);
    } else {
		DTStamp(); printf("(6) %m: pthread setsinheritsched success. ret_inheritsched = %d \n", ret_inheritsched);
	}

}

// ========================================================
int check_pthread_create(const char *this_thread, int thread_create_check) {
// ========================================================
    if (thread_create_check != 0) {
        DTStamp(); printf("(7) Failed: pthread create %s failed. pthread_create_check \t= %d \n", this_thread, thread_create_check);
		perror("thread_create_check");
		//exit(1);
		return(1);
    } else {
		DTStamp(); printf("(7) %m: pthread create %s success. pthread_create_check \t= %d \n", this_thread, thread_create_check);
	}

return(0);
}
// ========================================================
int check_pthread_join(const char *this_thread, int thread_join_check) {
// ========================================================
if (thread_join_check != 0) {
		DTStamp(); printf("(8) Failed: pthread join %s failed. thread_join_check \t= %d \n", this_thread, thread_join_check);
		perror("thread_join_check");
		// exit(1);
		return(1);
	} else {
		DTStamp(); printf("(8) %m: pthread join   %s success. pthread_join_check \t= %d \n", this_thread, thread_join_check);
	}
return(0);
}
// ========================================================
void execute_create_pthreads(void) {
// ========================================================
// (7) Create 4 different pthreads with same inherited attributes

	// IMPORTANT
	execute_pthread_settings();

	ret_create_producer_01 = pthread_create(&pthread_producer_01, &attr, produce_01, NULL);
	check_pthread_create("pthread_producer_01", ret_create_producer_01);

	ret_create_producer_02 = pthread_create(&pthread_producer_02, &attr, produce_02, NULL);
	check_pthread_create("pthread_producer_02", ret_create_producer_02);

	ret_create_consumer_01 = pthread_create(&pthread_consumer_01, &attr, consume, NULL);
	check_pthread_create("pthread_consumer_01", ret_create_consumer_01);

	ret_create_consumer_02 = pthread_create(&pthread_consumer_02, &attr, consume, NULL);
	check_pthread_create("pthread_consumer_02", ret_create_consumer_02);

	// IMPORTANT
	// IF the_queue IS NOT EMPTY, TO ENSURE ALL THREADS FINISHED
	sleep_sec(1);  // Set to sleep sufficiently
	consume(NULL); // Repeat run on balance data (multi-consumer)

}
// ========================================================
void execute_join_pthreads(void) {
// ========================================================
// (8) Join the thread and wait until it is done

	ret_join_producer_01 = pthread_join(pthread_producer_01, NULL);
	check_pthread_join("pthread_producer_01", ret_join_producer_01);

	ret_join_producer_02 = pthread_join(pthread_producer_02, NULL);
	check_pthread_join("pthread_producer_02", ret_join_producer_02);

	ret_join_consumer_01 = pthread_join(pthread_consumer_01, NULL);
	check_pthread_join("pthread_consumer_01", ret_join_consumer_01);

	ret_join_consumer_02 = pthread_join(pthread_consumer_02, NULL);
	check_pthread_join("pthread_consumer_02", ret_join_consumer_02);

}
// ========================================================
void queue_result_MPMC_pthreaded_sum(void) {
// ========================================================
	DTStamp(); std::cout << "RESULT. The MultiProducer-MultiConsumer MPMC thread sum: the_queue_sum = " << the_queue_sum << std::endl;

	if (the_queue_sum == the_recorded_queue_sum) {
		printf("\n");
		DTStamp(); std::cout << "SUCCESS. Parallel MPMC threaded_sum is equal to sequential sum_check. \n" << std::endl;
	} else {
		printf("\n");
		DTStamp(); std::cout << "FAILED. Parallel MPMC threaded_sum sum is not equal to sequential sum_check. \n" << std::endl;
	}

    // TESTING
	//DTStamp(); printf("Uniform random_integer = %ld \n", random_integer(-10, +10));
	//DTStamp(); printf("Uniform random_double  = %lf \n", random_double(-3.5, +6.5));

}
// ========================================================




