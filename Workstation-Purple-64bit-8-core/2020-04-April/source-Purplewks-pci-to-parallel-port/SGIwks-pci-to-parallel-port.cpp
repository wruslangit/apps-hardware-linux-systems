//============================================================================
// Name        : SGIwks-pci-to-parallel-port.cpp
// Author      : wruslan
// Version     :
// Copyright   : Bismillah Hirrahma Nirrahim
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
wruslan@SGIwks-Ub1804-rt38-64b:~/apps/cpp-eclipse-wks/SGIwks-pci-to-parallel-port/Debug$ sudo ./SGIwks-pci-to-parallel-port
[sudo] password for wruslan:
2020-04-16 13:37:04.495980539 	Starting in main(), Bismillah 3 times WRY.
2020-04-16 13:37:04.496002155 	Program started.

=============================================================
2020-04-16 13:37:04.496046112 	Timer 1 start.
2020-04-16 13:37:04.496053201 	CHECK 1: Check environment, date, time and clock.
2020-04-16 13:37:04.496073078 	Current date and time: Thu Apr 16, 2020 13:37:04
2020-04-16 13:37:04.496085449 	Current directory: /home/wruslan/apps/cpp-eclipse-wks/SGIwks-pci-to-parallel-port/Debug
2020-04-16 13:37:04.496095350 	Current runfile  : ./SGIwks-pci-to-parallel-port
2020-04-16 13:37:04.496107152 	Clock time resolution 	= 1 nanoseconds
2020-04-16 13:37:04.496119619 	Timer 1 stop. Duration (timer start-to-stop) = 0.000074046 seconds.

=============================================================
2020-04-16 13:37:04.496146977 	Timer 2 start.
2020-04-16 13:37:04.496164423 	PARPORT01: User must have root permission to access the port.
2020-04-16 13:37:04.496176627 	SUCCESS: Set max priority level io_prio_lvl 	= 0
2020-04-16 13:37:04.496187644 	SUCCESS: Set port i/o permissions io_perm_parport01 	= 0
2020-04-16 13:37:04.496196551 	STARTED  open_fd_parport01(void).
2020-04-16 13:37:04.496224248 	SUCCESS: Open DEVICE_PARPORT_01 (/dev/lp0).
2020-04-16 13:37:04.496232951 	SUCCESS: Display file descriptor fd_parport01 	= 3
2020-04-16 13:37:04.496241673 	SUCCESS: Display BASEPORT_01 	= 0x378
2020-04-16 13:37:04.496251188 	SUCCESS: Display PARPORT_IRQ_01 = 7
2020-04-16 13:37:04.496259927 	SUCCESS: Display CPUMAP_01 	= 0x08
2020-04-16 13:37:04.496269286 	SUCCESS: Display PERIOD_01 	= 500000 (ns)
2020-04-16 13:37:04.496278319 	SUCCESS: Display TICK_TIME_01 	= 1000000 (ns)
2020-04-16 13:37:04.496290118 	FINISHED open_fd_parport01(void).
2020-04-16 13:37:04.496298995 	STARTED  test_writepci_to_parport01(void).
2020-04-16 13:37:04.496316015 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 0 	char= S bin= 01010011 hex= 0x53 int= 83
2020-04-16 13:37:04.496329329 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 1 	char= G bin= 01000111 hex= 0x47 int= 71
2020-04-16 13:37:04.496341461 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 2 	char= I bin= 01001001 hex= 0x49 int= 73
2020-04-16 13:37:04.496354547 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 3 	char= w bin= 01110111 hex= 0x77 int= 119
2020-04-16 13:37:04.496366708 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 4 	char= k bin= 01101011 hex= 0x6b int= 107
2020-04-16 13:37:04.496378424 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 5 	char= s bin= 01110011 hex= 0x73 int= 115
2020-04-16 13:37:04.496390729 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 6 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.496402546 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 7 	char= A bin= 01000001 hex= 0x41 int= 65
2020-04-16 13:37:04.496414366 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 8 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496425914 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 9 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 13:37:04.496438299 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 10 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.496449865 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 11 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 13:37:04.496461170 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 12 	char= d bin= 01100100 hex= 0x64 int= 100
2020-04-16 13:37:04.496473011 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 13 	char= u bin= 01110101 hex= 0x75 int= 117
2020-04-16 13:37:04.496484364 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 14 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496495795 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 15 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.496507247 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 16 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496518923 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 17 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496530411 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 18 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.496542111 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 19 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 13:37:04.496554165 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 20 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.496565727 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 21 	char= H bin= 01001000 hex= 0x48 int= 72
2020-04-16 13:37:04.496577200 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 22 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.496588709 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 23 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.496600418 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 24 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.496611870 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 25 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.496623615 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 26 	char= b bin= 01100010 hex= 0x62 int= 98
2020-04-16 13:37:04.496635519 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 27 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.496646926 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 28 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496658399 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 29 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.496669800 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 30 	char= A bin= 01000001 hex= 0x41 int= 65
2020-04-16 13:37:04.496681524 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 31 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.496692931 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 32 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.496704577 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 33 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 13:37:04.496716469 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 34 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.496727903 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 35 	char= n bin= 01101110 hex= 0x6e int= 110
2020-04-16 13:37:04.496739370 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 36 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.496750798 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 37 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-16 13:37:04.496762561 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 38 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-16 13:37:04.496774342 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 39 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-16 13:37:04.496785752 	SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = 40 	char= ! bin= 00100001 hex= 0x21 int= 33
2020-04-16 13:37:04.496795236 	FINISHED test_writepci_to_parport01(void).
2020-04-16 13:37:04.496803054 	Timer 2 stop. Duration (timer start-to-stop) = 0.000656468 seconds.

