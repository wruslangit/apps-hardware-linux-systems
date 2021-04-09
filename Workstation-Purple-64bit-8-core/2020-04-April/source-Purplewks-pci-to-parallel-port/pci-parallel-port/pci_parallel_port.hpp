/*
 * pci_parallel_port.hpp
 *
 *  Created on: Apr 15, 2020
 *      Author: wruslan
 */

#ifndef PCI_PARALLEL_PORT_HPP_
#define PCI_PARALLEL_PORT_HPP_

void convert_integer_to_binary8(int input_int, char *output_bin8);

void check_io_priority_level(void);

void check_io_permission_parport01(void);
void open_fd_parport01(void);
void test_writepci_to_parport01(void);
void close_fd_parport01(void);

void check_io_permission_parport02(void);
void open_fd_parport02(void);
void test_writepci_to_parport02(void);
void close_fd_parport02(void);

#endif /* PCI_PARALLEL_PORT_HPP_ */
