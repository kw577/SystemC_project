#include <systemc.h>
#include "processor.h"

//FIR main thread
void processor::processor_main(void)
{
	sc_int<8> temp;


	//Resetowanie wyjscia
	in_sp_vld.write(0);
	in_dp_rdy.write(0);
	in_pp_rdy.write(0);
	outp_vld.write(0);
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
		
		cout << "\tprocessor: uruchomiono program id: " << (int)temp << endl;

		//na razie modul nie moze przyjac nowych danych
		in_sp_vld.write(0);

			//przekazanie info  do wyswietlacza ze modul ma nowe dane do wyslania
			in_dp_rdy.write(1);

			in_dp.write(temp);

			do{
				wait();
			}while(!in_dp_vld.read());

			in_dp_rdy.write(0);


			//przekazanie info  do processora2 ze modul ma nowe dane do wyslania
			in_pp_rdy.write(1);

			in_pp.write(temp);

			do{
				wait();
			}while(!in_pp_vld.read());

			in_pp_rdy.write(0);

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