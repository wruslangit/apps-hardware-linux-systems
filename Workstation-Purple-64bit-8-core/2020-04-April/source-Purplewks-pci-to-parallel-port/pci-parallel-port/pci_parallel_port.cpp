/*
 * pci_parallel_port.cpp
 *
 *  Created on: Apr 15, 2020
 *      Author: wruslan

===========================================================
*/
// ========================================================
// C-PROGRAM HEADER FILES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>      // FILE (open, read, write, close)
#include <termios.h>
#include <sched.h>
#include <signal.h>		// Signal for User interrupt Ctrl-C to stop
#include <math.h>
#include <errno.h>
#include <string.h>		// TO HANDLE strlen IN gcode . h
#include <curses.h>		// TO HANDLE getch () , wgetch ()
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <cstdlib>		// To free() memory

// WRY Date-Time stamp nanosecond display
#include "../dtstamp/dtstamp.hpp"

// ========================================================
// GLOBAL DEFINITIONS
// ========================================================
#define PERIOD		500000		// nanoseconds
#define TICK_TIME	1000000		// nanoseconds

// #define CPUMAP 	0xF  	// 16-cpus
#define CPUMAP		0x8		// 8-cpus  	(SGI-Workstation)
// #define CPUMAP	0x4		// 4-cpus	(Blue-Workstation)
/*
===========================================================
wruslan@SGIwks-Ub1804-rt38-64b:~$ dmesg
....
[   27.746411] lp: driver loaded but no devices found
[   27.894636] ppdev: user-space parallel port driver
[   28.023139] parport0: PC-style at 0x378 (0x778) [PCSPP,TRISTATE,EPP]
[   28.036690] parport0: irq 7 detected
[   28.143972] lp0: using parport0 (polling).
[   28.156786] parport_pc 0000:08:04.0: PCI->APIC IRQ transform: INT A -> IRQ 19
[   28.170000] PCI parallel port detected: 9710:9805, I/O at 0x4030(0x4028), IRQ 19
[   28.170046] parport1: PC-style at 0x4030 (0x4028), irq 19, using FIFO [PCSPP,TRISTATE,COMPAT,EPP,ECP]
[   28.291986] lp1: using parport1 (interrupt-driven).
....
wruslan@SGIwks-Ub1804-rt38-64b:~$ ls -al /dev | grep lp
crw-rw----   1 root    lp        6,   0 Apr 16 07:07 lp0
crw-rw----   1 root    lp        6,   1 Apr 16 07:07 lp1
crw-rw-r--   1 root    lp       99,   0 Apr 16 07:07 parport0
crw-rw-r--   1 root    lp       99,   1 Apr 16 07:07 parport1
wruslan@SGIwks-Ub1804-rt38-64b:~$

wruslan@SGIwks-Ub1804-rt38-64b:~$ stat /dev/lp0
  File: /dev/lp0
  Size: 0         	Blocks: 0          IO Block: 4096   character special file
Device: 6h/6d	Inode: 15702       Links: 1     Device type: 6,0
Access: (0660/crw-rw----)  Uid: (    0/    root)   Gid: (    7/      lp)
Access: 2020-04-16 07:07:57.995999641 +0800
Modify: 2020-04-16 07:07:57.995999641 +0800
Change: 2020-04-16 07:07:57.995999641 +0800
 Birth: -
wruslan@SGIwks-Ub1804-rt38-64b:~$

wruslan@SGIwks-Ub1804-rt38-64b:~$ stat /dev/parport0
  File: /dev/parport0
  Size: 0         	Blocks: 0          IO Block: 4096   character special file
Device: 6h/6d	Inode: 15703       Links: 1     Device type: 63,0
Access: (0664/crw-rw-r--)  Uid: (    0/    root)   Gid: (    7/      lp)
Access: 2020-04-16 07:07:57.999999641 +0800
Modify: 2020-04-16 07:07:57.999999641 +0800
Change: 2020-04-16 07:07:57.999999641 +0800
 Birth: -
wruslan@SGIwks-Ub1804-rt38-64b:~$

*/
// ========================================================
// FROM THE ABOVE WE GET THE 3 DEVICE PARAMETERS BELOW
// FOR THE TWO PCI PARALLEL PORTS
#define DEVICE_PARPORT_01	"/dev/lp0"
#define BASE_PARPORT_01	    0x378
#define IRQ_PARPORT_01		7

#define DEVICE_PARPORT_02	"/dev/lp1"
#define BASE_PARPORT_02	    0x4030
#define IRQ_PARPORT_02		19

// DEVICES /dev/lp0 and /dev/lp1 GLOBAL VARIABLES
// ========================================================
int  io_prio_lvl;           // I/O priority level

int  io_perm_parport01;		// I/O permissions
int  fd_parport01;			// File descriptors
int  io_perm_parport02;		// I/O permissions
int  fd_parport02;			// File descriptors

// BINARY REPRESENTATION FOR PRINTING (DISPLAY) TO SCREEN
char bin8_output[33] = {0};	// LAST CHAR IS NULL "\0"

