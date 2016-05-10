#include "func.h"

int main() {


    int semc1start = semget(SEMC1, 1, 0);
    if (semc1start < 0) {
        perror("Errore semaforo C1: ");
        exit(-1);
    }

    int semc1done = semget(SEMC1FINE, 1, 0);
    if (semc1done < 0) {
        perror("Errore creazione semaforo");
        exit(-1);
    }

    int semR = semget(SEM_R, 1, 0);
    if (semR < 0) {
        perror("Errore creazione semaforo SEM_R");
        exit(-1);

    }

    int semc1read = semget(SEMC1READ, 1, 0);
    if (semc1read < 0) {
        perror("Errore creazione semaforo");
        exit(-1);
    }
    int semc1calc = semget(SEMC1CALC, 1, 0);
    if (semc1calc < 0) {
        perror("Errore creazione semaforo C1");
        exit(-1);
    }

    int queue = cr_queue(QUEUE);
    if (queue < 0) {
        printf("Errore di acquisizione nella coda messaggi \n");
        exit(-1);
    }

    struct text *q = malloc(sizeof (struct text));

    int i = 0;
    for (i = 0; i < N; i++) {
        waitSem(semc1start);
        recive_msg(queue, q);
        
        signalSem(semc1read);
        waitSem(semc1calc);
        int sum = 0;
        if (SUM == q->op) { //faccio operazione
            sum = q->x + q->y;

            write_message(queue, q, 0, 0, -1, sum); //Invio nella coda

            signalSem(semR); //Ho inviato il messaggio e dico al leader di leggerlo

        }
        signalSem(semc1done);//Segnalo che il messaggio è stato inviato, e termino
    }
    free(q);
    exit(0);
}