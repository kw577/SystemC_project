#include <systemc.h>


SC_MODULE(processorSt) {
	sc_in<bool>		clk;
	sc_in<bool>		rst
		;
	//do komunikacji z procesorem1
	sc_in< sc_int<8> >		in_pp; 
	//handshaking with processor1
	sc_out<bool> in_pp_vld;
	sc_in<bool> in_pp_rdy;


	//deklaracja funkcji
	void processorSt_main();


	//konstruktor
	SC_CTOR(processorSt) {

		SC_CTHREAD(processorSt_main, clk.pos());
		reset_signal_is(rst, true);

	}

};