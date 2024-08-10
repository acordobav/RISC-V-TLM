/*!
 \file ProjectAddress.h
 \brief Declare the SystemC register interface address
 \author Arturo Cordoba
 \date August 2024
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PROJECT_ADDRESS__H
#define PROJECT_ADDRESS__H

// Offset in which the project address starts
#define PROJECT_ADDRESS 0x50000000

// Size assigned to the project address space
#define PROJECT_ADDRESS_SIZE 0x10000000

// End address of the project space
#define PROJECT_ADDRESS_END (PROJECT_ADDRESS + PROJECT_ADDRESS_SIZE)

#endif
