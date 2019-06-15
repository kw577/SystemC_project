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

		//modul nie moze w tym momencie przyjac danych
		in_wp_vld.write(0);

		if((int)temp == 1){
			cout << "\t\t\t\tPralka: Pranie wstepne" << endl;
			wait(50000);
		}
		else if((int)temp == 2){
			cout << "\t\t\t\tPralka: Pranie" << endl;
			wait(50000);
		}
		else if((int)temp == 3){
			cout << "\t\t\t\tPralka: Odplamianie" << endl;
			wait(50000);
		}
		else if((int)temp == 4){
			cout << "\t\t\t\tPralka: Plukanie" << endl;
			wait(50000);
		}
		else if((int)temp == 5){
			cout << "\t\t\t\tPralka: Dodatkowe plukanie" << endl;
			wait(50000);
		}
		else if((int)temp == 6){
			cout << "\t\t\t\tPralka: Wirowanie" << endl;
			wait(50000);
		}
		else if((int)temp == 7){
			cout << "\t\t\t\tPralka: ---KONIEC PRANIA---" << endl;
			wait(50000);
		}

	}

}