/*!
 \file Uart.cpp
 \brief Basic TLM-2 UART module
 \author Oriol Casas - Marius Montón
 \date October 2020
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Uart.h"

SC_HAS_PROCESS(Uart);
Uart::Uart(sc_core::sc_module_name name) :
		sc_module(name), socket("uart_socket") {

	socket.register_b_transport(this, &Uart::b_transport);


	SC_THREAD(run);
}

int _write(int file, const char *ptr, int len) {
  int x;

  for (x = 0; x < len; x++) {
    TRACE =  *ptr++;
  }

  return (len);
}

void Uart::b_transport(tlm::tlm_generic_payload &trans,
		sc_core::sc_time &delay) {

	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 addr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();

	uint32_t aux_value = 0;
	std::cout << "START TRANSMISSION" << '\n';
	if (cmd == tlm::TLM_WRITE_COMMAND) {
		memcpy(&aux_value, ptr, len);
		switch (addr) {
		case UART_REGISTERS_MEMORY_ADDRESS:
		    std::cout << "Data in address: " << std::hex << addr << " to be written: " << aux_value << '\n';
		    my_regs.thr = aux_value;
			txReceived.notify();			// Tell the thread
			break;
		}

	} else { // TLM_READ_COMMAND
		switch (addr) {
		case UART_REGISTERS_MEMORY_ADDRESS:
		  std::cout << "READ" << '\n';
			aux_value = my_regs.rbr; //MODIFY REGISTER LATER
			break;
		}
		//memcpy(ptr, &aux_value, len);


	}

	std::cout << "END TRANSMISSION" << '\n';
	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}


void Uart::run() {

	int i = 0;
	while (true){

		//If interrupt enabled
		//UART_REGISTERS->ier == 0x00;

		wait( txReceived );			// Wait for when data is written in the bus
		
		i++;
		//write to terminal
		//printf("Data written: 0x%08lX\n", my_regs.thr);
		printf("%d. Data written:%c\n", i, my_regs.thr);
	}
}
