#include "func.h"

int waitSem(int semid) 
{
	struct sembuf wait_buf;
	wait_buf.sem_num = 0;
	wait_buf.sem_op = -1;
	wait_buf.sem_flg = 0;
	if((semop(semid, &wait_buf, 1)) <0) {
		perror("sem fallita");
		return(-1);
	}
	return(0);
}

int signalSem(int semid)
{
	struct sembuf signal_buf;
	signal_buf.sem_num = 0;
	signal_buf.sem_op = 1;
	signal_buf.sem_flg = 0;
	if(semop(semid, &signal_buf, 1) <0) 
{
		perror("Errore signal");
		return(-1);
}
	return(0);
}

void dealloca()
{
	//acquisisco l'id dei semafori e li elimino
	printf("\neliminazione semafori...\n");
	int semc1start = semget(semc1, 1, 0);
	if (semc1start<0)
		perror("err getting semc1start: ");
	if ((semctl(semc1start,0,IPC_RMID,0))<0)
		perror("err removing semc1start: ");

	int semc2start = semget(semc2, 1, 0);
	if (semc2start<0)
		perror("err getting semc2start: ");
	if ((semctl(semc2start,0,IPC_RMID,0))<0)
		perror("err removingsemc2start: ");

	int semc3start = semget(semc3, 1, 0);
	if (semc3start<0)
		perror("err getting semc3start: ");
	if ((semctl(semc3start,0,IPC_RMID,0))<0)
		perror("err semc3start: ");

	int semc1done = semget(semc1fine, 1, 0);
	if (semc1done<0)
		perror("err gettingsemc1done: ");
	if ((semctl(semc1done,0,IPC_RMID,0))<0)
		perror("err removing semc1done: ");

	int semc2done = semget(semc2fine, 1, 0);
	if (semc2done<0)
		perror("err getting semc2done: ");
	if ((semctl(semc2done,0,IPC_RMID,0))<0)
		perror("err removing semc2done: ");

	int semc3done = semget(semc3fine, 1, 0);
	if (semc3done<0)
		perror("err getting semc3done: ");
	if ((semctl(semc3done,0,IPC_RMID,0))<0)
		perror("err removing semc3done: ");


	int semR = semget(SEM_R, 1, 0);
	if (semR<0)
		perror("err acquisizione semR ");
	if ((semctl(semR,0,IPC_RMID,0))<0)
		perror("errore rimozione semR: ");

	printf("...rimossi\n");


	//acquisisco l'id della memoria condivisa e la elimino
	printf("eliminazione memoria condivisa...\n");
	int memoria = shmget(shared_mem,1,0);
	if (memoria<0)
		perror("errore aquisizione memoria condivisa: ");
	if((shmctl(memoria,IPC_RMID,0))<0)
		perror("errore eliminazione memoria: ");
	printf("...rimossa\n");
}


