#include <systemc.h>
#include "processor.h"

//FIR main thread
void processor::processor_main(void)
{
	sc_int<8> temp;
	sc_int<8> temp2;

	//Resetowanie wyjscia
	in_sp_vld.write(0);
	in_dp_rdy.write(0);
	in_pp_rdy.write(0);
	outp_vld.write(0);
	out_pp_rdy.write(0);
	outp.write(0);

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
		
		cout << "\tProcessor1: uruchomiono program id: " << (int)temp << endl;

		//na razie modul nie moze przyjac nowych danych
		in_sp_vld.write(0);
		wait(50000);
			//przekazanie info  do wyswietlacza ze modul ma nowe dane do wyslania
			in_dp_rdy.write(1);

			in_dp.write(temp);

			do{
				wait();
			}while(!in_dp_vld.read());

			in_dp_rdy.write(0);



			if(temp >= 0 && temp < 5){
			//przekazanie info  do processora2 ze modul ma nowe dane do wyslania
			in_pp_rdy.write(1);

			in_pp.write(temp);

			do{
				wait();
			}while(!in_pp_vld.read());

			in_pp_rdy.write(0);


			//odbior danych od processor2
			out_pp_rdy.write(1);

			do{
				wait();
			}while(!out_pp_vld.read());

			temp2 = out_pp.read();

			out_pp_rdy.write(0);

			cout << "\t\t\t\tProcessor1: ---KONIEC PROGRAMU PRANIA---" << endl;
			wait(50000);


			//przekazanie info  do wyswietlacza ze modul ma nowe dane do wyslania
			in_dp_rdy.write(1);

			in_dp.write(20);//20 to sygnal zakonczenia prania

			do{
				wait();
			}while(!in_dp_vld.read());

			in_dp_rdy.write(0);

			}


		//przekazanie informacji ze modul ma nowe dane do wyslania
		outp_vld.write(1);
		
		outp.write(temp); // zapisanie wartosci na wyjscie

		do {
			wait(); //czeka na zegar
		} while (!outp_rdy.read());

		outp_vld.write(0);

		//out_sld.write(temp);
		wait(); //czeka na zegar

	}

}