/*!
 \file Simulator.cpp
 \brief Top level simulation entity
 \author Marius Monton
 \date September 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include <csignal>

#include <unistd.h>

#include "CPU.h"
#include "Memory.h"
#include "BusCtrl.h"
#include "Trace.h"
#include "Timer.h"
#include "Uart.h"

std::string filename;

/**
 * @class Simulator
 * This class instantiates all necessary modules, connects its ports and starts
 * the simulation.
 *
 * @brief Top simulation entity
 */
SC_MODULE(Simulator) {
	CPU *cpuA;

	Memory *MainMemory;
	BusCtrl *Bus;
	Trace *trace;
	Timer *timer;
	Uart *uart;

	uint32_t start_PC;

	SC_CTOR(Simulator) {
		MainMemory = new Memory("Main_Memory", filename);
		start_PC = MainMemory->getPCfromHEX();

		cpuA = new CPU("cpuA", start_PC);

		Bus = new BusCtrl("BusCtrl");
		trace = new Trace("Trace");
		timer = new Timer("Timer");
		uart = new Uart("Uart");

		cpuA->instr_bus(Bus->cpu_instr_socket);
		cpuA->mem_intf->data_bus.bind(Bus->cpu_data_socket);

		Bus->memory_socket.bind(MainMemory->socket);
		Bus->trace_socket.bind(trace->socket);
		Bus->timer_socket.bind(timer->socket);

		Bus->uart_socket.bind(uart->socket);

		//timer->timer_irq.bind(IRQ);
		// cpu->interrupt.bind(IRQ);
		timer->irq_line.bind(cpuA->irq_line_socket);
	}

	~Simulator() {
		delete MainMemory;
		delete cpuA;
		delete Bus;
		delete trace;
		delete timer;
		delete uart;
	}
};

Simulator *top;

void intHandler(int dummy) {
	delete top;
	//sc_stop();
	exit(-1);
}

void process_arguments(int argc, char *argv[]) {

	int c;
	int debug_level;
	Log *log;

	log = Log::getInstance();
	log->setLogLevel(Log::ERROR);
	while ((c = getopt(argc, argv, "D:f:?")) != -1) {
		switch (c) {
		case 'D':
			debug_level = std::atoi(optarg);

			switch (debug_level) {
			case 3:
				log->setLogLevel(Log::INFO);
				break;
			case 2:
				log->setLogLevel(Log::WARNING);
				break;
			case 1:
				log->setLogLevel(Log::DEBUG);
				break;
			case 0:
				log->setLogLevel(Log::ERROR);
				break;
			default:
				log->setLogLevel(Log::INFO);
				break;
			}
			break;
		case 'f':
			filename = std::string(optarg);
			break;
		case '?':
			std::cout << "Call ./RISCV_TLM -D <debuglevel> (0..3) filename.hex"
					<< std::endl;
			break;
		}
	}

	if (filename.empty()) {
		filename = std::string(argv[optind]);
	}
}

int sc_main(int argc, char *argv[]) {

	/* Capture Ctrl+C and finish the simulation */
	std::signal(SIGINT, intHandler);

	/* SystemC time resolution set to 1 ns*/
	sc_core::sc_set_time_resolution(1, sc_core::SC_NS);

	/* Parse and process program arguments. -f is mandatory */
	process_arguments(argc, argv);

	top = new Simulator("top");
	sc_core::sc_start();

	std::cout << "Press Enter to finish" << std::endl;
	std::cin.ignore();

	// call all destructors, clean exit.
	delete top;

	return 0;
}
