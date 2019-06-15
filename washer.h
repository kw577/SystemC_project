#include <systemc.h>


SC_MODULE(washer) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;

	//do komunikacji ze procesorem2
	sc_in< sc_int<8> >		in_wp; 

	//handshaking with processor1
	sc_out<bool> in_wp_vld;
	sc_in<bool> in_wp_rdy;





	//deklaracja funkcji
	void washer_main();


	//konstruktor
	SC_CTOR(washer) {

		SC_CTHREAD(washer_main, clk.pos());
		reset_signal_is(rst, true);

	}



};