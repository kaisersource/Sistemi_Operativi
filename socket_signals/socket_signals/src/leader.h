#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <signal.h>


#define MY_SOCK_PATH "socket"
#define NO_CLIENTS 3
#define SOMMA 0
#define MOLT 1
#define POT 2
#define N 3

 struct sockaddr_un serverFd,sockC1,sockC2,sockC3;
int V[N],ris,r,l,s;
int clientC1,clientC2,clientC3,sockFd;




