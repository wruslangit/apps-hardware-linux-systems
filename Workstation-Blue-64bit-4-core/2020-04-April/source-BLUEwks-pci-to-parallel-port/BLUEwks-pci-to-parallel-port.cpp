//============================================================================
// Name        : BLUEwks-pci-to-parallel-port.cpp
// Author      : wruslan
// Version     :
// Copyright   : Busmillah Hirrahma Nirrahim
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
REFERENCE: https://www.howtoforge.com/tutorial/accessing-parallel-ports-on-linux/

*/
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// WRY Date-Time stamp nanosecond display
#include "dtstamp/dtstamp.hpp"

// WRY parallel port codes
#include "pci-parallel-port/pci_parallel_port.hpp"

// ========================================================
int main(int argc, char* argv[]){
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
	printf("PARPORT01: User must have root permission to access the port.\n");
	check_io_priority_level();
	check_io_permission_parport01();
	open_fd_parport01();
	test_writepci_to_parport01();
	stop_timer(2);

    printf("=============================================================\n");
	start_timer(3);
	DTStamp();
	printf("PARPORT02: User must have root permission to access the port.\n");
	check_io_priority_level();
	check_io_permission_parport02();
	open_fd_parport02();
	test_writepci_to_parport02();
	stop_timer(3);

	printf("=============================================================\n");
	DTStamp();
	printf("GROUP CLOSING: To make different file descriptor numbers. Otherwise, reuse.\n");
	close_fd_parport01();
	close_fd_parport02();

	printf("=============================================================\n");
	total_program_duration();
	WRY_ending_salutation();

return (0);
}
// ========================================================
/*
wruslan@BLUEwks-Ub1804-rt38-64b:~/apps/cpp-eclipse-wks/parallel-port-01/Debug$ sudo ./pci-to-parallel-port
2020-04-16 12:10:55.604079496 	Starting in main(), Bismillah 3 times WRY.
2020-04-16 12:10:55.604107208 	Program started.

=============================================================
2020-04-16 12:10:55.604134915 	Timer 1 start.
2020-04-16 12:10:55.604152000 	CHECK 1: Check environment, date, time and clock.
2020-04-16 12:10:55.604171975 	Current date and time: Thu Apr 16, 2020 12:10:55
2020-04-16 12:10:55.604190238 	Current directory: /home/wruslan/apps/cpp-eclipse-wks/parallel-port-01/Debug
2020-04-16 12:10:55.604206432 	Current runfile  : ./pci-to-parallel-port
2020-04-16 12:10:55.604224152 	Clock time resolution 	= 1 nanoseconds
2020-04-16 12:10:55.604241383 	Timer 1 stop. Duration (timer start-to-stop) = 0.000106799 seconds.

=============================================================
2020-04-16 12:10:55.604265570 	Timer 2 start.
2020-04-16 12:10:55.604285666 	PARPORT01: User must have root permission to access the port.
2020-04-16 12:10:55.604293043 	SUCCESS: Set max priority level io_prio_lvl 	= 0
2020-04-16 12:10:55.604313687 	SUCCESS: Set port i/o permissions io_perm_parport01 	= 0
2020-04-16 12:10:55.604333182 	STARTED  open_fd_parport01(void).
2020-04-16 12:10:55.653992672 	SUCCESS: Open DEVICE_PARPORT_01 (/dev/lp0).
2020-04-16 12:10:55.654025521 	SUCCESS: Display file descriptor fd_parport01 	= 3
2020-04-16 12:10:55.654041475 	SUCCESS: Display BASEPORT_01 	= 0xBF00
2020-04-16 12:10:55.654061175 	SUCCESS: Display PARPORT_IRQ_01 = 16
2020-04-16 12:10:55.654078106 	SUCCESS: Display CPUMAP_01 	= 0x04
2020-04-16 12:10:55.654096361 	SUCCESS: Display PERIOD_01 	= 500000 (ns)
2020-04-16 12:10:55.654115761 	SUCCESS: Display TICK_TIME_01 	= 1000000 (ns)
2020-04-16 12:10:55.654133352 	FINISHED open_fd_parport01(void).
2020-04-16 12:10:55.654149874 	STARTED  test_writepci_to_parport01(void).
2020-04-16 12:10:55.654184470 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 0 	char= A bin= 01000001 hex= 0x41 int= 65
2020-04-16 12:10:55.654207598 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 1 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654231781 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 2 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 12:10:55.654253205 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 3 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.654279969 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 4 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 12:10:55.654301140 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 5 	char= d bin= 01100100 hex= 0x64 int= 100
2020-04-16 12:10:55.654324162 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 6 	char= u bin= 01110101 hex= 0x75 int= 117
2020-04-16 12:10:55.654350373 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 7 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654376483 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 8 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.654400543 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 9 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654427453 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 10 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654456798 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 11 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.654482231 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 12 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 12:10:55.654506868 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 13 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.654533081 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 14 	char= H bin= 01001000 hex= 0x48 int= 72
2020-04-16 12:10:55.654559083 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 15 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.654583318 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 16 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.654607360 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 17 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.654633968 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 18 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.654660164 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 19 	char= b bin= 01100010 hex= 0x62 int= 98
2020-04-16 12:10:55.654686479 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 20 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.654712063 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 21 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654736134 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 22 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.654762003 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 23 	char= A bin= 01000001 hex= 0x41 int= 65
2020-04-16 12:10:55.654785648 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 24 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.654809647 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 25 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.654833340 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 26 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 12:10:55.654859111 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 27 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.654883945 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 28 	char= n bin= 01101110 hex= 0x6e int= 110
2020-04-16 12:10:55.654910790 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 29 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.654935766 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 30 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-16 12:10:55.654960671 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 31 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-16 12:10:55.654987933 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 32 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-16 12:10:55.655012512 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 33 	char= ! bin= 00100001 hex= 0x21 int= 33
2020-04-16 12:10:55.655031911 	FINISHED test_writepci_to_parport01(void).
2020-04-16 12:10:55.655049361 	Timer 2 stop. Duration (timer start-to-stop) = 0.050783519 seconds.

=============================================================
2020-04-16 12:10:55.655080743 	Timer 3 start.
2020-04-16 12:10:55.655097507 	PARPORT02: User must have root permission to access the port.
2020-04-16 12:10:55.655116333 	SUCCESS: Set max priority level io_prio_lvl 	= 0
2020-04-16 12:10:55.655138488 	SUCCESS: Set port i/o permissions io_perm_parport02 	= 0
2020-04-16 12:10:55.655158420 	STARTED  open_fd_parport02(void).
2020-04-16 12:10:55.655200101 	SUCCESS: Open DEVICE_PARPORT_02 (/dev/lp1).
2020-04-16 12:10:55.655218852 	SUCCESS: Display file descriptor fd_parport02 	= 4
2020-04-16 12:10:55.655238428 	SUCCESS: Display BASEPORT_02 	= 0xDF00
2020-04-16 12:10:55.655259615 	SUCCESS: Display PARPORT_IRQ_02 = 19
2020-04-16 12:10:55.655276504 	SUCCESS: Display CPUMAP_02 	= 0x04
2020-04-16 12:10:55.655297593 	SUCCESS: Display PERIOD_02 	= 500000 (ns)
2020-04-16 12:10:55.655316436 	SUCCESS: Display TICK_TIME_02 	= 1000000 (ns)
2020-04-16 12:10:55.655338156 	FINISHED open_fd_parport02(void).
2020-04-16 12:10:55.655354557 	STARTED  test_writepci_to_parport02(void).
2020-04-16 12:10:55.655376011 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 0 	char= B bin= 01000010 hex= 0x42 int= 66
2020-04-16 12:10:55.655402683 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 1 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.655428780 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 2 	char= s bin= 01110011 hex= 0x73 int= 115
2020-04-16 12:10:55.655452576 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 3 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 12:10:55.655478789 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 4 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.655502265 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 5 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.655524839 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 6 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 12:10:55.655544147 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 7 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.655569219 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 8 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 12:10:55.655593332 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 9 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.655617046 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 10 	char= H bin= 01001000 hex= 0x48 int= 72
2020-04-16 12:10:55.655640877 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 11 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.655667463 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 12 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.655693453 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 13 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.655719214 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 14 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.655745248 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 15 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 12:10:55.655771067 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 16 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 12:10:55.655796974 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 17 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.655820623 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 18 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.655846638 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 19 	char= N bin= 01001110 hex= 0x4e int= 78
2020-04-16 12:10:55.655873260 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 20 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.655897012 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 21 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.655927639 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 22 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 12:10:55.655953877 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 23 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 12:10:55.655977714 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 24 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 12:10:55.656002771 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 25 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 12:10:55.656025985 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 26 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 12:10:55.656054093 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 27 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 12:10:55.656078133 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 28 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-16 12:10:55.656104892 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 29 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-16 12:10:55.656130866 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 30 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-16 12:10:55.656157368 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 31 	char= ! bin= 00100001 hex= 0x21 int= 33
2020-04-16 12:10:55.656177437 	FINISHED test_writepci_to_parport02(void).
2020-04-16 12:10:55.656195111 	Timer 3 stop. Duration (timer start-to-stop) = 0.001114421 seconds.

=============================================================
2020-04-16 12:10:55.656227090 	GROUP CLOSING: To make different file descriptor numbers. Otherwise, reuse.

2020-04-16 12:10:55.656251596 	STARTED  close_fd_parport01(void).
2020-04-16 12:10:55.656267972 	CHECK: Before closing file descriptor number: fd_parport01 	= 3
2020-04-16 12:10:55.656303172 	SUCCESS  closing DEVICE_PARPORT_01. Status: closed_fd_parport01 = 0
2020-04-16 12:10:55.656321984 	CHECK: After closing file descriptor number: fd_parport01 	= 3
2020-04-16 12:10:55.656340871 	FINISHED close_fd_parport01(void).

2020-04-16 12:10:55.656362933 	STARTED  close_fd_parport02(void).
2020-04-16 12:10:55.656379504 	CHECK: Before closing file descriptor number: fd_parport02 	= 4
2020-04-16 12:10:55.656406017 	SUCCESS  closing DEVICE_PARPORT_02. Status: closed_fd_parport02 = 0
2020-04-16 12:10:55.656425749 	CHECK: After closing file descriptor number: fd_parport02 	= 4
2020-04-16 12:10:55.656444628 	FINISHED close_fd_parport02(void).
=============================================================
2020-04-16 12:10:55.656467764 	Total program run duration   = 0.052511498 seconds.

2020-04-16 12:10:55.656492319 	Program ended.
2020-04-16 12:10:55.656509096 	Ending in main(), Alhamdulillah 3 times WRY.
wruslan@BLUEwks-Ub1804-rt38-64b:~/apps/cpp-eclipse-wks/parallel-port-01/Debug$

*/
// ========================================================
