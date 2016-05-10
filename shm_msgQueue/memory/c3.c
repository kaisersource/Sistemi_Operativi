#include "func.h"
int main(){
	
	//settaggio semafori
	int semc3start = semget(semc3, 1, 0);
	if (semc3start<0)
	{
		perror("semget semc3start: ");
		exit(1);
	}

	int semc3done = semget(semc3fine, 1, 0);
	if (semc3done<0)
	{
		perror("error generating semc3done: ");
		exit(1);
	}

	int semR = semget(SEM_R, 1, 0);
	if (semR<0)
	{
		perror("error generating semR: ");
		exit(1);
	}
	int i=0;

	int shmid = shmget(shared_mem, 10*sizeof(int),0666 );
	if (shmid<0)
	{
		perror("errore shmget memoria condivisa: ");
		exit(1);
	}

	int *puntMem=(int *) shmat(shmid, NULL, 0666);
	if (puntMem<0)
	{
		perror("errore puntmem");
		exit(1);
	}
	//operazione
	for(i=0;i<N;i++)
	{
		
		waitSem(semc3start);
	
		if(POW==puntMem[2])
		{
			//faccio operazione
			int i=0;
			int prodotto=1;
			for(i=0;i<puntMem[1];i++){ //POW
				prodotto=prodotto*puntMem[0]; 
			}
			puntMem[3]=prodotto;
		
			signalSem(semR); //vado dal leader
		
		}
		signalSem(semc3done); ////notifico al leader la terminazione di c3
	}
	exit(0);
}
