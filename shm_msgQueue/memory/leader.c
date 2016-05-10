#include "func.h"

int main(){
	
	srand(time(NULL));

	
	int semc1start = semget(semc1, 1, 0); //reset c1
	if (semc1start<0){
		perror("err semaforo c1");
		exit(1);
	}

	int semc2start = semget(semc2, 1, 0); //reset c2
	if (semc2start<0){
		perror("err semaforo c2");
		exit(1);
	}

	int semc3start = semget(semc3, 1, 0); //reset c3
	if (semc3start<0){
		perror("err semaforo c3");
		exit(1);
	}



	int semc1done = semget(semc1fine, 1, 0);
	if (semc1done<0){
		perror("err");
		exit(1);
	}

	int semc2done = semget(semc2fine, 1, 0);
	if (semc2done<0){
		perror("err");
		exit(1);
	}

	int semc3done = semget(semc3fine, 1, 0);
	if (semc3done<0){
		perror("semget semc3done: ");
		exit(1);
	}



	int semR = semget(SEM_R, 1, 0);
	if (semR<0){
		perror("semget semR_leader: ");
		exit(1);
	}

	int shmid = shmget(shared_mem, 10*sizeof(int),0666 );
	if (shmid<0){
		perror("shmget memoria condivisa: ");
		exit(1);
	}

	int *puntMem=(int *) shmat(shmid, NULL, 0666);
	if (puntMem<0){
		perror("shmat puntMem: ");
		exit(1);
	}
	//scrivo su memoria condivisa
	int i =0;
	for(i=0;i<N;i++){
		
		printf("time %d :",i+1);
		
		puntMem[0]=(int)rand()%10;
		puntMem[1]=(int)rand()%10;
		puntMem[2]= (int)rand()%3;
		int operazione=puntMem[2];

		if(puntMem[2]==0)
		{
			printf(" SUM\n");
			printf("x = %d\n",puntMem[0]);
			printf("y = %d\n",puntMem[1]);
			
		}
		else if(puntMem[2]==1)
		{
			printf(" MOLT\n");
			printf("x = %d\n",puntMem[0]);
			printf("y = %d\n",puntMem[1]);
			
		}
		else{
			printf(" POW\n");
			printf("x = %d\n",puntMem[0]);
			printf("y = %d\n",puntMem[1]);
			
		}
		//faccio la signal ai semafori c1 c2 c3
		signalSem(semc1start);
		signalSem(semc2start);
		signalSem(semc3start);
		

		waitSem(semR);
		waitSem(semc1done);
		waitSem(semc2done);
		waitSem(semc3done);
		printf("risultato: %d\n ",puntMem[3]);
		printf("\n");
	}
	exit(0);
}
