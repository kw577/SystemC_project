#include <systemc.h>
#include "sliders.h"
#include "testbench.h"
#include "processor.h"


SC_MODULE(SYSTEM) {

	//instacje modulow
	testbench *tb0;
	sliders* sliders0;
	processor* processor1;

	//deklaracje sygnalow miedzy tb0 i sliders
	sc_signal<bool> rst_sig;

	sc_signal< sc_int<8> >		inp_sig;
	sc_signal<bool>				inp_sig_vld;  //handshaking signal
	sc_signal<bool>				inp_sig_rdy;  //handshaking signal

	sc_signal< sc_int<8> >		outp_sig;
	sc_signal<bool>				outp_sig_vld;  //handshaking signal
	sc_signal<bool>				outp_sig_rdy;  //handshaking signal


	//deklaracje sygnalow miedzy processor1 i sliders
	sc_signal<bool> rst_proc_sliders;
	sc_signal< sc_int<8> >      in_proc_sliders;
	sc_signal< sc_int<8> >      out_proc_sliders;
	
	
	//ZEGAR SYSTEMOWY
	sc_clock clk_sig;


	//konstruktor
	SC_CTOR(SYSTEM):clk_sig("clk_sig", 10, SC_NS)   //SC_NS - nonosekundy (10) - system dziala w trybie 10ns
	{
		//deklaracja instancji modulu testbench
		tb0 = new testbench("tb0");
		//polaczenie modulu z zegarem
		tb0->clk(clk_sig);

		//polaczenie modulu z sygnalami
		tb0->rst(rst_sig);
		tb0->inp(inp_sig);
		tb0->inp_vld(inp_sig_vld); //handshaking signal
		tb0->inp_rdy(inp_sig_rdy); //handshaking signal
		tb0->outp(outp_sig);
		tb0->outp_vld(outp_sig_vld); //handshaking signal
		tb0->outp_rdy(outp_sig_rdy); //handshaking signal


		//////////////////////////////////////
		//deklaracja instancji modulu
		sliders0 = new sliders("sliders0");
		
		//polaczenie modulu z zegarem
		sliders0->clk(clk_sig);

		//polaczenie modulu z sygnalami
		sliders0->rst(rst_sig);
		sliders0->inp(inp_sig);
		sliders0->inp_vld(inp_sig_vld); //handshaking signal
		sliders0->inp_rdy(inp_sig_rdy); //handshaking signal
		sliders0->outp(outp_sig);
		sliders0->outp_vld(outp_sig_vld); //handshaking signal
		sliders0->outp_rdy(outp_sig_rdy); //handshaking signal
		
		sliders0->in_proc(out_proc_sliders); // pol z procesorem
		sliders0->out_proc(in_proc_sliders); // pol z procesorem

		//////////////////////////////////////
		//deklaracja instancji modulu
		processor1 = new processor("processor1");
		
		//polaczenie modulu z zegarem
		processor1->clk(clk_sig);

		//polaczenie modulu z sygnalami
		processor1->rst(rst_sig);
		processor1->in_sld(in_proc_sliders);
		processor1->out_sld(out_proc_sliders);


	}

	//Destruktor - nie jest wymagany
	~SYSTEM() {
		delete tb0;
		delete sliders0;
		delete processor1;
	}


};

SYSTEM* top = NULL;

int sc_main(int argc, char* argv[]) {

	//deklaracja instancji modulu SYSTEM
	top = new SYSTEM("top");
	
	//rozpoczecie symulacji
	sc_start();

	return 0;
}