=============================================================
2020-04-16 13:37:04.496816233 	Timer 3 start.
2020-04-16 13:37:04.496823904 	PARPORT02: User must have root permission to access the port.
2020-04-16 13:37:04.496831679 	SUCCESS: Set max priority level io_prio_lvl 	= 0
2020-04-16 13:37:04.496839756 	SUCCESS: Set port i/o permissions io_perm_parport02 	= 0
2020-04-16 13:37:04.496848238 	STARTED  open_fd_parport02(void).
2020-04-16 13:37:04.541937763 	SUCCESS: Open DEVICE_PARPORT_02 (/dev/lp1).
2020-04-16 13:37:04.541949589 	SUCCESS: Display file descriptor fd_parport02 	= 4
2020-04-16 13:37:04.541959574 	SUCCESS: Display BASEPORT_02 	= 0x4030
2020-04-16 13:37:04.541971912 	SUCCESS: Display PARPORT_IRQ_02 = 19
2020-04-16 13:37:04.541984549 	SUCCESS: Display CPUMAP_02 	= 0x08
2020-04-16 13:37:04.541994573 	SUCCESS: Display PERIOD_02 	= 500000 (ns)
2020-04-16 13:37:04.542005288 	SUCCESS: Display TICK_TIME_02 	= 1000000 (ns)
2020-04-16 13:37:04.542019031 	FINISHED open_fd_parport02(void).
2020-04-16 13:37:04.542028923 	STARTED  test_writepci_to_parport02(void).
2020-04-16 13:37:04.542040799 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 0 	char= S bin= 01010011 hex= 0x53 int= 83
2020-04-16 13:37:04.542053985 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 1 	char= G bin= 01000111 hex= 0x47 int= 71
2020-04-16 13:37:04.542071002 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 2 	char= I bin= 01001001 hex= 0x49 int= 73
2020-04-16 13:37:04.542083511 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 3 	char= w bin= 01110111 hex= 0x77 int= 119
2020-04-16 13:37:04.542095418 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 4 	char= k bin= 01101011 hex= 0x6b int= 107
2020-04-16 13:37:04.542107582 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 5 	char= s bin= 01110011 hex= 0x73 int= 115
2020-04-16 13:37:04.542119483 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 6 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.542134935 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 7 	char= B bin= 01000010 hex= 0x42 int= 66
2020-04-16 13:37:04.542146856 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 8 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.542158982 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 9 	char= s bin= 01110011 hex= 0x73 int= 115
2020-04-16 13:37:04.542170958 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 10 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 13:37:04.542188634 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 11 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.542201903 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 12 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.542215457 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 13 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-16 13:37:04.542227998 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 14 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.542240824 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 15 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 13:37:04.542253450 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 16 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.542266183 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 17 	char= H bin= 01001000 hex= 0x48 int= 72
2020-04-16 13:37:04.542281653 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 18 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.542294461 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 19 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.542306083 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 20 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.542322741 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 21 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.542335612 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 22 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 13:37:04.542348133 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 23 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 13:37:04.542359770 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 24 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.542372096 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 25 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.542384946 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 26 	char= N bin= 01001110 hex= 0x4e int= 78
2020-04-16 13:37:04.542397656 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 27 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.542409452 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 28 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.542421370 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 29 	char= r bin= 01110010 hex= 0x72 int= 114
2020-04-16 13:37:04.542433394 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 30 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-16 13:37:04.542445328 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 31 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-16 13:37:04.542456873 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 32 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-16 13:37:04.542469235 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 33 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-16 13:37:04.542481695 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 34 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-16 13:37:04.542494279 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 35 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-16 13:37:04.542506350 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 36 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-16 13:37:04.542518509 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 37 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-16 13:37:04.542530487 	SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = 38 	char= ! bin= 00100001 hex= 0x21 int= 33
2020-04-16 13:37:04.542539607 	FINISHED test_writepci_to_parport02(void).
2020-04-16 13:37:04.542547631 	Timer 3 stop. Duration (timer start-to-stop) = 0.045731569 seconds.

=============================================================
2020-04-16 13:37:04.542564780 	GROUP CLOSING: To make different file descriptor numbers. Otherwise, reuse.

2020-04-16 13:37:04.542581028 	STARTED  close_fd_parport01(void).
2020-04-16 13:37:04.542589531 	CHECK: Before closing file descriptor number: fd_parport01 	= 3
2020-04-16 13:37:04.542608420 	SUCCESS  closing DEVICE_PARPORT_01. Status: closed_fd_parport01 = 0
2020-04-16 13:37:04.542617914 	CHECK: After closing file descriptor number: fd_parport01 	= 3
2020-04-16 13:37:04.542627347 	FINISHED close_fd_parport01(void).

2020-04-16 13:37:04.542640482 	STARTED  close_fd_parport02(void).
2020-04-16 13:37:04.542648841 	CHECK: Before closing file descriptor number: fd_parport02 	= 4
2020-04-16 13:37:04.542664092 	SUCCESS  closing DEVICE_PARPORT_02. Status: closed_fd_parport02 = 0
2020-04-16 13:37:04.542673774 	CHECK: After closing file descriptor number: fd_parport02 	= 4
2020-04-16 13:37:04.542683606 	FINISHED close_fd_parport02(void).
=============================================================
2020-04-16 13:37:04.542697468 	Total program run duration   = 0.046777123 seconds.

2020-04-16 13:37:04.542710336 	Program ended.
2020-04-16 13:37:04.542718231 	Ending in main(), Alhamdulillah 3 times WRY.
wruslan@SGIwks-Ub1804-rt38-64b:~/apps/cpp-eclipse-wks/SGIwks-pci-to-parallel-port/Debug$


*/
// ========================================================
