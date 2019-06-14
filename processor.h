#include <systemc.h>


SC_MODULE(processor) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;

	//do komunikacji ze sliderami
	sc_in< sc_int<8> >		in_sp; 
	
	//handshaking with sliders
	sc_out<bool> in_sp_vld;
	sc_in<bool> in_sp_rdy;

	//do komunikacji z wyswietlaczem
	sc_out< sc_int<8> >		in_dp; 
	//handshaking with processor
	sc_in<bool> in_dp_vld;
	sc_out<bool> in_dp_rdy;


	//deklaracja funkcji
	void processor_main();


	//konstruktor
	SC_CTOR(processor) {

		SC_CTHREAD(processor_main, clk.pos());
		reset_signal_is(rst, true);

	}



};