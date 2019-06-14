#include <systemc.h>
#include "processor.h"

//FIR main thread
void processor::processor_main(void)
{
	sc_int<8> temp;


	//Resetowanie wyjscia
	in_sp_vld.write(0);



	wait(); //czeka na sygnal zegara

	while (true) {

		
		//odczytywanie wartosci z portu in
		temp = in_sp.read();


		//wyslanie info ze modul oczekuje na dane
		in_sp_vld.write(1);

		//oczekiwanie na dane
		do {
			wait();

		}while(!in_sp_rdy.read());

		//odczytanie wartosci z portu
		temp = in_sp.read();
		
		cout << "\tprocessor: uruchomiono program id: " << (int)temp << endl;

		//na razie modul nie moze przyjac nowych danych
		in_sp_vld.write(0);

		//out_sld.write(temp);
		wait(); //czeka na zegar

	}

}