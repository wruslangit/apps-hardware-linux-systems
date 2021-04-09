/*
 * dtstamp.cpp
 *
 *  Created on: Mar 15, 2020
 *      Author: wruslan
 */


#include <stdio.h>
#include <time.h> 		// For high-res timer clock_gettime with (nanoseconds)
#include <sys/time.h>	// For local date-time with (microseconds)
#include <unistd.h>     // getcwd()
#include <limits.h>     // perror()

// ========================================================
// GLOBALS
    time_t 			WRY_time;
    char 			WRY_strbuffer1[26];
    char			WRY_strbuffer2[60];

    struct tm* 		WRY_tminfo;
	struct timeval  WRY_usecvalnow; // inside #include <sys/time> microseconds
	struct timespec WRY_nsecvalnow; // For hires timer #include <time> nanoseconds
	struct timespec WRY_tvalres;


	struct timespec t_starttimer, t_endtimer, tnow;
	struct timespec t_startprogram, t_endprogram;


// ========================================================
void DTStamp(void) {
// ========================================================
	time(&WRY_time);

	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer1, 26, "%Y-%m-%d %H:%M:%S", WRY_tminfo);

	gettimeofday(&WRY_usecvalnow, NULL);

	printf("%s", WRY_strbuffer1);
	//printf(".%06ld \t", (long int)WRY_usecvalnow.tv_usec);

	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);
	printf(".%09ld \t", (long int)WRY_nsecvalnow.tv_nsec);
}

// ===================================================
void current_working_directory(void) {
// ===================================================
   char cwd[255];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
	   DTStamp(); printf("Current directory: %s\n", cwd);
   } else {
	   perror("getcwd() error");
   }

}
// ========================================================
void WRY_starting_salutation(void){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_startprogram = tnow;

	DTStamp();
	printf("Starting in main(), Bismillah 3 times WRY. \n");
	DTStamp();
	printf("Program started. \n");
	printf("\n");
}
// ========================================================
void WRY_ending_salutation(void){
// ========================================================
	printf("\n");
	DTStamp();
	printf("Program ended. \n");
	DTStamp(); printf("Ending in main(), Alhamdulillah 3 times WRY. \n");
}
// ========================================================
void total_program_duration(void) {
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_endprogram = tnow;

	struct timespec temp, t_duration;
	if ((t_endprogram.tv_nsec - t_startprogram.tv_nsec) < 0) {
		temp.tv_sec = t_endprogram.tv_sec - t_startprogram.tv_sec - 1;
		temp.tv_nsec = 1000000000 + t_endtimer.tv_nsec - t_startprogram.tv_nsec;
	} else {
		temp.tv_sec = t_endprogram.tv_sec - t_startprogram.tv_sec;
		temp.tv_nsec = t_endprogram.tv_nsec - t_startprogram.tv_nsec;
	}

	t_duration = temp;
	long sec_programduration  = t_duration.tv_sec;
	long nsec_programduration = t_duration.tv_nsec;
	DTStamp();
	printf("Total program run duration   = %ld.%09ld seconds. \n", sec_programduration, nsec_programduration);

}
// ========================================================
void display_date_only(void) {
// ========================================================
	time(&WRY_time);
	WRY_tminfo = localtime(&WRY_time);
	strftime(WRY_strbuffer2, 60, "%a %b %d, %Y %H:%M:%S", WRY_tminfo);

	DTStamp();
	printf("Current date and time: ");
	printf("%s \n", WRY_strbuffer2);
}

// ========================================================
void display_resolution_date_time(void) {
// ========================================================

	clock_getres(CLOCK_REALTIME, &WRY_tvalres);
	DTStamp();
	printf("Clock time resolution \t= %ld nanoseconds\n", WRY_tvalres.tv_nsec);

	/*
	clock_gettime(CLOCK_REALTIME, &WRY_nsecvalnow);
	DTStamp();
	printf("Wall clock time now \t= %ld seconds\n", WRY_nsecvalnow.tv_sec);
	DTStamp();
	printf("Wall clock time now \t= %ld nanoseconds\n", WRY_nsecvalnow.tv_nsec);
	*/
}

// ========================================================
// ALL SLEEP FUNCTIONS USING clock_nanosleep() for
// (seconds, milliseconds. microseconds and nanoseconds)
// ========================================================
void sleep_sec(long inp_sec) {

	// DTStamp(); printf("Sleep for %ld seconds \n", inp_sec);
    struct timespec res;
    res.tv_sec = inp_sec;
    res.tv_nsec = (inp_sec*1000000000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_msec(long inp_millisec) {
	// DTStamp(); printf("Sleep for %ld milliseconds \n", inp_millisec);
    struct timespec res;
    res.tv_sec = inp_millisec/1000;
    res.tv_nsec = (inp_millisec*1000000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_usec(long inp_microsec) {
	// DTStamp(); printf("Sleep for %ld microseconds \n", inp_microsec);
    struct timespec res;
    res.tv_sec = inp_microsec/1000000;
    res.tv_nsec = (inp_microsec*1000) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

void sleep_nsec(long inp_nanosec) {
	// DTStamp(); printf("Sleep for %ld nanoseconds \n", inp_nanosec);
    struct timespec res;
    res.tv_sec = inp_nanosec/1000000000;
    res.tv_nsec = (inp_nanosec*1) % 1000000000;
    clock_nanosleep(CLOCK_REALTIME, 0, &res, NULL);
}

// ========================================================
void start_timer(int timer_number){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_starttimer = tnow;

	DTStamp();
	printf("Timer %d start. \n", timer_number);
}

// ========================================================
void duration_timer(void) {
// ========================================================

	struct timespec temp, t_duration;
	if ((t_endtimer.tv_nsec - t_starttimer.tv_nsec) < 0) {
		temp.tv_sec = t_endtimer.tv_sec - t_starttimer.tv_sec - 1;
		temp.tv_nsec = 1000000000 + t_endtimer.tv_nsec - t_starttimer.tv_nsec;
	} else {
		temp.tv_sec = t_endtimer.tv_sec - t_starttimer.tv_sec;
		temp.tv_nsec = t_endtimer.tv_nsec - t_starttimer.tv_nsec;
	}

	t_duration = temp;
	long sec_timerduration  = t_duration.tv_sec;
	long nsec_timerduration = t_duration.tv_nsec;

	printf("Duration (timer start-to-stop) = %ld.%09ld seconds. \n", sec_timerduration, nsec_timerduration);

}

// ========================================================
void stop_timer(int timer_number){
// ========================================================
	clock_gettime(CLOCK_REALTIME, &tnow);
	t_endtimer = tnow;

	DTStamp();
	printf("Timer %d stop. ", timer_number);
	duration_timer();
	printf("\n");
}

// ========================================================
struct timespec duration(struct timespec timer_begin, struct timespec timer_end) {
// ========================================================
    struct timespec temp;

    if ((timer_end.tv_nsec - timer_begin.tv_nsec) < 0) {
        temp.tv_sec = timer_end.tv_sec - timer_begin.tv_sec - 1;
        temp.tv_nsec = 1000000000 + timer_end.tv_nsec - timer_begin.tv_nsec;
    } else {
        temp.tv_sec = timer_end.tv_sec - timer_begin.tv_sec;
        temp.tv_nsec = timer_end.tv_nsec - timer_begin.tv_nsec;
    }
return temp;
}

// ========================================================





