#include "func.h"

void freeMemory();

int main() {
    int *SemReturn = NULL;
    pid_t sem; //dichiaro una variabile sem di tipo pid_t
    sem = fork(); //creo un processo figlio con la system call fork()
    if (sem < 0) { //quando la fork è minore di zero vuol dire che non è avvenuta
        perror("Errore nella fork ");
        exit(-1);
    }
    if (sem == 0) //quando è 0 vuol dire che è il figlio
    {
        if (execl("sem", "sem", NULL, (char *) 0) < 0) {//passo al processo figlio le istruzioni di sem
            perror("Errore excl"); //la excl non può essere negativa
            exit(-1);
        }
    }
    wait(SemReturn); //wait per la terminazione del processo figlio che eseguiva sem
    if (SemReturn < 0) { //non può tornare negatico
        printf("Errore sem");
        freeMemory(); //libero la memoria
        exit(-1);
    }




    pid_t leader; //le stesse istruzioni vengono fatte eseguire al processo leader
    leader = fork();
    if (leader < 0) {
        perror("Errore nella fork");
        freeMemory();
        exit(-1);
    }
    if (leader == 0) {
        if (execl("leader", "leader", NULL, (char *) 0) < 0)
            perror("Errore excl");
        freeMemory();
        exit(-1);
    }

    pid_t c1;
    c1 = fork();
    if (c1 < 0) {
        perror("Errore nella fork");
        freeMemory();
        exit(-1);
    }
    if (c1 == 0) {
        if (execl("c1", "c1", NULL, (char *) 0) < 0)
            perror("Errore excl");
        freeMemory();
        exit(-1);
    }


    pid_t c2;
    c2 = fork();
    if (c2 < 0) {
        perror("Errore nella fork");
        freeMemory();
        exit(-1);
    }
    if (c2 == 0) {
        if (execl("c2", "c2", NULL, (char *) 0) < 0)
            perror("Errore excl");
        freeMemory();
        exit(-1);
    }



    pid_t c3;
    c3 = fork();
    if (c3 < 0) {
        perror("Errore nella fork");
        freeMemory();
        exit(-1);
    }
    if (c3 == 0) {
        if (execl("c3", "c3", NULL, (char *) 0) < 0)
            perror("errore excl");
        freeMemory();
        exit(-1);
    }

    int *return_value = NULL;
    int error = 0;
    int i;
    for (i = 0; i < 4; i++) { //ciclo for per fare la wai sui processi c1 c2 c3
        wait(return_value);
        if (return_value < 0) {
            error = 1;
            printf("Errore di esecuzione di uno dei processi");
        }
    }

    freeMemory();
    if (error)
        exit(-1);
    else
        exit(0);
}

void freeMemory() {

    int semc1start = semget(SEMC1, 1, 0);
    if (semc1start < 0)
        perror("Errore nell'acquisizione di c1");

    if ((semctl(semc1start, 0, IPC_RMID, 0)) < 0)
        perror("errore rimozione di c1");

    int semc2start = semget(SEMC2, 1, 0);
    if (semc2start < 0)
        perror("errore acquisizione c2");
    if ((semctl(semc2start, 0, IPC_RMID, 0)) < 0)
        perror("errore rimozione c2");

    int semc3start = semget(SEMC3, 1, 0);
    if (semc3start < 0)
        perror("errore acquisizione c3");
    if ((semctl(semc3start, 0, IPC_RMID, 0)) < 0)
        perror("errore rimozione c3");
    //--------------------------------------------------------------
    int semc1done = semget(SEMC1FINE, 1, 0);
    if (semc1done < 0)
        perror("Errore acquisizione c1");
    if ((semctl(semc1done, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione c1");

    int semc2done = semget(SEMC2FINE, 1, 0);
    if (semc2done < 0)
        perror("Errore acquisizione c2");
    if ((semctl(semc2done, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione c2");

    int semc3done = semget(SEMC3FINE, 1, 0);
    if (semc3done < 0)
        perror("Errore acquisizione c3");
    if ((semctl(semc3done, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione c3");

    int semc1read = semget(SEMC1READ, 1, 0);
    if (semc1read < 0)
        perror("Errore acquisizione semc1read");
    if ((semctl(semc1read, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semc1read");

    int semc2read = semget(SEMC2READ, 1, 0);
    if (semc2read < 0)
        perror("Errore acquisizione semc2read");
    if ((semctl(semc2read, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semc2read");

    int semc3read = semget(SEMC3READ, 1, 0);
    if (semc3read < 0)
        perror("Errore acquisizione c3");
    if ((semctl(semc3read, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione c3");

    
    int semc1calc = semget(SEMC1CALC, 1, 0);
    if (semc1calc < 0)
        perror("Errore acquisizione semc1calc");
    if ((semctl(semc1calc, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semc1calc");

    int semc2calc = semget(SEMC2CALC, 1, 0);
    if (semc2calc < 0)
        perror("Errore acquisizione semc2calc");
    if ((semctl(semc2calc, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semc2calc ");

    int semc3calc = semget(SEMC3CALC, 1, 0);
    if (semc3calc < 0)
        perror("Errore acquisizione semc3calc");
    if ((semctl(semc3calc, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semc3calc");

    int semR = semget(SEM_R, 1, 0);
    if (semR < 0)
        perror("Errore acquisizione semR");
    if ((semctl(semR, 0, IPC_RMID, 0)) < 0)
        perror("Errore rimozione semR");

    
   
    int queue = msgget(QUEUE, 0);
    if (queue < 0)
        perror("Errore acquisizione coda");
    if ((msgctl(queue, IPC_RMID, 0)) < 0)
        perror("Errore rimozione coda");
}