#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>

//struttura del messaggio
typedef struct text {
	long mesgtype; //tipo di messaggio
	int x;     	//valore del primo numero generato
	int y;		//valore del secondo numero generato
	int op;		//numero dell'operazione da eseguire				
	int res;    //risultato dell'operazione eseguita
}text;

int write_message(int queue,text *a,int x,int y, int op ,int res){ //(coda,puntatore alla struttura del messaggio,valori da inviare)
	int msg; //messaggio di risposta
	a->mesgtype=1;
	a->x=x;
	a->y=y;
	a->op=op;
	a->res=res;
	if((msg = msgsnd(queue,a,sizeof(struct text)-sizeof(long),0))<0){ //invio un messaggio di dimensione uguale a tutta la 
		perror("msgsnd scrivi msg: ");										//struttura - long perché il tipo non fa parte del messaggio
		return(-1);
	}
	return(0);			
}

int recive_msg(int coda,text *a){ //(coda, puntatore alla struttura del messaggio)
	int mlen;
		if ( (mlen = msgrcv(coda, a,sizeof(struct text)-sizeof(long),0, MSG_NOERROR)<0)){
			perror("msgrcv ricevi messaggio: ");
			return(-1);
		}
	return(0);
}

int cr_queue( key_t key ){
	int queue_id;
	queue_id = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
	if (queue_id < 0){
		if (errno == EEXIST) {
			queue_id = msgget(key, 0);
			if(queue_id<0)
			perror("Errore creazione coda");
		}
		else{
			printf("Creazione coda messaggi fallita \n");
			return(-1);
		}
	} 
	return queue_id;
}

/* SEMAFORI */

union _semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array; 
}semun;

int waitSem(int semid) {
	struct sembuf wait_buf;
	wait_buf.sem_num = 0;
	wait_buf.sem_op = -1;
	wait_buf.sem_flg = 0;
	if((semop(semid, &wait_buf, 1)) <0) {
		perror("Errore nella wait");
		return(-1);
	}
	return(0);
}

int signalSem(int semid) {
	struct sembuf signal_buf;
	signal_buf.sem_num = 0;
	signal_buf.sem_op = 1;
	signal_buf.sem_flg = 0;
	if(semop(semid, &signal_buf, 1) <0) {
		perror("Errore nella signal");
		return(-1);
	}
	return(0);
}


