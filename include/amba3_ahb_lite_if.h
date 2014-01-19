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
	static const unsigned char IDLE 	= 0U;
	static const unsigned char BUSY	 	= 1U;
	static const unsigned char NONSEQ 	= 2U;
	static const unsigned char SEQ 		= 3U;

	static const unsigned char SINGLE = 0U;
	static const unsigned char INCR   = 1U;
	static const unsigned char WRAP4  = 2U;
	static const unsigned char INCR4  = 3U;
	static const unsigned char WRAP8  = 4U;
	static const unsigned char INCR8  = 5U;
	static const unsigned char WRAP16 = 6U;
	static const unsigned char INCR16 = 7U;

	static const unsigned char Byte = 0;
	static const unsigned char Halfword = 1;
	static const unsigned char Word=2;
	static const unsigned char Doubleword=3;
	static const unsigned char Fourword=4;
	static const unsigned char Eightword=5;

	static const bool OKAY   = false;
	static const bool EORROR = true;

	typedef sc_uint<2> trans_type;
	typedef sc_uint<ADWIDTH> address_type;
	typedef sc_uint<3> burst_type;
	typedef sc_uint<3> size_type;
	typedef sc_uint<4> prot_type;
	typedef sc_uint<BUSWIDTH> data_type;

	typedef sc_uint<BUSWIDTH/8> strb_type;

	virtual void ahb_lite_reset() = 0;
	virtual bool ahb_lite_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt) = 0;
	virtual bool  ahb_lite_read(const prot_type& prot, const address_type& ad, data_type& dt) = 0;

};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_base_chain{
public:
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;

	sc_signal<bool> hsel;
	sc_signal<trans_type> htrans;
	sc_signal<address_type> haddr;
	sc_signal<bool> hwrite;
	sc_signal<burst_type>hburst;
	sc_signal<size_type>hsize;
	sc_signal<data_type> hwdata;
	sc_signal<data_type> hrdata;
	sc_signal<bool> hmastlock;
	sc_signal<bool> hready;
	sc_signal<bool> hreadyout;
	sc_signal<prot_type> hprot;
	sc_signal<bool> hresp;


	ahb3_lite_base_chain(const char* name=sc_gen_unique_name("ahb3_lite_base_chain")):
	hsel( PIN_NAME(name,"hsel" )),
	htrans( PIN_NAME(name,"htrans" )),
	haddr(PIN_NAME(name,"haddr")),
	hwrite(PIN_NAME(name,"hwrite")),
	hburst(PIN_NAME(name,"hburst")),
	hsize(PIN_NAME(name,"hsize")),
	hwdata(PIN_NAME(name,"hwdata")),
	hrdata(PIN_NAME(name,"hrdata")),
	hmastlock(PIN_NAME(name,"hmastlock")),
	hready(PIN_NAME(name,"hready")),
	hreadyout(PIN_NAME(name,"hreadyout")),
	hprot(PIN_NAME(name,"hprot")),
	hresp(PIN_NAME(name,"hresp")){}

};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_base_port{
public:
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;


	sc_out<bool> hsel;
	sc_out<trans_type> htrans;
	sc_out<address_type> haddr;
	sc_out<bool> hwrite;
	sc_out<burst_type>hburst;
	sc_out<size_type>hsize;
	sc_out<data_type> hwdata;
	sc_in<data_type> hrdata;
	sc_out<bool> hmastlock;
	sc_in<bool> hready;
	sc_out<prot_type> hprot;
	sc_in<bool> hresp;


	ahb3_lite_base_port(const char* name=sc_gen_unique_name("ahb3_lite_base_port")):
	hsel( PIN_NAME(name,"hsel" )),
	htrans( PIN_NAME(name,"htrans" )),
	haddr(PIN_NAME(name,"haddr")),
	hwrite(PIN_NAME(name,"hwrite")),
	hburst(PIN_NAME(name,"hburst")),
	hsize(PIN_NAME(name,"hsize")),
	hwdata(PIN_NAME(name,"hwdata")),
	hrdata(PIN_NAME(name,"hrdata")),
	hmastlock(PIN_NAME(name,"hmastlock")),
	hready(PIN_NAME(name,"hready")),
	hprot(PIN_NAME(name,"hprot")),
	hresp(PIN_NAME(name,"hresp")){}


	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		hsel(c.hsel);
		htrans(c.htrans);
		haddr(c.haddr);
		hwrite(c.hwrite);
		hburst(c.hburst);
		hsize(c.hsize);
		hwrite(c.hwrite);
		hrdata(c.hrdata);
		hmastlock(c.hmastlock);
		hready(c.hready);
		hprot(c.hprot);
		hresp(c.hresp);
	}

	void bind(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		hsel(c.hsel);
		htrans(c.htrans);
		haddr(c.haddr);
		hwrite(c.hwrite);
		hburst(c.hburst);
		hsize(c.hsize);
		hwrite(c.hwrite);
		hrdata(c.hrdata);
		hmastlock(c.hmastlock);
		hready(c.hready);
		hprot(c.hprot);
		hresp(c.hresp);
	}

};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_base_export{
public:
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;


	sc_in<bool> hsel;
	sc_in<trans_type> htrans;
	sc_in<address_type> haddr;
	sc_in<bool> hwrite;
	sc_in<burst_type>hburst;
	sc_in<size_type>hsize;
	sc_in<data_type> hwdata;
	sc_out<data_type> hrdata;
	sc_in<bool> hmastlock;
	sc_in<bool> hready;
	sc_out<bool> hreadyout;
	sc_in<prot_type> hprot;
	sc_out<bool> hresp;


	ahb3_lite_base_export(const char* name=sc_gen_unique_name("ahb3_lite_base_export")):
	hsel( PIN_NAME(name,"hsel" )),
	htrans(PIN_NAME(name,"htrans")),
	haddr(PIN_NAME(name,"haddr")),
	hwrite(PIN_NAME(name,"hwrite")),
	hburst(PIN_NAME(name,"hburst")),
	hsize(PIN_NAME(name,"hsize")),
	hwdata(PIN_NAME(name,"hwdata")),
	hrdata(PIN_NAME(name,"hrdata")),
	hmastlock(PIN_NAME(name,"hmastelock")),
	hready(PIN_NAME(name,"hready")),
	hreadyout(PIN_NAME(name,"hreadyout")),
	hprot(PIN_NAME(name,"hprot")),
	hresp(PIN_NAME(name,"hresp")){}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		hsel(c.hsel);
		htrans(c.htrans);
		haddr(c.haddr);
		hwrite(c.hwrite);
		hburst(c.hburst);
		hsize(c.hsize);
		hwdata(c.hwdata);
		hrdata(c.hrdata);
		hmastlock(c.hmastlock);
		hready(c.hready);
		hreadyout(c.hreadyout);
		hprot(c.hprot);
		hresp(c.hresp);
	}

	void bind(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		hsel(c.hsel);
		htrans(c.htrans);
		haddr(c.haddr);
		hwrite(c.hwrite);
		hburst(c.hburst);
		hsize(c.hsize);
		hwdata(c.hwdata);
		hrdata(c.hrdata);
		hmastlock(c.hmastlock);
		hready(c.hready);
		hreadyout(c.hreadyout);
		hprot(c.hprot);
		hresp(c.hresp);
	}
};


