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


#define UART_LSR_TEMT   0x40  	//!< Transmitter serial register empty
#define UART_LSR_THRE   0x20  	//!< Transmitter holding register empty

#define UART_FCR_FE     0x01    /* FIFO Enable */

#define TRACE (*(unsigned char *)0x40000000)


  //! UART registers.
  //! - rbr: R: Rx buffer,		      
  //! - thr: R: Tx hold reg,		      
  //! - ier: R/W: Interrupt Enable Register   
  //! - iir: R: Interrupt ID Register	      
  //! - lcr: R/W: Line Control Register	      
  //! - mcr: W: Modem Control Register	      
  //! - lsr: R: Line Status Register	      
  //! - msr: R: Modem Status Register	      
  //! - scr: R/W: Scratch Register            
  //! - dl:  R/W: Divisor Latch

  typedef struct {
    // volatile uint32_t   rbr;		// R: Rx buffer,
    volatile uint32_t   thr;		// W: Tx hold reg,
    volatile uint32_t   ier;		// R/W: Interrupt Enable Register
    //volatile uint32_t   iir;		// R: Interrupt ID Register
    //volatile uint32_t   lcr;		// R/W: Line Control RegisWASter
    //volatile uint32_t   mcr;		// W: Modem Control Register
    //volatile uint32_t   lsr;		// R: Line Status Register
    //volatile uint32_t   msr;		// R: Modem Status Register
    //volatile uint32_t   scr;		// R/W: Scratch Register            
    //volatile uint32_t    dl;		// R/W: Divisor Latch
  } uart_regs;

#define UART_REGISTERS ((uart_regs *) UART_REGISTERS_MEMORY_ADDRESS)


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

	void run();

	sc_core::sc_event txReceived; /**< event for when transmit buffer is written*/

};

#endif
