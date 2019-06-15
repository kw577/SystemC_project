#include <systemc.h>
#include "sliders.h"

//sliders main thread
void sliders::sliders_main(void)
{
	//Initialize handshake
	inp_rdy.write(0);

	in_sp_rdy.write(0);



	wait(); //czeka na sygnal zegara

	while (true) {

		sc_int<8> temp;

		//handshake - 1 - oznacza ze modul moze przyjac nowa porcje danych
		inp_rdy.write(1);

		do {
			wait();
		} while (!inp_vld.read());

		//odczytywanie wartosci z portu in
		temp = inp.read();

		cout << "sliders: Program id: " << (int)temp << endl;

		//handshake - na razie modul ie moze przyjac nowych danych
		inp_rdy.write(0);
				
				//wyslanie danych do procesora
				////przekazanie informacji ze modul ma nowe dane do wyslania
				in_sp_rdy.write(1);
				in_sp.write(temp);

				do {
					wait(); //czeka na zegar
				} while (!in_sp_vld.read());

				in_sp_rdy.write(0);


	}

}