template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_port:public sc_module, public ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	static const unsigned char IDLE 	= 0U;
	static const unsigned char BUSY	 	= 1U;
	static const unsigned char NONSEQ 	= 2U;
	static const unsigned char SEQ 		= 3U;

	static const unsigned char SINGLE = 0U;
	static const unsigned char INCR   = 1U;
	static const unsigned char WRAP4  = 2U;
	static const unsigned char INCR4  = 3U;
	static const unsigned char WRAP8  = 4U;
	static const unsigned char INCR8  = 5U;
	static const unsigned char WRAP16 = 6U;
	static const unsigned char INCR16 = 7U;

	static const unsigned char Byte = 0;
	static const unsigned char Halfword = 1;
	static const unsigned char Word=2;
	static const unsigned char Doubleword=3;
	static const unsigned char Fourword=4;
	static const unsigned char Eightword=5;

//	static const bool OKAY   = false;
//	static const bool EORROR = true;


	typedef ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE> base_class;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;


	sc_in<bool> hclk;
	sc_in<bool> nreset;

	ahb3_lite_port(sc_module_name name=sc_gen_unique_name("ahb3_lite_port")):sc_module(name),base_class(name)
	,hclk(PIN_NAME(name,"hclk")),nreset(PIN_NAME(name,"nreset")){
		end_module();
	}

	virtual void ahb_lite_reset(){
		base_class::hsel   = false;
		base_class::htrans = IDLE;
	}

	virtual bool ahb_lite_write(const prot_type& prot, const address_type& addr, const strb_type& strb, const data_type& dt){
		bool slverr = false;
		{
			base_class::hsel   = true;
			base_class::htrans = NONSEQ;
			base_class::haddr  = addr;
			base_class::hwrite = true;
			base_class::hprot  = prot;
			do{ wait(); } while (base_class::hready.read() == false );

			base_class::hsel   = false;
			base_class::hwdata = dt;
			base_class::htrans = IDLE;
			do{ wait(); } while (base_class::hready.read() == false );
			slverr = base_class::hresp.read();
		}

		return slverr;
	}

	virtual bool ahb_lite_read(const prot_type& prot, const address_type& addr, data_type& dt){
		bool slverr = false;

		{
			base_class::hsel   = true;
			base_class::htrans = NONSEQ;
			base_class::haddr  = addr;
			base_class::hwrite = false;
			base_class::hprot  = prot;
			do{ wait(); } while (base_class::hready.read() == false );

			base_class::hsel   = false;
			base_class::htrans = IDLE;
			do{ wait(); } while (base_class::hready.read() == false );
			dt = base_class::hrdata.read();
			slverr = base_class::hresp.read();
		}

		return slverr;
	}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		base_class::hsel(c.hsel);
		base_class::htrans(c.htrans);
		base_class::haddr(c.haddr);
		base_class::hwrite(c.hwrite);
		base_class::hburst(c.hburst);
		base_class::hsize(c.hsize);
		base_class::hwdata(c.hwdata);
		base_class::hrdata(c.hrdata);
		base_class::hmastlock(c.hmastlock);
		base_class::hready(c.hready);
		base_class::hprot(c.hprot);
		base_class::hresp(c.hresp);
	}

	void bind(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		base_class::hsel(c.hsel);
		base_class::htrans(c.htrans);
		base_class::haddr(c.haddr);
		base_class::hwrite(c.hwrite);
		base_class::hburst(c.hburst);
		base_class::hsize(c.hsize);
		base_class::hwdata(c.hwdata);
		base_class::hrdata(c.hrdata);
		base_class::hmastlock(c.hmastlock);
		base_class::hready(c.hready);
		base_class::hprot(c.hprot);
		base_class::hresp(c.hresp);
	}

	void operator()(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		bind(c);
	}

	void operator()(ahb3_lite_base_port<ADWIDTH,BUSWIDTH,MODE>& c){
		bind(c);
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_class::hsel, 		TR_NAME("hsel"));
		sc_trace(tf,	base_class::htrans, 	TR_NAME("htrans"));
		sc_trace(tf,	base_class::haddr,		TR_NAME("haddr"));
		sc_trace(tf,	base_class::hwrite,		TR_NAME("hwrite"));
		sc_trace(tf,	base_class::hburst,		TR_NAME("hburst"));
		sc_trace(tf,	base_class::hsize,		TR_NAME("hsize"));
		sc_trace(tf,	base_class::hwdata,		TR_NAME("hwdata"));
		sc_trace(tf,	base_class::hrdata,		TR_NAME("hrdata"));
		sc_trace(tf,	base_class::hmastlock,	TR_NAME("hmastlock"));
		sc_trace(tf,	base_class::hready,		TR_NAME("hready"));
		sc_trace(tf,	base_class::hprot,		TR_NAME("hprot"));
		sc_trace(tf,	base_class::hresp,		TR_NAME("hresp"));
	}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH, class MODE=PIN>
