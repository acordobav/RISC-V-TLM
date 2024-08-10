/*!
 \file InternalMemory.h
 \brief Basic TLM-2 memory model
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __INTERNALMEMORY_H__
#define __INTERNALMEMORY_H__

#include <iostream>
#include <fstream>

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

#include "Log.h"
#include "ProjectAddress.h"

/**
 * @brief Basic TLM-2 memory
 */
class InternalMemory: sc_core::sc_module {
public:
	// TLM-2 socket, defaults to 32-bits wide, base protocol
	tlm_utils::simple_target_socket<InternalMemory> socket;

	//enum { SIZE = 0x90000000  };
	enum {
		SIZE = 0x10000000
	};
	const sc_core::sc_time LATENCY;

	InternalMemory(sc_core::sc_module_name const &name, std::string const &filename);
	InternalMemory(const sc_core::sc_module_name& name);

	~InternalMemory(void);

	// TLM-2 blocking transport method
	virtual void b_transport(tlm::tlm_generic_payload &trans,
			sc_core::sc_time &delay);

private:

	/**
	 * @brief Memory array in bytes
	 */
	uint8_t *mem;

	/**
	 * @brief Log class
	 */
	Log *log;

	uint32_t memory_offset;

};
#endif /* __INTERNALMEMORY_H__ */
