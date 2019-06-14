#include <systemc.h>


SC_MODULE(processor) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;
	//do komunikacji ze sliderami
	sc_in< sc_int<8> >		in_sld; 
	sc_out< sc_int<8> >		out_sld;

	//deklaracja funkcji
	void processor_main();


	//konstruktor
	SC_CTOR(processor) {

		SC_CTHREAD(processor_main, clk.pos());
		reset_signal_is(rst, true);

	}



};