class ahb3_lite_export:public sc_module, public ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE> base_class;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;

	static const unsigned char IDLE 	= 0U;
	static const unsigned char BUSY	 	= 1U;
	static const unsigned char NONSEQ 	= 2U;
	static const unsigned char SEQ 		= 3U;

	static const unsigned char SINGLE = 0U;
	static const unsigned char INCR   = 1U;
	static const unsigned char WRAP4  = 2U;
	static const unsigned char INCR4  = 3U;
	static const unsigned char WRAP8  = 4U;
	static const unsigned char INCR8  = 5U;
	static const unsigned char WRAP16 = 6U;
	static const unsigned char INCR16 = 7U;

	static const unsigned char Byte = 0;
	static const unsigned char Halfword = 1;
	static const unsigned char Word=2;
	static const unsigned char Doubleword=3;
	static const unsigned char Fourword=4;
	static const unsigned char Eightword=5;

//	static const bool OKAY   = false;
//	static const bool EORROR = true;


	sc_in<bool> hclk;
	sc_in<bool> nreset;

	sc_export<if_type> cb_port;

	SC_HAS_PROCESS(ahb3_lite_export);

	ahb3_lite_export(sc_module_name name=sc_gen_unique_name("ahb3_lite_export")):sc_module(name),base_class(name)
	,hclk(PIN_NAME(name,"hclk")),nreset(PIN_NAME(name,"nreset")){
		SC_CTHREAD(bus_thread,hclk.pos());
		async_reset_signal_is(nreset,false);

		end_module();
	}

	virtual void ahb_lite_reset(){
		cb_port->ahb_lite_reset();
	}

	virtual bool ahb_lite_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		return cb_port->ahb_lite_write(prot, ad, strb, dt);
	}

	virtual bool ahb_lite_read(const prot_type& prot, const address_type& ad, data_type& dt){
		return cb_port->ahb_lite_read(prot, ad, dt);
	}

	void bind(if_type& p){
		this->cb_port(p);
	}

	void bind(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		base_class::hsel(c.hsel);
		base_class::htrans(c.htrans);
		base_class::haddr(c.haddr);
		base_class::hwrite(c.hwrite);
		base_class::hburst(c.hburst);
		base_class::hsize(c.hsize);
		base_class::hwdata(c.hwdata);
		base_class::hrdata(c.hrdata);
		base_class::hmastlock(c.hmastlock);
		base_class::hready(c.hready);
		base_class::hreadyout(c.hreadyout);
		base_class::hprot(c.hprot);
		base_class::hresp(c.hresp);
	}

	void bind(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		base_class::hsel(c.hsel);
		base_class::htrans(c.htrans);
		base_class::haddr(c.haddr);
		base_class::hwrite(c.hwrite);
		base_class::hburst(c.hburst);
		base_class::hsize(c.hsize);
		base_class::hwdata(c.hwdata);
		base_class::hrdata(c.hrdata);
		base_class::hmastlock(c.hmastlock);
		base_class::hready(c.hready);
		base_class::hreadyout(c.hreadyout);
		base_class::hprot(c.hprot);
		base_class::hresp(c.hresp);
	}

	void operator()(ahb3_lite_base_chain<ADWIDTH,BUSWIDTH>& c){
		bind(c);
	}

	void operator()(ahb3_lite_base_export<ADWIDTH,BUSWIDTH,MODE>& c){
		bind(c);
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_class::hsel, 		TR_NAME("hsel"));
		sc_trace(tf,	base_class::htrans, 	TR_NAME("htrans"));
		sc_trace(tf,	base_class::haddr,		TR_NAME("haddr"));
		sc_trace(tf,	base_class::hwrite,		TR_NAME("hwrite"));
		sc_trace(tf,	base_class::hburst,		TR_NAME("hburst"));
		sc_trace(tf,	base_class::hsize,		TR_NAME("hsize"));
		sc_trace(tf,	base_class::hwdata,		TR_NAME("hwdata"));
		sc_trace(tf,	base_class::hrdata,		TR_NAME("hrdata"));
		sc_trace(tf,	base_class::hmastlock,	TR_NAME("hmastlock"));
		sc_trace(tf,	base_class::hready,		TR_NAME("hready"));
		sc_trace(tf,	base_class::hreadyout,	TR_NAME("hreadyout"));
		sc_trace(tf,	base_class::hprot,		TR_NAME("hprot"));
		sc_trace(tf,	base_class::hresp,		TR_NAME("hresp"));
	}

	void bus_thread(){
		bool         post_sel   = false;
		trans_type   post_trans = IDLE;
		address_type post_addr = base_class::haddr.read();
		bool 		 post_write = false;

		data_type rdata = data_type();
		bool slverr = if_type::OKAY;

		{
			ahb_lite_reset();
			base_class::hreadyout  	= false;
			base_class::hrdata  	= data_type();
			base_class::hresp   	= slverr;
			wait();
		}

		while( true ){
			prot_type prot = prot_type();

			bool hsel = false;
			trans_type trans = IDLE;
			bool write = false;
			address_type addr = address_type();
			strb_type strb = strb_type();
			data_type wdata = data_type();

			{
				base_class::hreadyout = true;
				base_class::hrdata  = rdata;
				base_class::hresp   = slverr;
				wait();
				while(base_class::hready.read() == false) wait();
				base_class::hreadyout = false;
				wdata = base_class::hwdata.read();

				hsel  = base_class::hsel.read();
				trans = base_class::htrans.read();
				prot  = base_class::hprot.read();
				write = base_class::hwrite.read();
				addr  = base_class::haddr.read();
			}

			if( post_sel == true && post_trans == NONSEQ && post_write == true ){
				slverr = ahb_lite_write(prot, post_addr, strb, wdata);
			}else if( post_sel == true && post_trans == NONSEQ && post_write == false ){
				slverr =  ahb_lite_read(prot, post_addr, rdata);
			}

			post_sel = hsel;
			post_trans = trans;
			post_addr = addr;
			post_write = write;

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
		sensitive << initiator_port.hsel;
		sensitive << initiator_port.htrans;
		sensitive << initiator_port.haddr;
		sensitive << initiator_port.hwrite;
		sensitive << initiator_port.hburst;
		sensitive << initiator_port.hsize;
		sensitive << initiator_port.hwdata;
		sensitive << initiator_port.hmastlock;
		sensitive << initiator_port.hprot;

		sensitive << target_port.hreadyout;
		sensitive << target_port.hrdata;
		sensitive << target_port.hresp;

		dont_initialize();
		end_module();
	}

	void method(){
		target_port.hsel      = initiator_port.hsel.read();
		target_port.htrans    = initiator_port.htrans.read();
		target_port.haddr     = initiator_port.haddr.read();
		target_port.hwrite    = initiator_port.hwrite.read();
		target_port.hburst    = initiator_port.hburst.read();
		target_port.hsize     = initiator_port.hsize.read();
		target_port.hwdata    = initiator_port.hwdata.read();
		target_port.hmastlock = initiator_port.hmastlock.read();
		target_port.hprot     = initiator_port.hprot.read();
		initiator_port.hrdata = target_port.hrdata.read();
		initiator_port.hresp  = target_port.hresp.read();

		initiator_port.hready = target_port.hreadyout.read();
		target_port.hready 	  = target_port.hreadyout.read();
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	initiator_port.hsel, 		TR_NAME("initiator_port.hsel"));
		sc_trace(tf,	initiator_port.htrans, 		TR_NAME("initiator_port.htrans"));
		sc_trace(tf,	initiator_port.haddr,		TR_NAME("initiator_port.haddr"));
		sc_trace(tf,	initiator_port.hwrite,		TR_NAME("initiator_port.hwrite"));
		sc_trace(tf,	initiator_port.hburst,		TR_NAME("initiator_port.hburst"));
		sc_trace(tf,	initiator_port.hsize,		TR_NAME("initiator_port.hsize"));
		sc_trace(tf,	initiator_port.hwdata,		TR_NAME("initiator_port.hwdata"));
		sc_trace(tf,	initiator_port.hmastlock,	TR_NAME("initiator_port.hmastlock"));
		sc_trace(tf,	initiator_port.hprot,		TR_NAME("initiator_port.hprot"));

		sc_trace(tf,	initiator_port.hready,		TR_NAME("initiator_port.hready"));
		sc_trace(tf,	initiator_port.pstrb,		TR_NAME("initiator_port.pstrb"));
		sc_trace(tf,	initiator_port.hrdata,		TR_NAME("initiator_port.hrdata"));


		sc_trace(tf,	target_port.hsel, 		TR_NAME("target_port.hsel") );
		sc_trace(tf,	target_port.htrans, 	TR_NAME("target_port.htrans") );
		sc_trace(tf,	target_port.haddr,		TR_NAME("target_port.haddr"));
		sc_trace(tf,	target_port.hwrite,		TR_NAME("target_port.hwrite"));
		sc_trace(tf,	target_port.hburst,		TR_NAME("target_port.hburst"));
		sc_trace(tf,	target_port.hsize,		TR_NAME("target_port.hsize"));
		sc_trace(tf,	target_port.hwdata,		TR_NAME("target_port.hwdata"));
		sc_trace(tf,	target_port.hmastlock,	TR_NAME("target_port.hmastlock"));
		sc_trace(tf,	target_port.hprot,		TR_NAME("target_port.hprot"));

		sc_trace(tf,	target_port.hreadyout,	TR_NAME("target_port.hreadyout"));
		sc_trace(tf,	target_port.hready,		TR_NAME("target_port.hready"));
		sc_trace(tf,	target_port.pstrb,		TR_NAME("target_port.pstrb"));
		sc_trace(tf,	target_port.hrdata,		TR_NAME("target_port.hrdata"));

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
class ahb3_lite_port<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_initiator_socket<BUSWIDTH>, public tlm_bw_transport_if<>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef tlm_initiator_socket<BUSWIDTH> base_type;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;

	sc_in<bool> hclk;
	sc_in<bool> nreset;

	ahb3_lite_port(const sc_module_name name=sc_gen_unique_name("ahb3_lite_port")):base_type(name)
	,hclk(PIN_NAME(name,"pclk")),nreset(PIN_NAME(name,"nreset")){
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



	virtual void ahb_lite_reset(){}
	virtual bool ahb_lite_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		 tlm::tlm_generic_payload trans;
		 sc_time time;

		 trans.is_write();
		 (*this)->b_transport(trans,time);

		 if( trans.get_response_status() == TLM_ADDRESS_ERROR_RESPONSE ){
			 return if_type::EORROR;
		 }else{
			 return if_type::OKAY;
		 }
	}

	virtual bool  ahb_lite_read(const prot_type& prot, const address_type& ad, data_type& dt){
		 tlm::tlm_generic_payload trans;
		 sc_time time;

		 trans.is_read();
		 (*this)->b_transport(trans,time);

		 if( trans.get_response_status() == TLM_ADDRESS_ERROR_RESPONSE ){
			 return if_type::EORROR;
		 }else{
			 return if_type::OKAY;
		 }
	}
};

