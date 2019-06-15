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

		if(temp == 0 ){
			cout << "\t\tDisplay: Program: ZRASZANIE" << endl;
		}
		else if(temp == 1 ){
			cout << "\t\tDisplay: Program: WODA 1/3" << endl;
		}
		else if(temp == 2 ){
			cout << "\t\tDisplay: Program: WODA 1/2" << endl;
		}
		else if(temp == 3 ){
			cout << "\t\tDisplay: Program: WODA 3/4" << endl;
		}
		else if(temp == 4 ){
			cout << "\t\tDisplay: Program: WODA 1/1" << endl;
		}

		else if(temp == 20){

			cout << "\t\tDisplay: --END--" << endl;

		} else{

			cout << "\t\tDisplay: --ERROR--" << endl;
		}

		

		

		in_dp_vld.write(0);
	}

} 