/*
 * random_int_dbl.cpp
 * Version: 1.0
 * Created on: Mar 20, 2020
 * Author: wruslan
 */

#include <unistd.h>
#include <time.h>       // For timespec, time()
#include <stdio.h>      // For printf()
#include <stdlib.h>     // For srand() and rand(), scanf(),

// FUNCTION GENERATE INTEGER RANDOM NUMBER
// ========================================================
long int random_integer(long int min, long int max) {
// ========================================================
	// srand((unsigned)time(NULL));

    if (max <= min) {
        printf("ERROR ON INTEGER: max cannot be equal or less than min.! \n");
        exit(1);
    } else {
        int range = (max - min);
        int offset_int = (rand() % range); // Random integer between 0 and (range-1)
        // printf("DEBUG: range = %d offset 0 to max =  %d \n", range, offset0);
    return (min + offset_int);
    }
}

// ========================================================
void display_random_integers(long int count, long int min, long int max) {
// ========================================================

	for (long int j = 0; j < count; j++) {
		    printf("j = %ld Uniform random_integer between (%ld, %ld) = %ld \n", \
		   		j, min, max, random_integer(min, max));
	}

	printf("\n");
	printf("SUCCESS: Above are the %ld generated uniform random integers between (%ld, %ld). \n\n", count, min, max);

}

// CHECK RANDOMNESS OF INTEGER RANDOM NUMBERS
// ========================================================
void check_randomness_of_integers(int bins, long int count, long int min, long int max) {
// ========================================================
	srand((unsigned)time(NULL));

	if (max <= min) {
	        printf("\n***** ERROR ON INTEGER: Value of max cannot be equal or less than min.! \n");
	        exit(1);
	}

	if (bins > (max-min)) {
			printf("\n***** ERROR ON BINS: Integer bins cannot be greater than number range.! \n");
			exit(1);
	}

	// ====================================================
	// Determine the lower and upper boundary for each bin
	// Initialize counts in each bin to zero
	int loopnum;
	long int bin_count[bins+1];
	for (loopnum = 0; loopnum <= bins+1; loopnum++) {
		 bin_count[loopnum] = 0;
	}

	// From input range, calculate bin_width (+1 for fractional part of integer division)
	long int bin_width = ((max - min)/bins) + 1;
	// printf("bin_width = %ld \n", bin_width);

	// Using bin_width, set boundaries for each bin
	long int bin_boundary[bins+1];
	bin_boundary[0] = min;
	// printf("bin_boundary[0] = %ld \n", bin_boundary[0]);
	for (loopnum = 1; loopnum <= bins; loopnum++) {
		bin_boundary[loopnum] = bin_boundary[loopnum-1] + bin_width;
		// printf("bin_boundary[%d] = %ld \n", loopnum, bin_boundary[loopnum]);
	}
	bin_boundary[bins+1] = max;
	// printf("bin_boundary[%d] = %ld \n", bins+1, bin_boundary[bins+1]);

	// ====================================================
	// Generate a random integer, identify the_bin and increment bin_count
	long int rand_int;
	int the_bin;

	// Generate the total number (count) of random numbers
	for (loopnum = 1; loopnum <= count; loopnum++) {

		// Get a random integer
		rand_int = random_integer(min, max);
		// printf("loopnum = %d rand_int = %ld \n", loopnum, rand_int);

		// Find the_bin and increment bin_count[the_bin]
		for (the_bin = 0; the_bin <= bins+1; the_bin++) {

			// LOWER BOUNDARY = BIN INCLUSIVE
			if (rand_int == bin_boundary[the_bin] ) {
				bin_count[the_bin] = bin_count[the_bin] + 1;
			} else if ((rand_int > bin_boundary[the_bin]) && (rand_int < bin_boundary[the_bin+1])) {
				bin_count[the_bin] = bin_count[the_bin] + 1;
			} // end (if .. else if ...)

		} // end for(the_bin)
	} // end for(loopnum)

	// ====================================================
    // Check to ensure all random numbers are accounted for in some bin
	long int check_bin_count = 0;
	for (loopnum = 0; loopnum < bins; loopnum++) {

		printf("Random integers in range[%ld, %ld) = \t", bin_boundary[loopnum], bin_boundary[loopnum+1]);
		printf("bin_count[%d] = %ld \t", loopnum, bin_count[loopnum]);

		check_bin_count = check_bin_count + bin_count[loopnum];
		printf("cumulative check_bin_count = %ld \n", check_bin_count);
	}

	if (check_bin_count == count) {
		printf("\nSUCCESS: Above are the %ld uniform random integers in the range(%ld, %ld) accounted for in the %d bins. \n\n", check_bin_count, min, max, bins);
	} else {
		printf("\nERROR: Some uniform random integers are not accounted for in the bins. \n\n");
	}

}

// FUNCTION GENERATE DOUBLE RANDOM NUMBER
// =========================================================
double random_double(double min, double max) {
// =========================================================
	// srand((unsigned)time(NULL));

	if (max <= min) {
        printf("ERROR ON DOUBLE: max cannot be equal or less than min.! \n");
        exit(1);
    } else {
        double range = (max - min);
        double div = (RAND_MAX / range);
        double offset_dbl = (rand() / div);
        // printf("DEBUG: range = %f offset 0 to max =  %f \n", range, offset);
    return min + (offset_dbl);
    }
}

