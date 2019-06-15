#include "testbench.h"

//funkcja wysylajaca dane do modulu sliders
void testbench::source() {

	completed = 0;
	//resetowanie wejsc i wyjsc
	inp.write(0);
	inp_vld.write(0);
	outp_rdy.write(0);
	rst.write(1);
	wait(); //czeka do nastepnego cyklu zegara
	rst.write(0); //reset done
	wait();

	sc_int<8> tmp;
	sc_int<8> indata;
	//wyslanie kolejnych identyfikatorow programu
	for (int i = 0; i <= 4; i++)
	{
		
		//numer programu pralki
		tmp = i;

		//sprawdzenie obslugi bledow - pralka ma zaprogramowane tylko 5 prgramow (id: 0 - 4)
		if(i == 2) tmp = 8; 


		//if(tmp == 0) tmp=1;

		inp_vld.write(1);

		//zapis sygnalu do wyjscia 
		inp.write(tmp); 

		//czeka na sygnal handshake
		do {
			wait();
		} while (!inp_rdy.read());

		inp_vld.write(0);




		//odbior sygnalu

		outp_rdy.write(1);
		do {
			wait();
		} while (!outp_vld.read());

		//czyta odpowiedz od modulu processor1
		indata = outp.read();

		outp_rdy.write(0);


		//zapisanie wynikow
		//fprintf(outfp, "\t\t\t\tZakonczono program id: %d\n", (int)indata);
		cout << "\t\t\t\t\tZakonczono program id: " << (int)indata << endl;

















	}

	

	//czeka na zakonczenie symulacji
	

	cout << "ZAKONCZONO SYMULACJE" << endl;

	sc_stop();

}