// ========================================================
void convert_integer_to_binary8(int input_int, char *output_bin8) {
// ========================================================
    unsigned int mask8;
    mask8  = 0b10000000;

    int bitposition = 0;
    while (mask8)  {         		// Loop until MASK is empty
		bitposition++;
		if (input_int & mask8) {    // Bitwise AND => test the masked bit
		   *output_bin8 = '1'; 		// if true, binary value 1 is appended to output array
		} else {
		   *output_bin8 = '0'; 		// if false, binary value 0 is appended to output array
		}

		output_bin8++;              // next character
        mask8 >>= 1;            	// shift the mask variable 1 bit to the right
    } // End while(..)

    *output_bin8 = 0;           	// add the trailing null
}

// ========================================================
void check_io_priority_level(void) {
// ========================================================
	if (io_prio_lvl != 0) {
		DTStamp();
		printf("ERROR  : Set max priority level io_prio_lvl \t= %d\n", io_prio_lvl);
		perror("io_prio_lvl");
	} else {
		DTStamp();
		printf("SUCCESS: Set max priority level io_prio_lvl \t= %d\n", io_prio_lvl);
	}
}

// ========================================================
void check_io_permission_parport01(void) {
// ========================================================
    if (io_perm_parport01 != 0) {
    	DTStamp();
		printf("ERROR  : Set port i/o permissions io_perm_parport01 \t= %d\n", io_perm_parport01);
		perror("io_perm_parport01");
    } else {
    	DTStamp();
    	printf("SUCCESS: Set port i/o permissions io_perm_parport01 \t= %d\n", io_perm_parport01);
    }
}
// ========================================================
void check_io_permission_parport02(void) {
// ========================================================
    if (io_perm_parport02 != 0) {
    	DTStamp();
		printf("ERROR  : Set port i/o permissions io_perm_parport02 \t= %d\n", io_perm_parport02);
		perror("io_perm_parport01");
    } else {
    	DTStamp();
    	printf("SUCCESS: Set port i/o permissions io_perm_parport02 \t= %d\n", io_perm_parport02);
    }
}
// ========================================================
void open_fd_parport01(void) {
// ========================================================
DTStamp(); printf("STARTED  open_fd_parport01(void).\n");

/*
open: Returns file descriptor used (positive integer), -1 upon failure
flags: O_RDONLY: read only, O_WRONLY: write only, O_RDWR: read and write, O_CREAT: create file if it doesn’t exist, O_EXCL: prevent creation if it already exists
*/

    fd_parport01 = open(DEVICE_PARPORT_01, O_RDWR | O_NOCTTY | O_NDELAY | O_CREAT);
	if(fd_parport01 == -1) {
		DTStamp(); printf("ERROR: Cannot open DEVICE_PARPORT_01 (/dev/lp0).\n");
		DTStamp(); printf("ERROR: Must run as root with $ sudo ./XXX \n");
		perror("fd_parport01");
		exit(1);
	} else {
		DTStamp();
		printf("SUCCESS: Open DEVICE_PARPORT_01 (/dev/lp0).\n");
		DTStamp();
		printf("SUCCESS: Display file descriptor fd_parport01 \t= %d \n", fd_parport01);
	}

	// Display details of DEVICE_PARPORT_01
	DTStamp(); printf("SUCCESS: Display BASEPORT_01 \t= 0x%02X\n", BASE_PARPORT_01);
	DTStamp(); printf("SUCCESS: Display PARPORT_IRQ_01 = %d\n", IRQ_PARPORT_01);

    DTStamp(); printf("SUCCESS: Display CPUMAP_01 \t= 0x%02X\n", CPUMAP);
	DTStamp(); printf("SUCCESS: Display PERIOD_01 \t= %d (ns)\n", PERIOD);
    DTStamp(); printf("SUCCESS: Display TICK_TIME_01 \t= %d (ns)\n", TICK_TIME);

DTStamp(); printf("FINISHED open_fd_parport01(void).\n");
}

// ========================================================
void open_fd_parport02(void) {
// ========================================================
DTStamp(); printf("STARTED  open_fd_parport02(void).\n");

	fd_parport02 = open(DEVICE_PARPORT_02, O_RDWR | O_NOCTTY | O_NDELAY | O_CREAT);
	if(fd_parport02 == -1) {
		DTStamp(); printf("ERROR: Cannot open DEVICE_PARPORT_02 (/dev/lp1).\n");
		DTStamp(); printf("ERROR: Must run as root with $ sudo ./XXX \n");
		perror("fd_parport02");
		exit(1);
	} else {
		DTStamp();
		printf("SUCCESS: Open DEVICE_PARPORT_02 (/dev/lp1).\n");
		DTStamp();
		printf("SUCCESS: Display file descriptor fd_parport02 \t= %d \n", fd_parport02);
	}

	// Display details of DEVICE_PARPORT_02
	DTStamp(); printf("SUCCESS: Display BASEPORT_02 \t= 0x%02X\n", BASE_PARPORT_02);
	DTStamp(); printf("SUCCESS: Display PARPORT_IRQ_02 = %d\n", IRQ_PARPORT_02);

	DTStamp(); printf("SUCCESS: Display CPUMAP_02 \t= 0x%02X\n", CPUMAP);
	DTStamp(); printf("SUCCESS: Display PERIOD_02 \t= %d (ns)\n", PERIOD);
	DTStamp(); printf("SUCCESS: Display TICK_TIME_02 \t= %d (ns)\n", TICK_TIME);

DTStamp(); printf("FINISHED open_fd_parport02(void).\n");
}

