#include <systemc.h>

//Deklaracja modulu testowego testbench

SC_MODULE(testbench)
{

	//deklaracja wejsc i wyjsc 
	sc_in<bool>	clk; 
	sc_out<bool> rst; 
	sc_out< sc_int<8> > inp; 
	sc_in< sc_int<8> > outp; 

	//handshaking
	sc_out<bool> inp_vld;
	sc_in<bool> inp_rdy;
	sc_in<bool> outp_vld;
	sc_out<bool> outp_rdy;

	//funkcja produkujaca wartosci ktore zostana nastepnie wyslane do modulu sliders
	void source();

	//Funkcja odbierajaca wartosci z modulu sliders
	void sink();


	FILE* outfp;

	//konstruktor
	SC_CTOR(testbench) {

		//procesy
		SC_CTHREAD(source, clk.pos()); // wyslanie sygnalow do modulu sliders

		SC_CTHREAD(sink, clk.pos()); // odbior sygnalow z modulu sliders


	}


};




