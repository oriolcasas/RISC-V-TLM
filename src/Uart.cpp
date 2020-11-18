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

	registerSetup();
}

void Uart::b_transport(tlm::tlm_generic_payload &trans,
		sc_core::sc_time &delay) {

	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 addr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();

	uint32_t aux_value = 0;

	if (cmd == tlm::TLM_WRITE_COMMAND) {
		memcpy(&aux_value, ptr, len);
		switch (addr) {
		case UART_REGISTER_A_MEMORY_ADDRESS_LO:
			m_registerA.range(31, 0) = aux_value;
			break;
		case UART_REGISTER_A_MEMORY_ADDRESS_HI:
			m_registerA.range(63, 32) = aux_value;
			break;
		case UART_REGISTER_B_MEMORY_ADDRESS_LO:
			m_registerB.range(31, 0) = aux_value;
			break;
		case UART_REGISTER_B_MEMORY_ADDRESS_HI:
			m_registerB.range(63, 32) = aux_value;
			break;
		}

	} else { // TLM_READ_COMMAND
		switch (addr) {
		case UART_REGISTER_A_MEMORY_ADDRESS_LO:
			aux_value = m_registerA.range(31, 0);
			break;
		case UART_REGISTER_A_MEMORY_ADDRESS_HI:
			aux_value = m_registerA.range(63, 32);
			break;
		case UART_REGISTER_B_MEMORY_ADDRESS_LO:
			aux_value = m_registerB.range(31, 0);
			break;
		case UART_REGISTER_B_MEMORY_ADDRESS_HI:
			aux_value = m_registerB.range(63, 32);
			break;
		}
		memcpy(ptr, &aux_value, len);
	}

	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

void Uart::registerSetup(void) {

	//TO DO
	//Set Registers with specific values in hexadecimal
	m_registerA |= 0X0000000000000000;
	m_registerB |= 0x0000000000000000;

}