// ========================================================
void test_writepci_to_parport01(void) {
// ========================================================
DTStamp(); printf("STARTED  test_writepci_to_parport01(void).\n");

	// Test write loop with buffered data
	// PERFORM WRITE LOOP FOR ELECTRICAL PULSE OUTPUTS
	int i;
	int intToWrite = 0;
	char TheChar[] = "SGIwks Alhamdulillah Hirrabil Alamin WRY!";
	int str_length = strlen(TheChar);

	for (i = 0; i < str_length; i++) {

		// GRAB INTEGER TO WRITE (8-BITS) TO DEVICE
		intToWrite = TheChar[i];
		char data_uchar = (char)intToWrite;
		if (fd_parport01 != -1) {

			convert_integer_to_binary8(intToWrite, bin8_output);
			write(fd_parport01, (const void *)(long)data_uchar, 1);

			DTStamp();
			printf("SUCCESS: write(fd_parport01, (const void *)(long)TheChar[i],1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
		} else {
			DTStamp();
			printf("FAILED:  write(fd_parport01, (const void *)(long)TheChar[i],1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
		}

	} // End for..loop

DTStamp(); printf("FINISHED test_writepci_to_parport01(void).\n");
}

// ========================================================
void test_writepci_to_parport02(void) {
// ========================================================
DTStamp(); printf("STARTED  test_writepci_to_parport02(void).\n");

// Test write loop with buffered data
// PERFORM WRITE LOOP FOR ELECTRICAL PULSE OUTPUTS
int i;
int intToWrite = 0;
char TheChar[] = "SGIwks Bismillah Hirrahma Nirrahim WRY!";
int str_length = strlen(TheChar);

for (i = 0; i < str_length; i++) {

	// GRAB INTEGER TO WRITE (8-BITS) TO DEVICE
	intToWrite = TheChar[i];
	char data_uchar = (char)intToWrite;
	if (fd_parport02 != -1) {

		convert_integer_to_binary8(intToWrite, bin8_output);
		write(fd_parport02, (const void *)(long)data_uchar, 1);

		DTStamp();
		printf("SUCCESS: write(fd_parport02, (const void *)(long)TheChar[i],1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
	} else {
		DTStamp();
		printf("FAILED:  write(fd_parport02, (const void *)(long)TheChar[i],1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
	}
} // End for..loop


DTStamp(); printf("FINISHED test_writepci_to_parport02(void).\n");
}
// ========================================================
void close_fd_parport01(void) {
// ========================================================
printf("\n");
DTStamp(); printf("STARTED  close_fd_parport01(void).\n");

DTStamp();
printf("CHECK: Before closing file descriptor number: fd_parport01 \t= %d \n", fd_parport01);

int closed_fd_parport01 = close(fd_parport01);
if (closed_fd_parport01 == 0) {
	DTStamp();
	printf("SUCCESS  closing DEVICE_PARPORT_01. Status: closed_fd_parport01 = %d \n", closed_fd_parport01);
} else {
	DTStamp();
	printf("ERROR:   closing DEVICE_PARPORT_01. Status: closed_fd_parport01 = %d \n", closed_fd_parport01);
}

DTStamp();
printf("CHECK: After closing file descriptor number: fd_parport01 \t= %d \n", fd_parport01);


DTStamp(); printf("FINISHED close_fd_parport01(void).\n");
}
// ========================================================
void close_fd_parport02(void) {
// ========================================================
printf("\n");
DTStamp(); printf("STARTED  close_fd_parport02(void).\n");

DTStamp();
printf("CHECK: Before closing file descriptor number: fd_parport02 \t= %d \n", fd_parport02);

int closed_fd_parport02 = close(fd_parport02);
if (closed_fd_parport02 == 0) {
	DTStamp();
	printf("SUCCESS  closing DEVICE_PARPORT_02. Status: closed_fd_parport02 = %d \n", closed_fd_parport02);
} else {
	DTStamp();
	printf("ERROR:   closing DEVICE_PARPORT_02. Status: closed_fd_parport02 = %d \n", closed_fd_parport02);
}

DTStamp();
printf("CHECK: After closing file descriptor number: fd_parport02 \t= %d \n", fd_parport02);

DTStamp(); printf("FINISHED close_fd_parport02(void).\n");
}
// ========================================================
/*

*/

// ========================================================
