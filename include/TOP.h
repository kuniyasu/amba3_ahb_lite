/*
 * TOP.h
 *
 *  Created on: 2013/12/31
 *      Author: Kuniyasu
 */

#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>

#include "amba3_ahb_lite_if.h"

#define ioMode TLM2LT
//#define ioMode PIN


class InitiatorDUT:public sc_module{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	ahb3_lite_port<32U,32U,ioMode> port;

	SC_HAS_PROCESS(InitiatorDUT);
	InitiatorDUT(const sc_module_name name):sc_module(name),clk("clk"),nrst("nrst"),port("i_port"){
		port.pclk(clk);
		port.nreset(nrst);
		end_module();
	}
};

class TargetDUT:public sc_module, public ahb3_lite_interface<32U,32U>{
public:
	sc_in<bool> clk;
	sc_in<bool> nrst;

	ahb3_lite_export<32U,32U,ioMode> ex_port;

	SC_HAS_PROCESS(TargetDUT);
	TargetDUT(const sc_module_name name):sc_module(name),clk("clk"),nrst("nrst"),ex_port("cb"){
		ex_port.pclk(clk);
		ex_port.nreset(nrst);

		ex_port.bind(*this);
		end_module();
	}

	typedef ahb3_lite_interface<32U,32U> if_type;
	typedef if_type::data_type    data_type;
	typedef if_type::strb_type 	  strb_type;
	typedef if_type::address_type address_type;
	typedef if_type::prot_type 	  prot_type;

	virtual void apb_reset(){}
	virtual bool apb_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		return false;
	}

	virtual bool  apb_read(const prot_type& prot, const address_type& ad, data_type& dt){
		return false;
	}
};


class TOP : public sc_module{
public:
	sc_clock clk;
	sc_signal<bool> nrst;

	InitiatorDUT initiatorDUT;
	TargetDUT targetDUT;
	ahb3_lite_simple_bus<32U,32U,ioMode> bus;

	SC_HAS_PROCESS(TOP);
	TOP(const sc_module_name name):sc_module(name),
		clk("CLK", 25, SC_NS, 0.5, 5, SC_NS, true ),nrst("nrst"),
		initiatorDUT("initiatorDUT"),
		targetDUT("targetDUT"),
		bus("bus"){

		initiatorDUT.clk(clk);
		initiatorDUT.nrst(nrst);
		initiatorDUT.port(bus.initiator_port);

		targetDUT.clk(clk);
		targetDUT.nrst(nrst);
		targetDUT.ex_port(bus.target_port);

		SC_THREAD(timeout_thread);
		end_module();
	}

	void timeout_thread(){
		nrst = false;
		wait(100,SC_NS);

		nrst = true;
		wait(10,SC_MS);

		sc_stop();
	}
};


#endif /* TOP_H_ */
