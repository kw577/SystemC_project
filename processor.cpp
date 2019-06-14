#include <systemc.h>
#include "processor.h"

//FIR main thread
void processor::processor_main(void)
{
	sc_int<8> temp;


	//Resetowanie wyjscia
	out_sld.write(0);
	wait(); //czeka na sygnal zegara

	while (true) {

		
		//odczytywanie wartosci z portu in
		temp = in_sld.read();

		out_sld.write(temp);
		wait(); //czeka na zegar

	}

}