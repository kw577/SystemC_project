#include "tb.h"

//funkcja wysylajaca dane do modulu fir
void tb::source() {

	//resetowanie wejsc i wyjsc
	inp.write(0);
	inp_vld.write(0);
	rst.write(1);
	wait(); //czeka do nastepnego cyklu zegara
	rst.write(0); //do resetu nalezy najpierw wyslac 1 potem 0 - dopiero wtedy sygnal reset jest zakonczony
	wait();

	sc_int<16> tmp;

	//wyslanie przykladowego sygnalow do modulu fir
	for (int i = 0; i < 64; i++)
	{
		//przyjete przykladowe wartosci do wyslania do modulu fir
		if (i > 23 && i < 29)
			tmp = 256;
		else
			tmp = 0;

		inp_vld.write(1);

		//zapis sygnalu do wyjscia - polaczonego sygnalem z wejsciem modulu fir o nazwie inp
		inp.write(tmp); 

		

		//czeka na sygnal handshake
		do {
			wait();
		} while (!inp_rdy.read());

		inp_vld.write(0);
	}

	//zapobieganie zawieszania sie procesu symulacji
	wait(10000);
	printf("Hanging simulation stopped by TB source thread.\n");
	sc_stop();

}


// funkjca pobierajaca wartosci zwrotne z modulu fir
void tb::sink() {

	sc_int<16> indata;

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


	//funckja source wysyla 64 sygnaly zatem funkcja sink powinna odebrac rowniez 64 sygnaly
	for (int i = 0; i < 64; i++) {

		outp_rdy.write(1);
		do {
			wait();
		} while (!outp_vld.read());

		//czyta odpowiedz od modulu fir
		indata = outp.read();

		outp_rdy.write(0);
		//wait();

		//zapisanie wynikow
		fprintf(outfp, "%d\n", (int)indata);
		cout << i << " : \t" << (int)indata << endl;


	}

	//zakonczenie symulacji i uruchomienie destruktorow modulow
	fclose(outfp);
	sc_stop();

}