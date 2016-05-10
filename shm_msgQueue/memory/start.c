#include "func.h"
int main()
{

	
	
	pid_t sem;
	sem=fork(); //creo sem
	if (sem<0)
	{
		perror("errore creazione semaforo");
		exit(1);
	}
	if (sem==0)
	{
		if (execl("sem", "sem", NULL, (char *) 0)<0)
		{
			perror("errore in esecuzione ");
			exit(-1);
		}
	}
	int *ritSem=NULL;	
	wait(ritSem);
	if(ritSem<0)
	{
		printf("Errore nell'esecuzione di sem");
		dealloca();
		exit(1);
	}

	pid_t leader; //creo leader
	leader=fork();
	if (leader<0)
	{
		perror("fork leader: ");
		dealloca();
		exit(-1);
	}
	if (leader==0)
	{
		if(execl( "leader", "leader" ,NULL,(char *) 0)<0)
			perror("exec leader: ");
			dealloca();
			exit(1);
	}
	//creazione c1
	pid_t c1;
	c1=fork();
	if (c1<0)
	{
		perror("errore nel creare c1\n");
		dealloca();
		exit(1);
	}
	if (c1==0)
	{
		if(execl( "c1", "c1" ,NULL,(char *) 0)<0)
			perror("errore esecuzione c1\n");
			dealloca();
			exit(1);
	}
	//creazione c2
	pid_t c2;
	c2=fork();
	if (c2<0){
		perror("errore nel creare C2\n");
		dealloca();
		exit(-1);
	}
	if (c2==0)
	{ 
		if(execl( "c2", "c2" ,NULL,(char *) 0)<0)
			perror("errore esecuzione c2\n");
			dealloca();
			exit(-1);
	}
	//creazione c3
	pid_t c3;
	c3=fork();
	if (c3<0)
	{
		perror("errore nel creare C3\n");
		dealloca();
		exit(-1);
	}
	if (c3==0)
	{
		if(execl( "c3", "c3" ,NULL,(char *) 0)<0)
			perror("errore esecuzione c3\n");
			dealloca();
			exit(1);
	}

	int *retval=NULL;
	int boolErrore=0;
	int i;
	for(i=0;i<4;i++)
	{
		wait(retval); //ritorno dell'esecuzione di c1,c2,c3
		if (retval<0)
		{
			boolErrore=1;
			printf ("err esecuzione c1,c2, o c3");
		}
	}
	dealloca();
	
 	if(boolErrore) //retval<0 setta boolErrore a 1, se true allora
		exit(1);		
	else
		exit(0);
}


