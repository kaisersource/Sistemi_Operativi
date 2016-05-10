#include "leader.h"

int main()
{
   signal(SIGINT, SIG_IGN);

    //socket endpoint
    int i;
    if ((clientC3 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("\n Error : Could not create socket \n");
        _exit(EXIT_FAILURE);
    }
    printf("[C3] endpoint creato\n");
    sleep(1);

    //creazione socket af_unix
    struct sockaddr_un serverFd;
    serverFd.sun_family = AF_UNIX;
    strcpy(serverFd.sun_path, MY_SOCK_PATH);

    //connessione al socket
    if(( connect( clientC3, (struct sockaddr *) &serverFd, sizeof(serverFd))) == -1)
    {
        perror("[CLIENT C3] Errore connessione al server.");
        _exit(EXIT_FAILURE);
    }
    printf("c3 in connessione\n");
    sleep(2);


    //loop
    while(1)
    {
    //ricezione dei parametri generati casualmente: x,y e l'operazione
    if((r=recv(clientC3, &V, 3*sizeof(int),0)) == -1)
    {

        perror("errore nel ricevere i parametri dal server ");
        _exit(EXIT_FAILURE);
    }
    //esecuzione potenza
	
    if(V[2] == 2)
    {
        ris=1;
        for(i=0; i < V[1]; i++){ris=V[0] * ris;}
            printf("pot");
        if((s = send(clientC3, &ris, sizeof(int),0)) == -1)
        {
            perror("errore nel ricevere i parametri dal server ");
            _exit(EXIT_FAILURE);

        }
    }
  }

    if(close(clientC3) == -1)
    {
        perror("Impossibile chiudere il socket di C3.");
        _exit(EXIT_FAILURE);

    }
    _exit(EXIT_SUCCESS);
}

