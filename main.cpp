#include <systemc.h>
#include "sliders.h"
#include "testbench.h"



SC_MODULE(SYSTEM) {

	//instacje modulow
	testbench *tb0;
	sliders* sliders0;

	//deklaracje sygnalow
	sc_signal<bool> rst_sig;

	sc_signal< sc_int<8> >		inp_sig;
	sc_signal<bool>				inp_sig_vld;  //handshaking signal
	sc_signal<bool>				inp_sig_rdy;  //handshaking signal

	sc_signal< sc_int<8> >		outp_sig;
	sc_signal<bool>				outp_sig_vld;  //handshaking signal
	sc_signal<bool>				outp_sig_rdy;  //handshaking signal

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

	}

	//Destruktor - nie jest wymagany
	~SYSTEM() {
		delete tb0;
		delete sliders0;

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