#include "func.h"

int main(){	
	//settaggio semafori
	if (initsem(semc1,0)<0)
	{
		printf("Creazione semaforo semc1: Fallita\n");
		exit(-1);	
	}
	if (initsem(semc2,0)<0)
	{
		printf("Creazione semaforo semc2: Fallita\n");
		exit(-1);
	}
	if (initsem(semc3,0)<0)
	{
		printf("Creazione semaforo semc3: Fallita\n");
		exit(-1);
	}
	if (initsem(semc1fine,0)<0)
	{
		printf("Creazione semaforo semc1fine: Fallita\n");
		exit(-1);
	}
	if (initsem(semc2fine,0)<0)
	{
		printf("Creazione semaforo semc2fine: Fallita\n");
		exit(-1);
	}
	if (initsem(semc3fine,0)<0)
	{
		printf("Creazione semaforo semc3fine: Fallita\n");
		exit(-1);
	}

	if (initsem(SEM_R,0)<0)
	{
		printf("err creazione sem_R\n");
		exit(-1);
	}
	//settaggio shared memory
	int idMem = initMemoria(shared_mem);	
	if (idMem<0){
		printf("err creazione memoria condivisa");
		exit(-1);
	}
	int *puntMem = (int *) shmat(idMem, NULL, 0);	//puntatore alla memoria condivisa
	if (puntMem<0){
		perror("error shmat");
		exit(-1);
	}
	//inizializzazione x,y,op,res
	puntMem[0] = 1; 
	puntMem[1] = 1; 
	puntMem[2] = 1; 
	puntMem[3] = 1; 
	exit(0);
}

int initsem(key_t semkey, int init) {
	int status = 0, semid;
	semun arg;
	arg.val = init;
	semid = semget(semkey, 1, SEMXXX | IPC_CREAT | IPC_EXCL);
	if (semid<0)
 	{
		if (errno == EEXIST)
		{ 
			semid = semget(semkey, 1, 0);
			if (semid<0)
				perror("errore semget");
			//resetto i semafori se già esistono
			if((semctl(semid, 0, SETVAL, arg))<0)
				perror("errore nel reimpostare i semafori");
		}
	} 
		else
		{
			status = semctl(semid, 0, SETVAL, arg);
			if (status<0)
				perror("semctl semaforo: ");
		}
	if (semid <0 || status <0) 
	{
		printf("initSem fallita");
		exit(1);
	}
	return(semid);
}
// settaggio initMemoria

int initMemoria(key_t key)
{
		int idmem = shmget(key,10*sizeof(int),IPC_CREAT | IPC_EXCL | 0666);
		if(idmem < 0)
		{
			if(errno==EEXIST)
			{ //se esiste 
				idmem = shmget(key,0,0); 
				if (idmem<0)
				perror("err mem condivisa");
			}
		 	else 
			{
				printf("err init memoria");
				exit(1);
			}
		}
	return idmem;
}
