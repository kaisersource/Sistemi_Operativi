#include "leader.h"

int main()
{
	
   signal(SIGINT, SIG_IGN);

    //socket endpoint
    if ((clientC2 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("\n Error : Could not create socket \n");
        _exit(EXIT_FAILURE);
    }
    printf("[C2] endpoint creato\n");

    sleep(1);
    //creazione socket af_unix
    
    serverFd.sun_family = AF_UNIX;
    strcpy(serverFd.sun_path, MY_SOCK_PATH);

    //connessione al socket
    if(( connect( clientC2, (struct sockaddr *) &serverFd, sizeof(serverFd))) == -1)
    {
        perror("[CLIENT C2] Errore connessione al server.");
        _exit(EXIT_FAILURE);
    }
    sleep(2);
    printf("c2 in connessione\n");

    //ricezione dei parametri generati casualmente: x,y e l'operazione
   while(1)
       {


    if((r=recv(clientC2, &V, 3*sizeof(int),0)) == -1)
    {
        perror("[CLIENT C2]errore nel ricevere i parametri dal server ");
        _exit(EXIT_FAILURE);
    }

    //esecuzione somma
    	if(V[2] == 1)
    	{
    	    ris=V[0] * V[1];
    	    if((s=send(clientC2, &ris, sizeof(int),0)) == -1)
    	    {
    	        perror("errore nel ricevere i parametri dal server ");
    	        _exit(EXIT_FAILURE);

    	    }
    	}
     }
    if((close(clientC2)) == -1)
    {
        perror("Impossibile chiudere il socket di C2.");
        _exit(EXIT_FAILURE);
    }
    _exit(EXIT_SUCCESS);
}
