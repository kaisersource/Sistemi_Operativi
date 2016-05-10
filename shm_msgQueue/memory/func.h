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


#define semc1 0601
#define semc2 0602
#define semc3 0603
#define SEM_R 0604
#define shared_mem 0605

#define semc1fine 0606
#define semc2fine 0607
#define semc3fine 0610

#define SUM 0
#define MOLT 1
#define POW 2
#define SEMXXX 0600
#define N 3





typedef union _semun
	{
	int val;
	struct semid_ds *buf;
	ushort *array;
	}semun;

void dealloca();

int waitSem(int semid);
int signalSem(int semid);
int initsem(key_t semkey, int init);
int initMemoria(key_t key);