template<unsigned int ADWIDTH, unsigned int BUSWIDTH>
class ahb3_lite_export<ADWIDTH,BUSWIDTH,TLM2LT>:public tlm_target_socket<BUSWIDTH>, public tlm_fw_transport_if<>, public ahb3_lite_interface<ADWIDTH,BUSWIDTH>{
public:
	typedef tlm_target_socket<BUSWIDTH> base_type;
	typedef ahb3_lite_interface<ADWIDTH,BUSWIDTH> if_type;
	typedef typename if_type::trans_type 	trans_type;
	typedef typename if_type::address_type 	address_type;
	typedef typename if_type::burst_type 	burst_type;
	typedef typename if_type::size_type 	size_type;
	typedef typename if_type::data_type 	data_type;
	typedef typename if_type::strb_type 	strb_type;
	typedef typename if_type::prot_type 	prot_type;

	sc_in<bool> hclk;
	sc_in<bool> nreset;

	ahb3_lite_export(const sc_module_name name=sc_gen_unique_name("ahb3_lite_export")):base_type(name)
	,hclk(PIN_NAME(name,"hclk")),nreset(PIN_NAME(name,"nreset")){
		(base_type::get_base_export())(*this);
	}

	void b_transport( tlm::tlm_generic_payload &trans, sc_time &time ) {
		bool resp = if_type::OKAY;

		uint64 ad = trans.get_address();
		unsigned int length = trans.get_data_length();
		unsigned char* dt = trans.get_data_ptr();
		unsigned char* mask = trans.get_byte_enable_ptr();

		if( trans.is_write() == true ){
			//resp;// = ahb_lite_write(trans.get_address());
		}


		if( resp == if_type::OKAY ){
			trans.set_response_status( tlm::TLM_OK_RESPONSE );
		}else{
			trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
		}
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

	sc_export<if_type> cb_port;

	void bind(if_type& if_class){
		cb_port(if_class);
		ahb_lite_reset();
	}

	virtual void ahb_lite_reset(){
		cb_port->ahb_lite_reset();
	}

	virtual bool ahb_lite_write(const prot_type& prot, const address_type& ad, const strb_type& strb, const data_type& dt){
		return cb_port->ahb_lite_write(prot, ad, strb, dt);
	}

	virtual bool  ahb_lite_read(const prot_type& prot, const address_type& ad, data_type& dt){
		return cb_port->ahb_lite_read(prot,ad,dt);
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
