/*
 * amba3_ahb_lite_if.h
 *
 *  Created on: 2013/12/31
 *      Author: Kuniyasu
 */

#ifndef AMBA3_AHB_LITE_IF_H_
#define AMBA3_AHB_LITE_IF_H_

#include<systemc.h>
#include<tlm.h>
using namespace tlm;

class PIN{};
class TLM2LT{};
class TLM2AT{};

#define TR_NAME(_name) (std::string(name())+"_"+std::string(_name)).c_str()
#define PIN_NAME(bname,_name_) (std::string(bname)+"_"+std::string(_name_)).c_str()

template<unsigned int ADWIDTH, unsigned int BUSWIDTH> class ahb3_lite_interface;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH> class ahb3_lite_base_chain;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE>class ahb3_lite_base_port;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE>class ahb3_lite_base_export;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE>class ahb3_lite_port;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE>class ahb3_lite_export;
template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE>class ahb3_litel_simple_bus;


template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_interface:public sc_interface{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	virtual void ahb_lite_reset() = 0;
	virtual bool ahb_lite_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt) = 0;
	virtual bool  ahb_lite_read(const prot_type& prot, const address_type& ad, data_type& dt) = 0;

};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_base_chain{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	sc_signal<bool> psel;
	sc_signal<address_type> paddr;
	sc_signal<prot_type> pprot;
	sc_signal<bool> penable;
	sc_signal<bool> pwrite;
	sc_signal<bool> pready;
	sc_signal<strb_type> pstrb;
	sc_signal<data_type> pwdata;

	sc_signal<data_type> prdata;
	sc_signal<bool> pslverr;


	ahb3_lite_base_chain(const char* name=sc_gen_unique_name("ahb3_lite_base_chain")):
	psel( PIN_NAME(name,"psel" )),
	paddr(PIN_NAME(name,"paddr")),
	pprot(PIN_NAME(name,"pprot")),
	penable(PIN_NAME(name,"penable")),
	pwrite(PIN_NAME(name,"pwrite")),
	pready(PIN_NAME(name,"pready")),
	pstrb(PIN_NAME(name,"pstrb")),
	pwdata(PIN_NAME(name,"pwdata")),
	prdata(PIN_NAME(name,"prdata")),
	pslverr(PIN_NAME(name,"pslverr")){}

};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_base_port{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	sc_out<bool> psel;
	sc_out<address_type> paddr;
	sc_out<prot_type> pprot;
	sc_out<bool> penable;
	sc_out<bool> pwrite;
	sc_in<bool>  pready;
	sc_out<strb_type> pstrb;
	sc_out<data_type> pwdata;

	sc_in<data_type> prdata;
	sc_in<bool> pslverr;

	ahb3_lite_base_port(const char* name=sc_gen_unique_name("ahb3_lite_base_port")):
	psel( PIN_NAME(name,"psel" )),
	paddr(PIN_NAME(name,"paddr")),
	pprot(PIN_NAME(name,"pprot")),
	penable(PIN_NAME(name,"penable")),
	pwrite(PIN_NAME(name,"pwrite")),
	pready(PIN_NAME(name,"pready")),
	pstrb(PIN_NAME(name,"pstrb")),
	pwdata(PIN_NAME(name,"pwdata")),
	prdata(PIN_NAME(name,"prdata")),
	pslverr(PIN_NAME(name,"pslverr")){}


	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		psel(c.psel);
		paddr(c.paddr);
		pready(c.pready);
		pprot(c.pprot);
		penable(c.penable);
		pwrite(c.pwrite);
		pstrb(c.pstrb);
		pwdata(c.pwdata);
		prdata(c.prdata);
		pslverr(c.pslverr);
	}

	void bind(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		psel(c.psel);
		paddr(c.paddr);
		pready(c.pready);
		pprot(c.pprot);
		penable(c.penable);
		pwrite(c.pwrite);
		pstrb(c.pstrb);
		pwdata(c.pwdata);
		prdata(c.prdata);
		pslverr(c.pslverr);
	}

};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_base_export{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	sc_in<bool> psel;
	sc_in<address_type> paddr;
	sc_in<prot_type> pprot;
	sc_in<bool> penable;
	sc_in<bool> pwrite;
	sc_out<bool> pready;
	sc_in<strb_type> pstrb;
	sc_in<data_type> pwdata;
	sc_out<data_type> prdata;
	sc_out<bool> pslverr;

	ahb3_lite_base_export(const char* name=sc_gen_unique_name("ahb3_lite_base_export")):
	psel( PIN_NAME(name,"psel" )),
	paddr(PIN_NAME(name,"paddr")),
	pprot(PIN_NAME(name,"pprot")),
	penable(PIN_NAME(name,"penable")),
	pwrite(PIN_NAME(name,"pwrite")),
	pready(PIN_NAME(name,"pready")),
	pstrb(PIN_NAME(name,"pstrb")),
	pwdata(PIN_NAME(name,"pwdata")),
	prdata(PIN_NAME(name,"prdata")),
	pslverr(PIN_NAME(name,"pslverr")){}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		psel(c.psel);
		paddr(c.paddr);
		pready(c.pready);
		pprot(c.pprot);
		penable(c.penable);
		pwrite(c.pwrite);
		pstrb(c.pstrb);
		pwdata(c.pwdata);
		prdata(c.prdata);
		pslverr(c.pslverr);
	}

	void bind(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		psel(c.psel);
		paddr(c.paddr);
		pready(c.pready);
		pprot(c.pprot);
		penable(c.penable);
		pwrite(c.pwrite);
		pstrb(c.pstrb);
		pwdata(c.pwdata);
		prdata(c.prdata);
		pslverr(c.pslverr);
	}
};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_port:public sc_module, public ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8U> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	typedef ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE> base_class;

	sc_in<bool> pclk;
	sc_in<bool> nreset;

	ahb3_lite_port(sc_module_name name=sc_gen_unique_name("ahb3_lite_port")):sc_module(name),pclk("pclk"),nreset("nreset"){
		end_module();
	}

	virtual void apb_reset(){
		base_class::psel = false;
	}

	virtual bool apb_write(const prot_type& prot, const address_type& addr, const strb_type& strb, const data_type& dt){
		bool slverr = false;
		{
			base_class::psel = true;
			base_class::penable = false;
			base_class::paddr = addr;
			base_class::pwrite = true;
			base_class::pstrb = strb;
			base_class::pwdata = dt;
			base_class::pprot = prot;
			wait();

			base_class::penable = true;
			wait();

			while( base_class::pready.read() == false) wait();
			base_class::psel = false;
			base_class::penable = false;
			slverr = base_class::pslverr.read();
		}

		return slverr;
	}

	virtual bool apb_read(const prot_type& prot, const address_type& addr, data_type& dt){
		bool slverr = false;

		{
			base_class::psel = true;
			base_class::penable = false;
			base_class::paddr = addr;
			base_class::pwrite = false;
			base_class::pprot = prot;
			//base_class::pstrb = strb_type();
			//base_class::pwdata = data_type();
			wait();

			base_class::penable = true;
			wait();

			while( base_class::pready.read() == false) wait();
			base_class::psel = false;
			base_class::penable = false;
			dt = base_class::prdata.read();
			slverr =  base_class::pslverr.read();
		}

		return slverr;
	}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		base_class::psel(c.psel);
		base_class::paddr(c.paddr);
		base_class::pready(c.pready);
		base_class::pprot(c.pprot);
		base_class::penable(c.penable);
		base_class::pwrite(c.pwrite);
		base_class::pstrb(c.pstrb);
		base_class::pwdata(c.pwdata);
		base_class::prdata(c.prdata);
		base_class::pslverr(c.pslverr);
	}

	void bind(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		base_class::psel(c.psel);
		base_class::paddr(c.paddr);
		base_class::pready(c.pready);
		base_class::pprot(c.pprot);
		base_class::penable(c.penable);
		base_class::pwrite(c.pwrite);
		base_class::pstrb(c.pstrb);
		base_class::pwdata(c.pwdata);
		base_class::prdata(c.prdata);
		base_class::pslverr(c.pslverr);
	}

	void operator()(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		bind(c);
	}

	void operator()(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		bind(c);
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_class::psel, 		TR_NAME("psel"));
		sc_trace(tf,	base_class::paddr,		TR_NAME("paddr"));
		sc_trace(tf,	base_class::pprot,		TR_NAME("pprot"));
		sc_trace(tf,	base_class::penable,	TR_NAME("penable"));
		sc_trace(tf,	base_class::pwrite,		TR_NAME("pwrite"));
		sc_trace(tf,	base_class::pready,		TR_NAME("pready"));
		sc_trace(tf,	base_class::pstrb,		TR_NAME("pstrb"));
		sc_trace(tf,	base_class::pwdata,		TR_NAME("pwdata"));
		sc_trace(tf,	base_class::prdata,		TR_NAME("prdata"));
		sc_trace(tf,	base_class::pslverr,	TR_NAME("pslverr"));
	}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_export:public sc_module, public ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	typedef ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE> base_class;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> inf_type;

	sc_in<bool> pclk;
	sc_in<bool> nreset;

	sc_export<inf_type> cb_port;
	//sc_export<reset_interface> reset_export;

	SC_HAS_PROCESS(ahb3_lite_export);

	ahb3_lite_export(sc_module_name name=sc_gen_unique_name("ahb3_lite_export")):sc_module(name),pclk("pclk"),nreset("nreset"){
		SC_CTHREAD(bus_thread,pclk.pos());
		async_reset_signal_is(nreset,false);

		end_module();
	}

	virtual void apb_reset(){
		cb_port->apb_reset();
	}

	virtual bool apb_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		return cb_port->apb_write(prot, ad, strb, dt);
	}

	virtual bool apb_read(const prot_type& prot, const address_type& ad, data_type& dt){
		return cb_port->apb_read(prot, ad, dt);
	}

	void bind(inf_type& p){
		this->cb_port(p);
	}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		base_class::psel(c.psel);
		base_class::paddr(c.paddr);
		base_class::pready(c.pready);
		base_class::pprot(c.pprot);
		base_class::penable(c.penable);
		base_class::pwrite(c.pwrite);
		base_class::pstrb(c.pstrb);
		base_class::pwdata(c.pwdata);
		base_class::prdata(c.prdata);
		base_class::pslverr(c.pslverr);
	}

	void bind(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		base_class::psel(c.psel);
		base_class::paddr(c.paddr);
		base_class::pready(c.pready);
		base_class::pprot(c.pprot);
		base_class::penable(c.penable);
		base_class::pwrite(c.pwrite);
		base_class::pstrb(c.pstrb);
		base_class::pwdata(c.pwdata);
		base_class::prdata(c.prdata);
		base_class::pslverr(c.pslverr);
	}

	void operator()(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		bind(c);
	}

	void operator()(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		bind(c);
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_class::psel, 		TR_NAME("psel"));
		sc_trace(tf,	base_class::paddr,		TR_NAME("paddr"));
		sc_trace(tf,	base_class::pprot,		TR_NAME("pprot"));
		sc_trace(tf,	base_class::penable,	TR_NAME("penable"));
		sc_trace(tf,	base_class::pwrite,		TR_NAME("pwrite"));
		sc_trace(tf,	base_class::pready,		TR_NAME("pready"));
		sc_trace(tf,	base_class::pstrb,		TR_NAME("pstrb"));
		sc_trace(tf,	base_class::pwdata,		TR_NAME("pwdata"));
		sc_trace(tf,	base_class::prdata,		TR_NAME("prdata"));
		sc_trace(tf,	base_class::pslverr,	TR_NAME("pslverr"));
	}

	void bus_thread(){
		{
			apb_reset();
			base_class::pready  = false;
			base_class::prdata  = data_type();
			base_class::pslverr = false;
			wait();
		}

		while( true ){
			prot_type prot = prot_type();
			bool write = false;
			address_type addr = address_type();
			strb_type strb = strb_type();
			data_type wdata = data_type();
			data_type rdata = data_type();
			bool slverr = false;


			{
				base_class::pready = true;
				wait();

				while( base_class::psel.read() == false) wait();
				base_class::pready = false;
				prot = base_class::pprot.read();
				write = base_class::pwrite.read();
				addr = base_class::paddr.read();
				strb = base_class::pstrb.read();
				wdata = base_class::pwdata.read();
				rdata = data_type();
				slverr = false;
			}

			if( write == true ){
				slverr = apb_write(prot, addr, strb, wdata);
			}else{
				slverr = apb_read(prot, addr, rdata);
			}


			{
				base_class::prdata = rdata;
				base_class::pready = true;
				base_class::pslverr = slverr;
				wait();
				base_class::pready = false;
			}

		}
	}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_simple_bus:public sc_module{
public:
	ahb3_lite_base_chain<ADWIDTH,BUSWIDTH> initiator_port;
	ahb3_lite_base_chain<ADWIDTH,BUSWIDTH> target_port;

	SC_HAS_PROCESS(ahb3_lite_simple_bus);

	ahb3_lite_simple_bus(sc_module_name name):sc_module(name),
	initiator_port("initiator_port"),target_port("target_port")
	{
		SC_METHOD(method);
		sensitive << initiator_port.psel;
		sensitive << initiator_port.pprot;
		sensitive << initiator_port.penable;
		sensitive << initiator_port.paddr;
		sensitive << initiator_port.pwrite;
		sensitive << initiator_port.pwdata;
		sensitive << initiator_port.pstrb;

		sensitive << target_port.pready;
		sensitive << target_port.prdata;
		sensitive << target_port.pslverr;
		dont_initialize();
		end_module();
	}

	void method(){
		target_port.psel    = initiator_port.psel.read();
		target_port.pprot   = initiator_port.pprot.read();
		target_port.penable = initiator_port.penable.read();
		target_port.paddr   = initiator_port.paddr.read();
		target_port.pwrite  = initiator_port.pwrite.read();
		target_port.pstrb   = initiator_port.pstrb.read();
		target_port.pwdata  = initiator_port.pwdata.read();

		initiator_port.pready = target_port.pready.read();
		initiator_port.prdata = target_port.prdata.read();
		initiator_port.pslverr = target_port.pslverr.read();

	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	initiator_port.psel, 	TR_NAME("initiator_port.psel") );
		sc_trace(tf,	initiator_port.paddr,	TR_NAME("initiator_port.paddr"));
		sc_trace(tf,	initiator_port.pprot,	TR_NAME("initiator_port.pprot"));
		sc_trace(tf,	initiator_port.penable,	TR_NAME("initiator_port.penable"));
		sc_trace(tf,	initiator_port.pwrite,	TR_NAME("initiator_port.pwrite"));
		sc_trace(tf,	initiator_port.pready,	TR_NAME("initiator_port.pready"));
		sc_trace(tf,	initiator_port.pstrb,	TR_NAME("initiator_port.pstrb"));
		sc_trace(tf,	initiator_port.pwdata,	TR_NAME("initiator_port.pwdata"));
		sc_trace(tf,	initiator_port.prdata,	TR_NAME("initiator_port.prdata"));
		sc_trace(tf,	initiator_port.pslverr,	TR_NAME("initiator_port.pslverr"));

		sc_trace(tf,	target_port.psel, 		TR_NAME("target_port.psel"));
		sc_trace(tf,	target_port.paddr,		TR_NAME("target_port.paddr"));
		sc_trace(tf,	target_port.pprot,		TR_NAME("target_port.pprot"));
		sc_trace(tf,	target_port.penable,	TR_NAME("target_port.penable"));
		sc_trace(tf,	target_port.pwrite,		TR_NAME("target_port.pwrite"));
		sc_trace(tf,	target_port.pready,		TR_NAME("target_port.pready"));
		sc_trace(tf,	target_port.pstrb,		TR_NAME("target_port.pstrb"));
		sc_trace(tf,	target_port.pwdata,		TR_NAME("target_port.pwdata"));
		sc_trace(tf,	target_port.prdata,		TR_NAME("target_port.prdata"));
		sc_trace(tf,	target_port.pslverr,	TR_NAME("target_port.pslverr"));

	}
};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_base_port<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_initiator_socket<BUSWIDTH>{
public:

	typedef tlm_initiator_socket<BUSWIDTH> base_type;
	ahb3_lite_base_port(const sc_module_name name=sc_gen_unique_name("ahb3_lite_base_port")):base_type(name){}
};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_base_export<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_target_socket<BUSWIDTH>{
public:
	typedef tlm_target_socket<BUSWIDTH> base_type;
	ahb3_lite_base_export(const sc_module_name name=sc_gen_unique_name("ahb3_lite_base_export")):base_type(name){}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_port<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_initiator_socket<BUSWIDTH>, public tlm_bw_transport_if<>, ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef tlm_initiator_socket<BUSWIDTH> base_type;

	sc_in<bool> pclk;
	sc_in<bool> nreset;

	ahb3_lite_port(const sc_module_name name=sc_gen_unique_name("ahb3_lite_port")):base_type(name){
		(base_type::get_base_export())(*this);
	}

	virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase &phase, sc_time& time ){
	    // not support
	    trans.set_response_status( tlm::TLM_GENERIC_ERROR_RESPONSE );
	    return tlm::TLM_COMPLETED;
	}

	virtual void invalidate_direct_mem_ptr( sc_dt::uint64 a, sc_dt::uint64 b){
	    // DMI unused
	}

	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	virtual void apb_reset(){}
	virtual bool apb_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		 tlm::tlm_generic_payload trans;
		 sc_time time;

		 trans.is_write();
		 (*this)->b_transport(trans,time);

		 if( trans.get_response_status() == TLM_ADDRESS_ERROR_RESPONSE ){
			 return false;
		 }else{
			 return true;
		 }
	}

	virtual bool  apb_read(const prot_type& prot, const address_type& ad, data_type& dt){
		 tlm::tlm_generic_payload trans;
		 sc_time time;

		 trans.is_read();
		 (*this)->b_transport(trans,time);

		 if( trans.get_response_status() == TLM_ADDRESS_ERROR_RESPONSE ){
			 return false;
		 }else{
			 return true;
		 }
	}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_export<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_target_socket<BUSWIDTH>, public tlm_fw_transport_if<>, ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef tlm_target_socket<BUSWIDTH> base_type;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> inf_type;

	sc_in<bool> pclk;
	sc_in<bool> nreset;

	ahb3_lite_export(const sc_module_name name=sc_gen_unique_name("ahb3_lite_export")):base_type(name),pclk("pclk"){
		(base_type::get_base_export())(*this);
	}

	void b_transport( tlm::tlm_generic_payload &trans, sc_time &time ) {
	    trans.set_response_status( tlm::TLM_OK_RESPONSE );
	}

	tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &time ){
	    cout << "nb_transport_fw is not supported." << endl;
	    trans.set_response_status( tlm::TLM_GENERIC_ERROR_RESPONSE );

	    return tlm::TLM_COMPLETED;
	}

	unsigned int transport_dbg( tlm::tlm_generic_payload &trans ){
	    return 0;  // Debug not supported
	}

	bool get_direct_mem_ptr( tlm::tlm_generic_payload &trans, tlm::tlm_dmi& dmi){
	    return false; // DMI not supported
	}

	typedef sc_uint<BUSWIDTH> data_type;
	typedef sc_uint<BUSWIDTH/8> strb_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> prot_type;

	sc_export<inf_type> cb_port;
	void bind(inf_type& if_class){
		cb_port(if_class);
		apb_reset();
	}

	virtual void apb_reset(){
		cb_port->apb_reset();
	}

	virtual bool apb_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		return cb_port->apb_write(prot, ad, strb, dt);
	}

	virtual bool  apb_read(const prot_type& prot, const address_type& ad, data_type& dt){
		return cb_port->apb_read(prot,ad,dt);
	}

};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_simple_bus<ADWIDTH,BUSWIDTH,TLM2LT>: public tlm_fw_transport_if<>, public tlm_bw_transport_if<>{
public:
	ahb3_lite_base_export<ADWIDTH,BUSWIDTH,TLM2LT> initiator_port;
	ahb3_lite_base_port<ADWIDTH,BUSWIDTH,TLM2LT> target_port;

	ahb3_lite_simple_bus(const sc_module_name name=sc_gen_unique_name("ahb3_lite_simple_bus")):initiator_port("initiator_port"),target_port("target_port"){
		initiator_port(*this);
		target_port(*this);
	}

	void b_transport( tlm::tlm_generic_payload &trans, sc_time &time ) {
		target_port->b_transport(trans,time);
	}

	tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &time ){
		return target_port->nb_transport_fw(trans,phase,time);
	}

	unsigned int transport_dbg( tlm::tlm_generic_payload &trans ){
		return target_port->transport_dbg(trans);
	}

	bool get_direct_mem_ptr( tlm::tlm_generic_payload &trans, tlm::tlm_dmi& dmi){
		return target_port->get_direct_mem_ptr(trans,dmi);
	}

	virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase &phase, sc_time& time ){
		return initiator_port->nb_transport_bw(trans,phase,time);
	}

	virtual void invalidate_direct_mem_ptr( sc_dt::uint64 a, sc_dt::uint64 b){
		initiator_port->invalidate_direct_mem_ptr(a,b);
	}
};

#endif /* AMBA4_APB_IF_H_ */
