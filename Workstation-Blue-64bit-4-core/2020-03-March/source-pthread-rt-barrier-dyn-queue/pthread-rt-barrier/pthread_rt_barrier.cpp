/*
 * pthread_rt_barrier.cpp
 *
 *  Created on: Mar 20, 2020
 *      Author: wruslan
 */

#include <stdlib.h> // For srand() and rand(), scanf(),
#include <unistd.h>

#include <pthread.h>
#include <time.h>		// For sleep()

#include <stdint.h>     // For intptr_t
#include <sys/types.h>  // For getpid() and getppid()
#include <unistd.h>     // For getpid() and getppid()
#include <sys/syscall.h> //For long tid = syscall(SYS_gettid);
#include <stdio.h>

// C++ program headers
#include <iostream>
using namespace std;

#include "../dtstamp/dtstamp.hpp"

// ========================================================

#define THREAD_COUNT 8

pthread_barrier_t mybarrier;

// ========================================================
void* threadFn(void *id_ptr) {
// ========================================================
  struct timespec t_startthread, t_endthread, thread_tnow;
  clock_gettime(CLOCK_REALTIME, &thread_tnow);
  t_startthread = thread_tnow;

  int thread_id = *(int*)id_ptr;
  int wait_sec = 1 + rand() % 25; // Maximum work time.

  DTStamp(); printf("Started run thread:%d in threadFn()\tTID:%ld Run is to wait for %d seconds.\n", thread_id, syscall(SYS_gettid), wait_sec);

  	  sleep(wait_sec); // RUNNING TIME SIMULATOR

  clock_gettime(CLOCK_REALTIME, &thread_tnow);
  t_endthread = thread_tnow;

  DTStamp(); printf("Finished run thread:%d in threadFn()\tTID:%ld ", thread_id, syscall(SYS_gettid));
  duration_thread(t_startthread, t_endthread);

  pthread_barrier_wait(&mybarrier);
  DTStamp(); printf("Thread:%d waiting at barrier \t\tTID:%ld waiting in threadFn(). \n", thread_id, syscall(SYS_gettid));

return NULL;
}

// ========================================================
void execute_pthread_barrier(void) {
// ========================================================

  int i;
  pthread_t 	ids[THREAD_COUNT];
  int 			short_ids[THREAD_COUNT];

  srand(time(NULL));
  pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT + 1);
  DTStamp(); printf("INITIALIZE: pthread_barrier_init \tPID:%d Barrier for %d threads initialized in main(). \n", getpid(), THREAD_COUNT+1);

  for (i=0; i < THREAD_COUNT; i++) {
    short_ids[i] = i;
    pthread_create(&ids[i], NULL, threadFn, &short_ids[i]);
    DTStamp(); printf("CREATE: pthread_create thread:%d \tPID:%d in main().\n", i, getpid());
  }

  pthread_barrier_wait(&mybarrier);
  DTStamp(); printf("Main() is waiting at barrier \t\tPID:%d in main().\n", getpid());

  for (i=0; i < THREAD_COUNT; i++) {
    pthread_join(ids[i], NULL);
    DTStamp(); printf("JOIN: pthread_join thread:%d \t\tPID:%d in main().\n", i, getpid());
  }

  pthread_barrier_destroy(&mybarrier);
  DTStamp(); printf("DESTROY: pthread_barrier_destroy \tPID:%d Barrier for %d threads destroyed in main(). \n", getpid(), THREAD_COUNT+1);

// return (NULL);
}
