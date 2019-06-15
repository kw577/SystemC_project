#include <systemc.h>


SC_MODULE(processor) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;
	

	sc_out< sc_int<8> >	outp;
	sc_out<bool> outp_vld;
	sc_in<bool> outp_rdy;


	



	//do komunikacji ze sliderami
	sc_in< sc_int<8> >		in_sp; 
	
	//handshaking with sliders
	sc_out<bool> in_sp_vld;
	sc_in<bool> in_sp_rdy;

	//do komunikacji z wyswietlaczem
	sc_out< sc_int<8> >		in_dp; 

	//do komunikacji z procesorem2
	sc_out< sc_int<8> >		in_pp; 
	sc_in<bool> in_pp_vld;
	sc_out<bool> in_pp_rdy;


	//handshaking with processor
	sc_in<bool> in_dp_vld;
	sc_out<bool> in_dp_rdy;



	//odbieranie danych od processor1
	sc_in< sc_int<8> >		out_pp; 
	sc_in<bool> out_pp_vld;
	sc_out<bool> out_pp_rdy;



	//deklaracja funkcji
	void processor_main();


	//konstruktor
	SC_CTOR(processor) {

		SC_CTHREAD(processor_main, clk.pos());
		reset_signal_is(rst, true);

	}



};