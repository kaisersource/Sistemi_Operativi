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
#include <limits.h>
#include <time.h>

#define SUM 0
#define MOL 1
#define POW 2
#define SEMXXX 0600
#define N 5

#define SEMC1 0601
#define SEMC2 0602
#define SEMC3 0603
#define SEM_R 0604

#define SEMC1FINE 0606
#define SEMC2FINE 0607
#define SEMC3FINE 0610

#define QUEUE 0611

#define SEMC1READ 0612
#define SEMC2READ 0613
#define SEMC3READ 0614

#define SEMC1CALC 0615
#define SEMC2CALC 0616
#define SEMC3CALC 0617
//~ SEMAFORI

typedef union _semun 
{
	int val;
	struct semid_ds *buf;
	ushort *array;
}semun;
	
typedef struct text 
{
	long mtype;
	int x;
	int y;
	int op;
	int res;
}text;

void write_message(int coda, text *a,int x,int y, int op ,int res);
void recive_msg(int coda, text *a);
int cr_queue(key_t key);
int waitSem(int semid);
int signalSem(int semid);
