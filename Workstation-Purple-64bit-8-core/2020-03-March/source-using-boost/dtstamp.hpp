/*
 * dtstamp.hpp
 *
 *  Created on: Mar 15, 2020
 *      Author: wruslan
 */

#ifndef DTSTAMP_HPP_
#define DTSTAMP_HPP_

void DTStamp(void);
void WRY_starting_salutation(void);
void WRY_ending_salutation(void);
void total_program_duration(void);

void current_working_directory(void);
void display_date_only(void);
void display_resolution_date_time(void);

void sleep_sec(long inp_sec);
void sleep_msec(long inp_millisec);
void sleep_usec(long inp_microsec);
void sleep_nsec(long inp_nanosec);

void start_timer(int timer_num);
void stop_timer(int timer_num);
void duration_timer(void);

struct timespec duration(struct timespec timer_begin, struct timespec timer_end);


#endif /* DTSTAMP_HPP_ */
