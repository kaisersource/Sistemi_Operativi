MAKEFILE : -src/: contiene i sorgenti
	   -bin/: contiene gli object
	   -exe/: contiene gli "eseguibili"
Il comando make compila e linka, spostando i file sulle opportune directories ed eseguendo successivamente il leader

Leader : genera 3 numeri casualmente, x (da 0 a 9), y ( da 0 a 9), op (da 0 a 2) memorizzati poi in un vettore. La gestione della comunicazione 
	 client/server avviene tramite system call send e recv con cui viene gestita la trasmissione del vettore (una send broadcast 
	 da server e recv dai client), e del risultato (send dal client corrispettivo al numero generato da op e recv dal server).
		
c1	: client che esegue la somma
c2	: client che esegue la moltiplicazione
c3	: client che esegue la potenza

Segnali:
	i client ignorano la SIGINT mentre il server si comporta diversamente, eseguendo una unlink del socket e restituendo un errore. 

