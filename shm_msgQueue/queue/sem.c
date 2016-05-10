#include "func.h"
int initsem(key_t semkey, int init);
int initMemoria(key_t key);
int main(){	
	if (initsem(SEMC1,0)<0){
		printf("Errore creazione semaforo SEMC1 \n");
		exit(-1);
	}
	if (initsem(SEMC2,0)<0){
		printf("Errore creazione semaforo SEMC2 \n");
		exit(-1);
	}
	if (initsem(SEMC3,0)<0){
		printf("Errore creazione semaforo SEMC3 \n");
		exit(-1);
	}
	if (initsem(SEMC1FINE,0)<0){
		printf("Errore Creazione semaforo SEMC1FINE \n");
		exit(-1);
	}
	if (initsem(SEMC2FINE,0)<0){
		printf("Errore Creazione semaforo SEMC2FINE \n");
		exit(-1);
	}
	if (initsem(SEMC3FINE,0)<0){
		printf("Errore Creazione semaforo SEMC3FINE \n");
		exit(-1);
	}
	if (initsem(SEMC1READ,0)<0){
		printf("Error creazione semaforo SEMC1READ \n");
		exit(-1);
	}
	if (initsem(SEMC2READ,0)<0){
		printf("Error creazione semaforo SEMC2READ \n");
		exit(-1);
	}
	if (initsem(SEMC3READ,0)<0){
		printf("Error creazione semaforo SEMC3READ \n");
		exit(-1);
	}
	if (initsem(SEMC1CALC,0)<0){
		printf("Creazione semaforo SEM_CALC_C1: Fallita\n");
		exit(-1);
	}
	if (initsem(SEMC2CALC,0)<0){
		printf("Creazione semaforo SEM_CALC_C2: Fallita\n");
		exit(-1);
	}
	if (initsem(SEMC3CALC,0)<0){
		printf("Creazione semaforo SEMC3CALC \n");
		exit(-1);
	}
	if (initsem(SEM_R,0)<0){
		printf("Creazione semaforo SEM_R \n");
		exit(-1);
	}
	if(cr_queue(QUEUE)<0){
		printf("Errore creazione coda di messaggi");
		exit(-1);
	}
	exit(0);
}

int initsem(key_t semkey, int init) {
	int status = 0, semid;
	semun arg;
	arg.val = init;
	semid = semget(semkey, 1, SEMXXX | IPC_CREAT | IPC_EXCL);
	if (semid<0) {
		if (errno == EEXIST) { 
			semid = semget(semkey, 1, 0);
			if (semid<0)
				perror("Errore semget semaforo ");
			if((semctl(semid, 0, SETVAL, arg))<0)
				perror("Errore di reset ");
		}
	} else {
		status = semctl(semid, 0, SETVAL, arg);
		if (status<0)
			perror("Errore controllo semafori");
		}
	if (semid <0 || status <0) {
		printf("Inizializzazione fallita");
		return(-1);
	}
	return(semid);
}