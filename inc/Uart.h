/*!
 \file Uart.h
 \brief Basic TLM-2 UART module
 \author Oriol Casas - Marius Montón
 \date October 2020
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __Uart_H__
#define __Uart_H__

#include <iostream>
#include <fstream>

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

#include "BusCtrl.h"

/**
 * @brief Simple Registers peripheral
 *
 * This peripheral reads/writes any character from/to a specific register
 */
class Uart: sc_core::sc_module {
public:

	/**
	 * @brief Constructor
	 * @param name Module name
	 */
	Uart(sc_core::sc_module_name name);


	/**
	 * @brief Bus socket
	 */
	tlm_utils::simple_target_socket<Uart> socket;

	/**
	 *
	 * @brief TLM-2.0 socket implementation
	 * @param trans TLM-2.0 transaction
	 * @param delay transaction delay time
	 */
	virtual void b_transport(tlm::tlm_generic_payload &trans,
			sc_core::sc_time &delay);


	/**
	 * @brief Destructor
	 */
	// ~Uart(); IS IT NEEDED?

private:

	void registerSetup(void);

	sc_dt::sc_uint<64> m_registerA; /**< memory_mapped register A*/
	sc_dt::sc_uint<64> m_registerB; /**< memory_mapped register B */

};

#endif
