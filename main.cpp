#include <systemc.h>
#include "fir.h"
#include "tb.h"


//glowna funkcja main jest deklarowana dla modulu SYSTEM - zawierajacego pozostale moduly
SC_MODULE(SYSTEM) {

	//Module declarations (instacje modulow)
	tb *tb0;
	fir* fir0;

	//Local signal declarations - do komunikacji miedzy modulem tb0 (testbench) i fir0
	sc_signal<bool> rst_sig;

	sc_signal< sc_int<16> >		inp_sig;
	sc_signal<bool>				inp_sig_vld;  //handshaking signal
	sc_signal<bool>				inp_sig_rdy;  //handshaking signal

	sc_signal< sc_int<16> >		outp_sig;
	sc_signal<bool>				outp_sig_vld;  //handshaking signal
	sc_signal<bool>				outp_sig_rdy;  //handshaking signal

	//ZEGAR SYSTEMOWY
	sc_clock clk_sig;


	//konstruktor
	SC_CTOR(SYSTEM):clk_sig("clk_sig", 10, SC_NS)   //SC_NS - nonosekundy (10) - system dziala w trybie 10ns
	{
		//deklaracja instancji modulu testbench
		tb0 = new tb("tb0");
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
		fir0 = new fir("fir0");
		
		//polaczenie modulu z zegarem
		fir0->clk(clk_sig);

		//polaczenie modulu z sygnalami
		fir0->rst(rst_sig);
		fir0->inp(inp_sig);
		fir0->inp_vld(inp_sig_vld); //handshaking signal
		fir0->inp_rdy(inp_sig_rdy); //handshaking signal
		fir0->outp(outp_sig);
		fir0->outp_vld(outp_sig_vld); //handshaking signal
		fir0->outp_rdy(outp_sig_rdy); //handshaking signal

	}

	//Destruktor - nie jest wymagany
	~SYSTEM() {
		delete tb0;
		delete fir0;

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