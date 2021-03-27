// File: independent-parallel-threads-06.cpp
// Date : Sun Mar  8 12:15:41 MYT 2015 WRY

// http://en.cppreference.com/w/cpp/thread

// COMPILATION
// THIS DOES NOT WORK
// g++  -o independent-parallel-threads-06.xx independent-parallel-threads-06.cpp -std=c++11 -pthread 

// THE FOLLOWING WORKS
// g++  -o independent-parallel-threads-06.xx independent-parallel-threads-06.cpp -std=c++11 -pthread -D_GLIBCXX_USE_NANOSLEEP 
// g++  -o independent-parallel-threads-06.xx independent-parallel-threads-06.cpp -std=gnu++11 -pthread -D_GLIBCXX_USE_NANOSLEEP 

#include <stdio.h>       // To use printf()
#include <iostream>      // std::cout
#include <thread>        // std::thread
#include <ctime>	 // To use the C++ timer function
#include <chrono>	 // To use the system_clock
#include <mutex>	 // To run mutual exclusion (mutex) locking thread

using namespace std;

  // Global variables (shared among all threads for Read/Write)
  double result_wry_thread_01 = 0.0;
  double result_wry_thread_02 = 0.0;
  double result_wry_thread_03 = 0.0;
  double result_total = 0.0;


// ======================================================== 
void calculate_norm1(double x, double y, double z) {
  // OPENING THREAD
  std::thread::id this_id = std::this_thread::get_id();
  auto threadstart_time = std::chrono::high_resolution_clock::now();
  printf(" %lld Start wry_thread_01. Thread_ID = %x Hex. \n", threadstart_time, this_id);
  
  // PROCESSING THREAD - DELAY (SLEEP) 10 SECONDS
  int sleep_seconds = 10;
  printf(" %lld PROCESSING wry_thread_01. Will sleep for %d seconds ... \n", threadstart_time, sleep_seconds);
  
  std::mutex g_display_mutex;
  g_display_mutex.lock();
  std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds));
  g_display_mutex.unlock();

  result_wry_thread_01 = (x + y + z);

  // CLOSING THREAD
  auto threadend_time = std::chrono::high_resolution_clock::now();
  auto duration_time = (threadend_time - threadstart_time);
  typedef std::chrono::duration<double> double_seconds;
  double process_seconds = std::chrono::duration_cast<double_seconds>(duration_time).count();
  printf(" %lld Ended wry_thread_01. Thread_ID = %x Hex. Thread processing time = %lf seconds = %lld ticks \n", threadend_time, this_id, process_seconds, duration_time);
}
// ======================================================== 
void calculate_norm2(double x, double y, double z) {

  // OPENING THREAD
  std::thread::id this_id = std::this_thread::get_id();
  auto threadstart_time = std::chrono::high_resolution_clock::now();
  printf(" %lld Start wry_thread_02. Thread_ID = %x Hex. \n", threadstart_time, this_id);

// PROCESSING THREAD - DELAY (SLEEP) 5 SECONDS
  int sleep_seconds = 5;
  printf(" %lld PROCESSING wry_thread_02. Will sleep for %d seconds ... \n", threadstart_time, sleep_seconds);
  
  std::mutex g_display_mutex;
  g_display_mutex.lock();
  std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds));
  g_display_mutex.unlock();

  result_wry_thread_02 = (x/0.675 + 15.198*y + 0.005*z);    
  
  // CLOSING THREAD
  auto threadend_time = std::chrono::high_resolution_clock::now();
  auto duration_time = (threadend_time - threadstart_time);
  typedef std::chrono::duration<double> double_seconds;
  double process_seconds = std::chrono::duration_cast<double_seconds>(duration_time).count();
  printf(" %lld Ended wry_thread_02. Thread_ID = %x Hex. Thread processing time = %lf seconds = %lld ticks \n", threadend_time, this_id, process_seconds, duration_time);
}
// ======================================================== 
void calculate_norm3(double x, double y, double z) {
  // OPENING THREAD
  std::thread::id this_id = std::this_thread::get_id();
  auto threadstart_time = std::chrono::high_resolution_clock::now();
  printf(" %lld Start wry_thread_03. Thread_ID = %x Hex. \n", threadstart_time, this_id);

 // PROCESSING THREAD - DELAY (SLEEP) 7 SECONDS
  int sleep_seconds = 7;
  printf(" %lld PROCESSING wry_thread_03. Will sleep for %d seconds ... \n", threadstart_time, sleep_seconds);
  
  std::mutex g_display_mutex;
  g_display_mutex.lock();
  std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds));
  g_display_mutex.unlock();

  result_wry_thread_03 = (2.56*x + y/1.56 + z*0.017); 
 
  // CLOSING THREAD
  auto threadend_time = std::chrono::high_resolution_clock::now();
  auto duration_time = (threadend_time - threadstart_time);
  typedef std::chrono::duration<double> double_seconds;
  double process_seconds = std::chrono::duration_cast<double_seconds>(duration_time).count();
  printf(" %lld Ended wry_thread_03. Thread_ID = %x Hex. Thread processing time = %lf seconds = %lld ticks \n", threadend_time, this_id, process_seconds, duration_time);
}

