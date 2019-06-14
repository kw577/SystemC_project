#include <systemc.h>


SC_MODULE(sliders) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;
	sc_in< sc_int<8> >		inp; //8 pinow na wejsciu
	sc_out< sc_int<8> >	outp;


	//handshaking
	sc_in<bool> inp_vld;
	sc_out<bool> inp_rdy;
	sc_out<bool> outp_vld;
	sc_in<bool> outp_rdy;



	//deklaracja funkcji
	void sliders_main();


	//konstruktor
	SC_CTOR(sliders) {

		//watek ponizej moze byc wykonywany wielokrotnie, moze zawierac petle
		SC_CTHREAD(sliders_main, clk.pos());
		reset_signal_is(rst, true);

	}

	   

};
