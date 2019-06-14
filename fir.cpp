#include <systemc.h>
#include "fir.h"

//FIR main thread
void fir::fir_main(void)
{
	sc_int<16> taps[5];

	//reset
	for (int i = 0; i < 5; i++) {
		taps[i] = 0;

	}

	//Initialize handshake
	inp_rdy.write(0);
	outp_vld.write(0);

	//Resetowanie wyjscia
	outp.write(0);
	wait(); //czeka na sygnal zegara

	while (true) {

		sc_int<16> in_val;
		sc_int<16> out_val;

		//handshake - 1 - oznacza ze modul moze przyjac nowa porcje danych
		inp_rdy.write(1);

		do {
			wait();
		} while (!inp_vld.read());

		//odczytywanie wartosci z portu in
		in_val = inp.read();

		//handshake - na razie modul ie moze przyjac nowych danych
		inp_rdy.write(0);

		//read input into shift register
		for (int i = 4; i > 0; i--) {
			taps[i] = taps[i - 1];
			
		}
		taps[0] = in_val;
		

		//deklaracja tymczasowej zmiennej do przechowywania wartosci
		sc_int<16> val;

		for (int i = 0; i < 5; i++) {
			//val += coef[i] * taps[i];
			val +=2 * taps[i];
		}


		//przekazanie informacji ze modul ma nowe dane do wyslania
		outp_vld.write(1);
		
		outp.write(val); // zapisanie wartosci na wyjscie

		do {
			wait(); //czeka na zegar
		} while (!outp_rdy.read());

		outp_vld.write(0);
	}

}
