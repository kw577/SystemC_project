#include <systemc.h>


SC_MODULE(fir) {
	sc_in<bool>		clk;
	sc_in<bool>		rst;
	sc_in< sc_int<16> >		inp; //16 pinow na wejsciu
	sc_out< sc_int<16> >	outp;


	//handshaking
	sc_in<bool> inp_vld;
	sc_out<bool> inp_rdy;
	sc_out<bool> outp_vld;
	sc_in<bool> outp_rdy;



	//deklaracja funkcji
	void fir_main();


	//konstruktor
	SC_CTOR(fir) {

		//watek ponizej moze byc wykonywany wielokrotnie, moze zawierac petle
		SC_CTHREAD(fir_main, clk.pos());
		reset_signal_is(rst, true);

	}

	   

};
