#include "func.h"

int main() {

    int semc2start = semget(SEMC2, 1, 0);
    if (semc2start < 0) {
        perror("Errore semaforo C2");
        exit(-1);
    }

    int semc2done = semget(SEMC2FINE, 1, 0);
    if (semc2done < 0) {
        perror("Errore semaforo C2");
        exit(-1);
    }

    int semc2read = semget(SEMC2READ, 1, 0);
    if (semc2read < 0) {
        perror("Errore creazione semaforo ");
        exit(-1);
    }

    int semc2calc = semget(SEMC2CALC, 1, 0);
    if (semc2calc < 0) {
        perror("Errore creazione semaforo C2");
        exit(-1);
    }

    int semR = semget(SEM_R, 1, 0);
    if (semR < 0) {
        perror("Errore creazione semaforo SEM_R");
        exit(-1);
    }

    int queue = cr_queue(QUEUE);
    if (queue < 0) {
        printf("Errore di acquisizione nella coda messaggi \n");
        exit(-1);
    }

    struct text *q = malloc(sizeof (struct text));

    int moltiplicazione = 1;
    int i = 0;
    for (i = 0; i < N; i++) {
        waitSem(semc2start);
        recive_msg(queue, q);
        signalSem(semc2read);
        waitSem(semc2calc);
        if (MOL == q->op) {
            moltiplicazione = q->x * q->y;
            write_message(queue, q, 0, 0, -1, moltiplicazione);
            signalSem(semR); //invio al leader la notifica di fine operazione
        }
        signalSem(semc2done); //segnalo al leader la terminazione
    }
    free(q);
    exit(0);

}