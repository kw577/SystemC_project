#include <systemc.h>
#include "sliders.h"
#include "testbench.h"
#include "processor.h"
#include "display.h"
#include "processorSt.h"
#include "washer.h"



SC_MODULE(SYSTEM) {

	//instacje modulow
	testbench *tb0;
	sliders* sliders0;
	processor* processor1;
	processorSt* processor2;
	display* display1;
	washer* washer1;

	//deklaracje sygnalow miedzy tb0 i sliders
	sc_signal<bool> rst_sig;

	sc_signal< sc_int<8> >		inp_sig;
	sc_signal<bool>				inp_sig_vld;  //handshaking signal
	sc_signal<bool>				inp_sig_rdy;  //handshaking signal

	sc_signal< sc_int<8> >		outp_sig;
	sc_signal<bool>				outp_sig_vld;  //handshaking signal
	sc_signal<bool>				outp_sig_rdy;  //handshaking signal


	//deklaracje sygnalow miedzy processor1 i sliders
	sc_signal< sc_int<8> >      in_sp_signal;
	sc_signal<bool>				in_sp_rdy_signal;  //handshaking signal
	sc_signal<bool>				in_sp_vld_signal;  //handshaking signal
	
	//deklaracje sygnalow miedzy processor1 i display
	sc_signal< sc_int<8> >      in_dp_signal;
	sc_signal<bool>				in_dp_rdy_signal;  //handshaking signal
	sc_signal<bool>				in_dp_vld_signal;  //handshaking signal

	//deklaracje sygnalow miedzy processor1 i processor2
	sc_signal< sc_int<8> >      in_pp_signal;
	sc_signal<bool>				in_pp_rdy_signal;  //handshaking signal
	sc_signal<bool>				in_pp_vld_signal;  //handshaking signal

	//deklaracje sygnalow miedzy processor2 i washer
	sc_signal< sc_int<8> >      in_wp_signal;
	sc_signal<bool>				in_wp_rdy_signal;  //handshaking signal
	sc_signal<bool>				in_wp_vld_signal;  //handshaking signal


	//ZEGAR SYSTEMOWY
	sc_clock clk_sig;


	//konstruktor
	SC_CTOR(SYSTEM):clk_sig("clk_sig", 10, SC_NS)   //SC_NS - nonosekundy (10) - system dziala w trybie 10ns
	{
		//deklaracja instancji modulu testbench
		tb0 = new testbench("tb0");
		//polaczenie modulu z zegarem
		tb0->clk(clk_sig);

		//polaczenie modulu z sygnalami
		tb0->rst(rst_sig);
		tb0->inp(inp_sig);
		tb0->inp_vld(inp_sig_vld); //handshaking signal
		tb0->inp_rdy(inp_sig_rdy); //handshaking signal
		tb0->outp(outp_sig);
		tb0->outp_vld(outp_sig_vld); //handshaking signal
		tb0->outp_rdy(outp_sig_rdy); //handshaking signal


		//////////////////////////////////////
		//deklaracja instancji modulu
		sliders0 = new sliders("sliders0");
		
		//polaczenie modulu z zegarem
		sliders0->clk(clk_sig);

		//polaczenie modulu z sygnalami
		sliders0->rst(rst_sig);
		sliders0->inp(inp_sig);
		sliders0->inp_vld(inp_sig_vld); //handshaking signal
		sliders0->inp_rdy(inp_sig_rdy); //handshaking signal

		
		sliders0->in_sp(in_sp_signal); // pol z procesorem
		
		sliders0->in_sp_rdy(in_sp_rdy_signal); //handshaking signal
		sliders0->in_sp_vld(in_sp_vld_signal); //handshaking signal

		//////////////////////////////////////
		//deklaracja instancji modulu
		processor1 = new processor("processor1");
		
		//polaczenie modulu z zegarem
		processor1->clk(clk_sig);

		//polaczenie modulu z sygnalami
		processor1->rst(rst_sig);
		processor1->in_sp(in_sp_signal);
	
		processor1->outp(outp_sig);
		processor1->outp_vld(outp_sig_vld); //handshaking signal
		processor1->outp_rdy(outp_sig_rdy); //handshaking signal

		processor1->in_sp_rdy(in_sp_rdy_signal); //handshaking signal
		processor1->in_sp_vld(in_sp_vld_signal); //handshaking signal

		processor1->in_dp(in_dp_signal);
	
		processor1->in_dp_rdy(in_dp_rdy_signal); //handshaking signal
		processor1->in_dp_vld(in_dp_vld_signal); //handshaking signal

		//komunikacja processor1 - processor2
		processor1->in_pp(in_pp_signal);
		processor1->in_pp_rdy(in_pp_rdy_signal); //handshaking signal
		processor1->in_pp_vld(in_pp_vld_signal); //handshaking signal

		//////////////////////////////////////
		//deklaracja instancji modulu
		display1 = new display("display1");
		
		//polaczenie modulu z zegarem
		display1->clk(clk_sig);

		//polaczenie modulu z sygnalami
		display1->rst(rst_sig);
		display1->in_dp(in_dp_signal);
	
		display1->in_dp_rdy(in_dp_rdy_signal); //handshaking signal
		display1->in_dp_vld(in_dp_vld_signal); //handshaking signal


		//////////////////////////////////////
		//deklaracja instancji modulu
		processor2 = new processorSt("processor2");
		
		//polaczenie modulu z zegarem
		processor2->clk(clk_sig);

		//polaczenie modulu z sygnalami
		processor2->rst(rst_sig);
		processor2->in_pp(in_pp_signal);
	
		processor2->in_pp_rdy(in_pp_rdy_signal); //handshaking signal
		processor2->in_pp_vld(in_pp_vld_signal); //handshaking signal

		//komunikacja processor2 - pralka
		processor2->in_wp(in_wp_signal);
		processor2->in_wp_rdy(in_wp_rdy_signal); //handshaking signal
		processor2->in_wp_vld(in_wp_vld_signal); //handshaking signal

	
		//////////////////////////////////////
		//deklaracja instancji modulu
		washer1 = new washer("washer1");
		
		//polaczenie modulu z zegarem
		washer1->clk(clk_sig);

		//polaczenie modulu z sygnalami
		washer1->rst(rst_sig);
		washer1->in_wp(in_wp_signal);
	
		washer1->in_wp_rdy(in_wp_rdy_signal); //handshaking signal
		washer1->in_wp_vld(in_wp_vld_signal); //handshaking signal



		

	}

	//Destruktor - nie jest wymagany
	~SYSTEM() {
		delete tb0;
		delete sliders0;
		delete processor1;
		delete display1;
		delete processor2;
		delete washer1;
	}


};

SYSTEM* top = NULL;

int sc_main(int argc, char* argv[]) {

	//deklaracja instancji modulu SYSTEM
	top = new SYSTEM("top");

	//rozpoczecie symulacji
	sc_start();

	return 0;
}