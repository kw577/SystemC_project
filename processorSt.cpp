#include <systemc.h>
#include "processorSt.h"

//PROGAMY PRANIA
//0-brak, 1-pranie wstepne, 2 - pranie, 3 - odplamianie, 4 - plukanie, 5 - dodatkowe plukanie, 6 - wirowanie, 7 - koniec prania
int  processorSt::programs[][11]={	{1,1,2,2,2,4,4,5,5,6,7}, 
									{0,0,2,2,2,4,4,5,5,6,7}, 
									{0,0,2,2,2,4,4,0,0,6,7}, 
									{1,1,3,3,3,4,4,5,5,6,7}, 
									{1,1,3,3,3,4,4,5,5,0,7}};




//FIR main thread
void processorSt::processorSt_main(void)
{
	sc_int<8> temp;

	in_pp_vld.write(0);
	in_wp_rdy.write(0);
	out_pp_vld.write(0);

	out_pp.write(0);

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
		wait(50000);
		
		controlWashing(temp);

		//Przekazanie info ze procesor ma owe dane do wyslania
		out_pp_vld.write(1);
		out_pp.write(temp);

		do{
			wait();
		}while(out_pp_rdy.read());

		out_pp_vld.write(0);

	}

}


void processorSt::controlWashing(int prog){

		for(int i=0; i < 11; i++){
			//przekazanie info ze modul ma nowe dane do wyslania
			in_wp_rdy.write(1);
		
			in_wp.write(programs[prog][i]);

			

			do{
				wait();
			}while(!in_wp_vld.read());

			in_wp_rdy.write(0);

	//cout<<"-------------------------------------";

		}
}