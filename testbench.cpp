#include "testbench.h"

//funkcja wysylajaca dane do modulu sliders
void testbench::source() {

	//resetowanie wejsc i wyjsc
	inp.write(0);
	inp_vld.write(0);
	rst.write(1);
	wait(); //czeka do nastepnego cyklu zegara
	rst.write(0); //reset done
	wait();

	sc_int<8> tmp;

	//wyslanie kolejnych identyfikatorow programu
	for (int i = 0; i <= 4; i++)
	{
		
		//numer programu pralki
		tmp = 2*i;
		if(tmp == 0) tmp=1;


		inp_vld.write(1);

		//zapis sygnalu do wyjscia 
		inp.write(tmp); 

		

		//czeka na sygnal handshake
		do {
			wait();
		} while (!inp_rdy.read());

		inp_vld.write(0);
	}

	//zapobieganie zawieszania sie procesu symulacji
	wait(5000);
	printf("Hanging simulation stopped by testbench source thread.\n");
	sc_stop();

}


// funkjca pobierajaca wartosci zwrotne z modulu sliders
void testbench::sink() {

	sc_int<8> indata;

	///////////////
	//Zapisanie danych symulacji do pliku
	char output_file[256];
	sprintf(output_file, "./output.dat");
	outfp = fopen(output_file, "wb");
	if(outfp == NULL)
	{
		printf("Couldn't open output.dat for writting.\n");
		exit(0);
	}
	///////////////
	

	//Initialize handshake port
	outp_rdy.write(0);


	//odbior tylu sygnalow ile wyslala funkcja source
	for (int i = 0; i < 64; i++) {

		outp_rdy.write(1);
		do {
			wait();
		} while (!outp_vld.read());

		//czyta odpowiedz od modulu sliders
		indata = outp.read();

		outp_rdy.write(0);
		//wait();

		//zapisanie wynikow
		fprintf(outfp, "\t\t\t\tZakonczono program id: %d\n", (int)indata);
		cout << "\t\t\t\t\tZakonczono program id: " << (int)indata << endl;


	}

	//zakonczenie symulacji i uruchomienie destruktorow modulow
	fclose(outfp);
	sc_stop();

}