#include "leader.h"

int main()
{
    signal(SIGINT, SIG_IGN);

    //socket endpoint
    if ((clientC1 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("\n Error : Could not create socket \n");
        _exit(EXIT_FAILURE);
    }
    printf("[C1] endpoint creato\n");

    sleep(1);
    //creazione socket af_unix
   
    serverFd.sun_family = AF_UNIX;
    strcpy(serverFd.sun_path, MY_SOCK_PATH);

    //connessione al socket
    if(( connect( clientC1, (struct sockaddr *) &serverFd, sizeof(serverFd))) == -1)
    {
        perror("[CLIENT C1] Errore connessione al server.");
        _exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("c1 in connessione\n");

    //ricezione dei parametri generati casualmente: x,y e l'operazione
   while(1)
        {


    if((r=recv(clientC1, &V, 3*sizeof(int),0)) == -1)
    {
        perror("errore nel ricevere i parametri dal server ");
        _exit(EXIT_FAILURE);
    }
    //esecuzione somma
    if(V[2] == 0)
    {
        ris=V[0] + V[1];
        if((s=send(clientC1, &ris, sizeof(int),0)) == -1)
        {
            perror("errore nel ricevere i parametri dal server ");
            _exit(EXIT_FAILURE);

        }
    }
}
    if(close(clientC1) == -1)
    {
        perror("Impossibile chiudere il socket di C1.");
        _exit(EXIT_FAILURE);
    }
    _exit(EXIT_SUCCESS);
}

