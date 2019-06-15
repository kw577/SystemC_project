#include <systemc.h>
#include "processorSt.h"

//FIR main thread
void processorSt::processorSt_main(void)
{
	sc_int<8> temp;

	in_pp_vld.write(0);
	in_wp_rdy.write(0);
	//Resetowanie wyjscia
	//out_sld.write(0);
	wait(); //czeka na sygnal zegara

	while (true) {


		//modul moze przyjac kolejna porcje danych
		in_pp_vld.write(1);

		do{
			wait();
		}while(!in_pp_rdy.read());

		//odczytanie wartosci z portu
		temp = in_pp.read();

		cout << "\t\t\tprocessor2: Program id: " << (int)temp << endl;

		in_pp_vld.write(0);

			//przekazanie info ze modul ma nowe dane do wyslania
			in_wp_rdy.write(1);

			in_wp.write(temp);

			do{
				wait();
			}while(!in_wp_rdy.read());

			in_wp_rdy.write(0);

	}

}