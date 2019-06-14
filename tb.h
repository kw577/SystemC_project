#include <systemc.h>

//Deklaracja modulu testowego testbench

SC_MODULE(tb)
{
	//deklaracja wejsc i wyjsc - nazewnictwo odrotnie jak dla moduly fir
	sc_in<bool>	clk; // wszedzie deklarowany jako sc_in
	sc_out<bool> rst; // deklarowany jako sc_in w fir.h
	sc_out< sc_int<16> > inp; //inp jest zadeklarowany w fih.h jako sc_in
	sc_in< sc_int<16> > outp; //outp jest zadeklarowany w fih.h jako sc_out

	//handshaking
	sc_out<bool> inp_vld;
	sc_in<bool> inp_rdy;
	sc_in<bool> outp_vld;
	sc_out<bool> outp_rdy;

	//funkcja produkujaca wartosci ktore zostana nastepnie wyslane do modulu fir
	void source();

	//Funkcja odbierajaca wartosci z modulu fir
	void sink();


	FILE* outfp;

	//konstruktor
	SC_CTOR(tb) {

		//procesy
		SC_CTHREAD(source, clk.pos()); // wyslanie sygnalow do modulu fir

		SC_CTHREAD(sink, clk.pos()); // odbior sygnalow z modulu fir


	}


};




