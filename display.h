#include <systemc.h>


SC_MODULE(display) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;

	//do komunikacji ze procesorem
	sc_in< sc_int<8> >		in_dp; 
	
	//handshaking with processor
	sc_out<bool> in_dp_vld;
	sc_in<bool> in_dp_rdy;

	//deklaracja funkcji
	void display_main();


	//konstruktor
	SC_CTOR(display) {

		SC_CTHREAD(display_main, clk.pos());
		reset_signal_is(rst, true);

	}



};