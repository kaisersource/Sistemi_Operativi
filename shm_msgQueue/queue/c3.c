#include "func.h"
int main(){
	
	int semc3start = semget(SEMC3, 1, 0);
	if (semc3start<0){
		perror("Errore semaforo C3: ");
		exit(-1);
	}

	int semc3done = semget(SEMC3FINE, 1, 0);
	if (semc3done<0){
		perror("Errore semaforo C3: ");
		exit(-1);
	}

	int semc3read = semget(SEMC3READ, 1, 0);
	if (semc3read<0){
		perror("Errore creazione semaforo ");
		exit(-1);
	}

	int semc3calc = semget(SEMC3CALC, 1, 0);
	if (semc3calc<0){
		perror("Errore creazione semaforo C3");
		exit(-1);
	}

	int semR = semget(SEM_R, 1, 0);
	if (semR<0){
		perror("errore creazione semaforo SEM_R ");
		exit(-1);
	}

	int queue = cr_queue(QUEUE);	
	if(queue<0){
		printf("Errore di acquisizione nella coda messaggi \n");
		exit(-1);
	}

	struct text *q=malloc(sizeof(struct text));
		
	int i =0;
	for(i=0;i<N;i++){
		int pow=1;
		waitSem(semc3start);
		recive_msg(queue,q);
		//printf("\n VALORI: x: %d y: %d \n",q->x,q->y);
		signalSem(semc3read);
		waitSem(semc3calc);
		if(POW==q->op){
			int i=0;
			for(i=0;i<q->y;i++){
				pow=pow*q->x;
			}

			write_message(queue,q,0,0,-1,pow);
			signalSem(semR);
		}
		signalSem(semc3done);
	}
	free(q);
        exit(0);
}