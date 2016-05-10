 
#include "leader.h"
   
//unlink
void cleanup()
{   
if((unlink(MY_SOCK_PATH)) == -1) 
    {
        perror("errore durante unlink del socket");
        _exit(EXIT_FAILURE);
    }
exit(-1);
}

int main()
{
	
    struct sockaddr_un serverFd,sockC1,sockC2,sockC3;

    serverFd.sun_family = AF_UNIX;
    strcpy(serverFd.sun_path, MY_SOCK_PATH);

//gestione del ctrl-c
if (signal(SIGINT, cleanup) == SIG_ERR)
	{
	perror("Cannot set up signal\n");
	_exit(EXIT_FAILURE);
	}

    //creazione socket
    sleep(1);
    sockFd = socket (AF_UNIX, SOCK_STREAM, 0);
    if(sockFd == -1)
    {
        perror("error creating socket");
        _exit(EXIT_FAILURE);
    }

    printf("sock created\n");
    sleep(1);

    //associo al socket un indirizzo
    if( (bind (sockFd, (struct sockaddr *)&serverFd, sizeof(serverFd))) == -1)
    {
        perror("error binding socket");
        exit(-1);

    }
    printf("Bind completed succesfully\n");
    sleep(1);

    //leader in ascolto
    if ( (listen (sockFd, NO_CLIENTS)) == -1)
    {
        perror("listen");
        exit(-1);
    }
    printf("leader in ascolto\n");
    sleep(1);

    //creazione processo c1
    pid_t c1=fork();
    if(c1 == -1)
    {
        perror("fork fallita");
        exit(1);
    }
    else if (c1==0)
    {
        if(execl("exe/c1", "c1" ,NULL,(char *) 0)<0)
            perror("exec c1 fallita ");
        exit(-1);
    }
    printf("fork C1 eseguita\n");
    sleep(1);


//creazione processo c2
    pid_t c2=fork();
    if(c2 == -1)
    {
        perror("fork fallita");
        exit(1);
    }
    else if (c2==0)
    {
        if(execl("exe/c2", "c2" ,NULL,(char *) 0)<0)
            perror("exec c2 fallita ");
        exit(-1);
    }
    printf("fork C2 eseguita\n");
    sleep(1);

//creazione processo c3
    pid_t c3=fork();
    if(c3 == -1)
    {
        perror("fork fallita");
        exit(1);
    }
    else if (c3==0)
    {
        if(execl("exe/c3", "c3" ,NULL,(char *) 0)<0)
            perror("exec c3 fallita ");
        exit(-1);
    }
    printf("fork C3 eseguita\n");
    sleep(1);



    //test per l'accettazione della connessione del client
    struct sockaddr_un sockpeer;
    socklen_t peerlen=sizeof(sockC1);
    

    if((clientC1 = accept(sockFd, (struct sockaddr *) &sockC1, &peerlen)) == -1)
    {
        perror("errore d'accettazione\n");
        exit(-1);
    }

    sleep(1);

    if((clientC2 = accept(sockFd, (struct sockaddr *) &sockC2, &peerlen)) == -1)
    {
        perror("errore d'accettazione\n");
        exit(-1);
    }

    sleep(1);

    if((clientC3 = accept(sockFd, (struct sockaddr *) &sockC3, &peerlen)) == -1)
    {
        perror("errore d'accettazione\n");
        exit(-1);
    }
    srand(time(NULL));


while(1)
{
//generami i numeri e operazione
    V[0]=(int)rand()%10;
    V[1]=(int)rand()%10;
    V[2]=(int)rand()%3;//(int)rand()%3;
    printf("||||||||||||||||||||||||||||||||||| \n");
    printf("||x = %d                         ||| \n", V[0]);
    printf("||y = %d                         ||| \n", V[1]);

//passaggio parametri a c1
    if(( s = send(clientC1, &V, 3*sizeof(int),0)) == -1)
    {
        perror("errore durante la send");
        exit(-1);
    }
    sleep(1);

//passaggio parametri a c2
    if(( s = send(clientC2, &V, 3*sizeof(int),0)) == -1)
    {
        perror("errore durante la send");
        exit(-1);
    }
    sleep(1);
//passaggio parametri a c3
    if(( s = send(clientC3, &V, 3*sizeof(int),0)) == -1)
    {
        perror("errore durante la send");
        exit(-1);
    }
    sleep(1);


//Filtro della risultato in base all'operazione
    switch(V[2])
    {
    case SOMMA:
    if((r = recv(clientC1, &ris, sizeof(int),0)) == -1)
        {
            perror("errore durante la recv");
            exit(-1);
        }
        printf("  Somma - Risultato : %d           \n", ris);
	printf("|||||||||||||||||||||||||||||||||||\n");
	printf("\n");
    break;

    case MOLT:
    if((r = recv(clientC2, &ris, sizeof(int),0)) == -1)
        {
            perror("errore durante la recv");
            exit(-1);
        }
        printf("  Molt - Risultato : %d            \n",ris);
	printf("|||||||||||||||||||||||||||||||||||\n");
	printf("\n");
    break;

    case POT:
    if((r = recv(clientC3, &ris, sizeof(int),0)) == -1)
        {
            perror("errore durante la recv");
            exit(-1);
        }
        printf("  Potenza - Risultato : %d         \n",ris);
	printf("|||||||||||||||||||||||||||||||||||\n");
	printf("\n");
    break;
    }
    
}
 if((close(clientC1)) == -1)
    {
        perror("errore durante la chiusura del socket C1");
        _exit(EXIT_FAILURE);
    }

    if((close(clientC2)) == -1)
    {
        perror("errore durante la chiusura del socket C2");
        _exit(EXIT_FAILURE);
    }

    if((close(clientC3)) == -1)
    {
        perror("errore durante la chiusura del socket C3");
        _exit(EXIT_FAILURE);
    }
    if((close(sockFd)) == -1) //chiusura del server
    {
        perror("errore durante la chiusura del socket leader");
        _exit(EXIT_FAILURE);
    }
      
    exit(0);

}



