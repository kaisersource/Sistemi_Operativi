#include "func.h"

int main(){

	srand(time(NULL)); //inizio lavoro del padre
	int semc1start = semget(SEMC1, 1, 0); //reimposto i semafori
	if (semc1start<0){
		perror("semget semPartiC1: ");
		exit(-1);
	}

	int semc2start = semget(SEMC2, 1, 0);
	if (semc2start<0){
		perror("semget semPartiC2: ");
		exit(-1);
	}

	int semc3start = semget(SEMC3, 1, 0);
	if (semc3start<0){
		perror("semget semPartiC3: ");
		exit(-1);
	}
//-----------------------------------------------------------------
	int semc1done = semget(SEMC1FINE, 1, 0);
	if (semc1done<0){
		perror("semget semFattoC1: ");
		exit(-1);
	}

	int semc2done = semget(SEMC2FINE, 1, 0);
	if (semc2done<0){
		perror("semget semFattoC2: ");
		exit(-1);
	}

	int semc3done = semget(SEMC3FINE, 1, 0);
	if (semc3done<0){
		perror("semget semFattoC3: ");
		exit(-1);
	}

	int semc1read = semget(SEMC1READ, 1, 0);
	if (semc1read<0){
		perror("Errore lettura C1");
		exit(-1);
	}

	int semc2read = semget(SEMC2READ, 1, 0);
	if (semc2read<0){
		perror("Errore lettura C2");
		exit(-1);
	}

	int semc3read = semget(SEMC3READ, 1, 0);
	if (semc3read<0){
		perror("Errore lettura C3");
		exit(-1);
	}

	int semc1calc = semget(SEMC1CALC, 1, 0);
	if (semc1calc<0){
		perror("Errore creazione semaforo SEMC1CALC");
		exit(-1);
	}

	int semc2calc = semget(SEMC2CALC, 1, 0);
	if (semc2calc<0){
		perror("Errore creazione semaforo SEMC2CALC");
		exit(-1);
	}

	int semc3calc = semget(SEMC3CALC, 1, 0);
	if (semc3calc<0){
		perror("Errore creazione semaforo SEMC3CALC");
		exit(-1);
	}

	int semR = semget(SEM_R, 1, 0);
	if (semR<0){
		perror("Errore creazione semaforo SEM_R");
		exit(-1);
	}

        
	int queue = cr_queue(QUEUE);	
	if(queue<0){
		printf("Errore acquisizione coda messaggi");
		exit(-1);
	}
	struct text *q=malloc(sizeof(struct text));

        
	int i=0;
	for(i=0;i<N;i++){

		
            printf("\n numero operazione: %d ", i+1);
            
		int x=rand()%11;
		int y=rand()%11;
		int op=rand()%3;
               
		if(op==SUM){
			printf("\n Tipo operazione: SOMMA \n");

		}
		else if(op==MOL) {
			printf("\n Tipo operazione: MOLTIPLICAZIONE \n");
		}
		else if(op==POW) {
			printf("\n Tipo operazione: POTENZA \n");
		}
		

		write_message(queue,q,x,y,op,1); //Scrivo nella coda
		write_message(queue,q,x,y,op,1);
		write_message(queue,q,x,y,op,1);
                
		signalSem(semc1start);
		signalSem(semc2start);
		signalSem(semc3start);

		waitSem(semc1read); //Attesa degli altri processi
		waitSem(semc2read);
		waitSem(semc3read);

		signalSem(semc1calc); //notifico a c1 che può svolgere la somma
		signalSem(semc2calc);//notifico a c2 che può svolgere la moltiplicazione
		signalSem(semc3calc);//notifico a c3 che può svolgere la potenza

		waitSem(semR);
		recive_msg(queue,q);
		waitSem(semc1done);
		waitSem(semc2done);
		waitSem(semc3done);
                printf(" Valori x: %d  y: %d \n",x,y);
		printf(" RISULTATO = %d \n",q->res);
	}
	free(q);
exit(0);}