// ========================================================
void print_current_date_time() {
	time_t the_time;
	auto now = std::chrono::system_clock::now();
	the_time = std::chrono::system_clock::to_time_t(now);
	// std::cout << "Now : " << ctime(&tt) << std::endl;
        printf("Date Time: %s", ctime(&the_time));
}
// ========================================================
void time_ticks() {
	auto ticks_wry = std::chrono::high_resolution_clock::now();
        printf(" %lld ", ticks_wry);
}

// ========================================================
int main(int argc, char *argv[]) {

  // OPENING MAIN PROGRAM MESSAGE
  auto start_time = std::chrono::high_resolution_clock::now();
  time_ticks(); print_current_date_time();
  time_ticks(); printf("Bismillah. Main thread started. \n");

  // Threads are started by defining an object std::thread
  // Spawn and launch three different threads runnung the same function
  std::thread 	wry_thread_01(calculate_norm1, 1.0, 2.0, 3.0);     
  std::thread 	wry_thread_02(calculate_norm2, 4.0, 5.0, 6.0);        
  std::thread 	wry_thread_03(calculate_norm3, 2.2, 3.2, 6.2);    

  // join() - The function returns when the thread execution has completed.
  // Synchronize all threads, pause until all threads finish execution.
  wry_thread_01.join();
  wry_thread_02.join();
  wry_thread_03.join();

  // Display results of individual threads
  time_ticks(); printf("result_wry_thread_01 = %f \n", result_wry_thread_01);
  time_ticks(); printf("result_wry_thread_02 = %f \n", result_wry_thread_02);
  time_ticks(); printf("result_wry_thread_03 = %f \n", result_wry_thread_03);

  time_ticks(); printf("result_total = %f \n", result_wry_thread_01 + result_wry_thread_02 + result_wry_thread_03);

  // CALCULATE TOTAL PROCESSING TIME
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration_time = (end_time - start_time);
  typedef std::chrono::duration<double> double_seconds;
  double process_seconds = std::chrono::duration_cast<double_seconds>(duration_time).count();
  time_ticks(); printf("TOTAL PROGRAM MULTI-THREADED PROCESSING TIME = %lf seconds = %lld ticks. \n", process_seconds, duration_time);
  
  // CLOSING MAIN PROGRAM MESSAGE
  time_ticks(); print_current_date_time();
  time_ticks(); printf("Alhamdulillah. Main thread ended. \n");

  return 0;
}
// ========================================================
/*
root@hpcompaqdk-ub1004-rtai:~/Documents/Multithreaded-C++11/test2.6# g++  -o independent-parallel-threads-06.xx independent-parallel-threads-06.cpp -std=c++11 -pthread -D_GLIBCXX_USE_NANOSLEEP 
root@hpcompaqdk-ub1004-rtai:~/Documents/Multithreaded-C++11/test2.6# ./independent-parallel-threads-06.xx 
 1425871390235109 Date Time: Mon Mar  9 11:23:10 2015
 1425871390235280 Bismillah. Main thread started. 
 1425871390235345 Start wry_thread_02. Thread_ID = b6f28b70 Hex. 
 1425871390235345 PROCESSING wry_thread_02. Will sleep for 5 seconds ... 
 1425871390235340 Start wry_thread_01. Thread_ID = b7729b70 Hex. 
 1425871390235340 PROCESSING wry_thread_01. Will sleep for 10 seconds ... 
 1425871390235398 Start wry_thread_03. Thread_ID = b6727b70 Hex. 
 1425871390235398 PROCESSING wry_thread_03. Will sleep for 7 seconds ... 
 1425871395235469 Ended wry_thread_02. Thread_ID = b6f28b70 Hex. Thread processing time = 5.000124 seconds = 5000124 ticks 
 1425871397235500 Ended wry_thread_03. Thread_ID = b6727b70 Hex. Thread processing time = 7.000102 seconds = 7000102 ticks 
 1425871400235832 Ended wry_thread_01. Thread_ID = b7729b70 Hex. Thread processing time = 10.000492 seconds = 10000492 ticks 
 1425871400235899 result_wry_thread_01 = 6.000000 
 1425871400235922 result_wry_thread_02 = 81.945926 
 1425871400235932 result_wry_thread_03 = 7.788682 
 1425871400235939 result_total = 95.734608 
 1425871400235963 TOTAL PROGRAM MULTI-THREADED PROCESSING TIME = 10.000849 seconds = 10000849 ticks. 
 1425871400235969 Date Time: Mon Mar  9 11:23:20 2015
 1425871400235995 Alhamdulillah. Main thread ended. 
root@hpcompaqdk-ub1004-rtai:~/Documents/Multithreaded-C++11/test2.6# 
*/



