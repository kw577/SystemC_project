#include <systemc.h>
#include "display.h"

//FIR main thread
void display::display_main(void)
{
	sc_int<8> temp = 0;
	int tick = 0;
	in_dp_vld.write(0);

	//Resetowanie wyjscia
	//out_sld.write(0);
	wait(); //czeka na sygnal zegara

	while (true) {


		//modul moze przyjac kolejna porcje danych
		in_dp_vld.write(1);

		do{
			wait();
			//if(temp!=0){
			//	cout << "\t\tdisplay: Program id: " << (int)temp << endl;
			//}
		}while(!in_dp_rdy.read());

		//odczytanie wartosci z portu
		temp = in_dp.read();

		

		cout << "\t\tdisplay: Program id: " << (int)temp << endl;

		in_dp_vld.write(0);
	}

} 