/*
 * random_int_dbl.hpp
 *
 *  Created on: Mar 20, 2020
 *      Author: wruslan
 */

#ifndef RANDOM_INT_DBL_HPP_
#define RANDOM_INT_DBL_HPP_

long int random_integer(long int min, long int max);
void 	 display_random_integers(long int count, long int min, long int max);
void 	 check_randomness_of_integers(int bins, long int count, long int min, long int max);

double 	 random_double(double min, double max);
void 	 display_random_doubles(long int count, double min, double max);
void 	 check_randomness_of_doubles(int bins, long int count, double min, double max);

#endif /* RANDOM_INT_DBL_HPP_ */
