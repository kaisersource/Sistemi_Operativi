--------------------------
Compilazione ed esecuzione
--------------------------

Memoria condivisa e semafori	
-	cd memory; make && ./start


Code di messaggi e semafori 	
-	cd queue; make && ./start


--------------------------------------------------
Descrizione soluzione memoria condivisa e semafori
--------------------------------------------------

							Abbiamo deciso a priori di strutturare il programma in maniera modulare (descrizione di entrambe le tipologie di soluzione)
							func.h: definisce le strutture, funzioni, semafori ed eventuali parametri definiti a priori;
							func.c: implementa il codice delle funzioni definite nel file header
							leader.c contiene codice per: 
														   -generazione degli operandi e dell'operazione in maniera casuale, ripetuta per N=3   					
														   -comunicazione tra i processi operanti, regolata da semafori  
														   -output a video degli operandi e dell'operazione generati dal leader, con relativo risultato
															comunicato dal processo rispettivamente usando shared memory e code di messaggi
						
							sem.c contiene              :  -codice per la creazione dei semafori con relativi test
							start.c contiene            :  -codice per la creazione ed esecuzione dei processi con relativi test
							c1.c,c2.c,c3.c contengono   :  -codice d'esecuzione delle operazioni rispettivamente somma,prodotto e potenze.	
							
     	
