/*
 * random_dbl_pthread_rt_dyn_queue.hpp
 *
 *  Created on: Mar 20, 2020
 *      Author: wruslan
 */

#ifndef RANDOM_DBL_PTHREAD_RT_DYN_QUEUE_HPP_
#define RANDOM_DBL_PTHREAD_RT_DYN_QUEUE_HPP_

void queue_result_MPMC_pthreaded_sum(void);
void recordedqueue_serial_sum_check_and_fulldisplay(void);

void *pthread_func_producer_01(void *data);
void *pthread_func_producer_02(void *data);
void *pthread_func_consumer_01(void *data);
void *pthread_func_consumer_02(void *data);

void execute_pthread_settings(void);

void execute_create_pthreads(void);
int check_pthread_create(const char *this_thread, int thread_create_check);

void execute_join_pthreads(void);
int check_pthread_join(const char *this_thread, int thread_join_check);

#endif /* RANDOM_DBL_PTHREAD_RT_DYN_QUEUE_HPP_ */
