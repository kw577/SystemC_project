#include <systemc.h>
#include "washer.h"

//FIR main thread
void washer::washer_main(void)
{
	sc_int<8> temp;

	in_wp_vld.write(0);

	//Resetowanie wyjscia
	//out_sld.write(0);
	wait(); //czeka na sygnal zegara

	while (true) {


		//modul moze przyjac kolejna porcje danych
		in_wp_vld.write(1);

		do{
			wait();
		}while(!in_wp_rdy.read());

		//odczytanie wartosci z portu
		temp = in_wp.read();

		cout << "\t\t\t\tpralka: Program id: " << (int)temp << endl;

		in_wp_vld.write(0);

	}

}