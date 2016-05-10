#include "func.h"
int main(){


	//settaggio semafori
	int semc1start = semget(semc1, 1, 0);
	if (semc1start<0)
	{
		perror("err");
		exit(1);
	}

	int semc1done = semget(semc1fine, 1, 0);
	if (semc1done<0)
	{
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
		exit(-1);
	}


	int *puntMem=(int *) shmat(shmid, NULL, 0666); //collega alla memoria condivisa
	if (puntMem<0)
	{
		perror("err");
		exit(-1);
	}
//operazione
	int i=0;
	for(i=0;i<N;i++)
	{
		waitSem(semc1start);

		if(SUM==puntMem[2]){
			puntMem[3]=puntMem[0]+puntMem[1]; //SUM
			signalSem(semR); //vado al leader
		}
		signalSem(semc1done);// notifico al leader la terminazione di c2
	}
	exit(0);
}
