/*!
 \file Memory.cpp
 \brief Basic TLM-2 memory model
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "InternalMemory.h"

SC_HAS_PROCESS(InternalMemory);
InternalMemory::InternalMemory(sc_core::sc_module_name const &name, std::string const &filename) :
		sc_module(name), socket("socket"), LATENCY(sc_core::SC_ZERO_TIME) {
	// Register callbacks for incoming interface method calls
	socket.register_b_transport(this, &InternalMemory::b_transport);

	mem = new uint8_t[SIZE];
	//memset(mem, 0, SIZE*sizeof(uint8_t));

	memory_offset = PROJECT_ADDRESS;

	log = Log::getInstance();
	log->SC_log(Log::INFO) << "Using file: " << filename << std::endl;
}

InternalMemory::InternalMemory(sc_core::sc_module_name const& name) :
		sc_module(name), socket("socket"), LATENCY(sc_core::SC_ZERO_TIME) {
	socket.register_b_transport(this, &InternalMemory::b_transport);
	memory_offset = PROJECT_ADDRESS;

	mem = new uint8_t[SIZE];

	log = Log::getInstance();
	log->SC_log(Log::INFO) << "Memory instantiated without file" << std::endl;
}

InternalMemory::~InternalMemory() {
	delete[] mem;
}

void InternalMemory::b_transport(tlm::tlm_generic_payload &trans,
		sc_core::sc_time &delay) {
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 adr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();
	unsigned char *byt = trans.get_byte_enable_ptr();
	unsigned int wid = trans.get_streaming_width();

	adr = adr - memory_offset;

	// Obliged to check address range and check for unsupported features,
	//   i.e. byte enables, streaming, and bursts
	// Can ignore extensions

	// *********************************************
	// Generate the appropriate error response
	// *********************************************
	if (adr >= sc_dt::uint64(SIZE)) {
		trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
		return;
	}
	if (byt != nullptr) {
		trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
		return;
	}
	if (len > 4 || wid < len) {
		trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
		return;
	}

  // std::cout << "I've been accessed at address: " << std::hex << adr << std::endl;

	// Obliged to implement read and write commands
	if (cmd == tlm::TLM_READ_COMMAND)
		memcpy(ptr, &mem[adr], len);
	else if (cmd == tlm::TLM_WRITE_COMMAND)
		memcpy(&mem[adr], ptr, len);

	// Illustrates that b_transport may block
	//sc_core::wait(delay);

	// Reset timing annotation after waiting
	delay = sc_core::SC_ZERO_TIME;

	// *********************************************
	// Set DMI hint to indicated that DMI is supported
	// *********************************************

	if (memory_offset == 0) {
		trans.set_dmi_allowed(true);
	} else {
		trans.set_dmi_allowed(false);
	}

	// Obliged to set response status to indicate successful completion
	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}