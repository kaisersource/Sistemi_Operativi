#include "func.h"
int main(){
	
	
    //settaggio semafori
	int semc2start = semget(semc2, 1, 0);
	if (semc2start<0){
		perror("err ");
		exit(1);
	}

	int semc2done = semget(semc2fine, 1, 0);
	if (semc2done<0){
		perror("err");
		exit(1);
	}

	int semR = semget(SEM_R, 1, 0);
	if (semR<0){
		perror("err");
		exit(1);
	}

	int shmid = shmget(shared_mem, 10*sizeof(int),0666 );
	if (shmid<0){
		perror("err");
		exit(1);
	}

	int *puntMem=(int *) shmat(shmid, NULL, 0666);
	if (puntMem<0)
	{
		perror("err");
		exit(1);
	}

	int i=0;

	//operazione
	for(i=0;i<N;i++){
		
		waitSem(semc2start);
		
		if(MOLT==puntMem[2]) //se puntmem si riferisce alla moltiplicazione
		{
			
			puntMem[3]=puntMem[0]*puntMem[1]; //allora la eseguo
			
			signalSem(semR); //notifico al leader dell'avvenuta moltiplicazione
			
		}
		signalSem(semc2done); //notifico al leader la terminazione di c2
	}
	exit(0);
}