// ========================================================
void display_random_doubles(long int count, double min, double max) {
// ========================================================

	for (long int j = 0; j < count; j++) {
		    printf("j = %ld Uniform random_doubles between (%f, %f) = %f \n", \
		   		j, min, max, random_double(min, max));
	}

	printf("\nSUCCESS: Above are the %ld generated uniform random doubles between (%f, %f). \n\n", count, min, max);

}

// ========================================================
void check_randomness_of_doubles(int bins, long int count, double min, double max) {
// ========================================================
	srand((unsigned)time(NULL));

	if (max <= min) {
	        printf("\n***** ERROR ON DOUBLE: Value of max cannot be equal or less than min.! \n");
	        exit(1);
	}

	if (bins > (max-min)) {
			printf("\n***** ERROR ON BINS: Integer bins cannot be greater than number range.! \n");
			exit(1);
	}

	// ====================================================
	// Determine the lower and upper boundary for each bin
	// Initialize counts in each bin to zero
	int loopnum;
	long int bin_count[bins+1];
	for (loopnum = 0; loopnum <= bins+1; loopnum++) {
		 bin_count[loopnum] = 0;
	}

	// From input range, calculate bin_width
	double bin_width = (max - min)/bins;
	// printf("bin_width = %f\n", bin_width);

	// Using bin_width, set boundaries for each bin
	double bin_boundary[bins+1];
	bin_boundary[0] = min;
	// printf("bin_boundary[0] = %f \n", bin_boundary[0]);
	for (loopnum = 1; loopnum <= bins; loopnum++) {
		bin_boundary[loopnum] = bin_boundary[loopnum-1] + bin_width;
		//printf("bin_boundary[%d] = %f \n", loopnum, bin_boundary[loopnum]);
	}
	bin_boundary[bins+1] = max;
	// printf("bin_boundary[%d] = %f \n", bins+1, bin_boundary[bins+1]);

	// ====================================================
	// Generate a random double, identify the_bin and increment bin_count
	double rand_dbl;
	int the_bin;

	// Generate the total number (count) of random numbers
	for (loopnum = 1; loopnum <= count; loopnum++) {

		// Get a random integer
		rand_dbl = random_double(min, max);
		// printf("loopnum = %d rand_dbl = %f \n", loopnum, rand_dbl);

		// Find the_bin and increment bin_count[the_bin]
		for (the_bin = 0; the_bin <= bins+1; the_bin++) {

			// LOWER BOUNDARY = BIN INCLUSIVE
			if (rand_dbl == bin_boundary[the_bin] ) {
				bin_count[the_bin] = bin_count[the_bin] + 1;
			} else if ((rand_dbl > bin_boundary[the_bin]) && (rand_dbl < bin_boundary[the_bin+1])) {
				bin_count[the_bin] = bin_count[the_bin] + 1;
			} // end (if .. else if ...)

		} // end for(the_bin)
	} // end for(loopnum)

	// ====================================================
    // Check to ensure all random numbers are accounted for in some bin
	long int check_bin_count = 0;
	for (loopnum = 0; loopnum < bins; loopnum++) {

		printf("Random doubles in range[%f, %f) = \t", bin_boundary[loopnum], bin_boundary[loopnum+1]);
		printf("bin_count[%d] = %ld \t", loopnum, bin_count[loopnum]);

		check_bin_count = check_bin_count + bin_count[loopnum];
		printf("cumulative check_bin_count = %ld \n", check_bin_count);
	}

	if (check_bin_count == count) {
		printf("\nSUCCESS: Above are the %ld uniform random doubles in the range(%f, %f) accounted for in the %d bins. \n\n", check_bin_count, min, max, bins);
	} else {
		printf("\nERROR: Some uniform random doubles are not accounted for in the bins. \n\n");
	}

}

// ========================================================
// MISC EXAMPLE USAGE
// ========================================================
/*
int     i, j, k;
int     int_count, dbl_count;
int     int_min, int_max;
double  dbl_min, dmin, dbl_max, dmax;

// INITIALIZE RANDOM NUMBER GENERATOR
srand(time(NULL));

// scanf("%d", &int_min); // Scan an integer as a signed decimal number.
// scanf("%f", &dbl_min); // Scan an double  as a signed decimal number.

// DISPLAY INTEGER RANDOM NUMBERS
// ==================================
printf("\nEnter an integer for minimum value, int_min = ");
scanf("%d", &int_min);

printf("Enter an integer for maximum value, int_max = ");
scanf("%d", &int_max);

printf("Enter number of random integers to generate (max = 1000) = ");
scanf("%d", &int_count);

for (i = 0; i < int_count; i++) {
    printf("i = %d Uniform random_integer between(%d, %d) = %d \n", i, int_min, int_max, random_integer(int_min, int_max));
}

// DISPLAY DOUBLE RANDOM NUMBERS
// ==================================

printf("\nEnter a double for minimum dbl_min: ");
scanf("%lf", &dbl_min);

printf("Enter a double for maximum dbl_max: ");
scanf("%lf", &dbl_max);

printf("Enter number of random doubles to generate (max = 1000) = ");
scanf("%d", &dbl_count);

for (i = 0; i < dbl_count; i++) {
    printf("i = %d Uniform random_double between ( %f, %f) = %16.9lf \n", i, dbl_min, dbl_max, random_double(dbl_min, dbl_max));
}

*/
// ========================================================







