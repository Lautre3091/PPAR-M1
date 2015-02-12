
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

static const int min_eat_ms[NUM_PHILOSOPHERS]   = {300, 300, 300, 300, 300};
static const int max_eat_ms[NUM_PHILOSOPHERS]   = {600, 600, 600, 600, 600};
static const int min_think_ms[NUM_PHILOSOPHERS] = {300, 300, 300, 300, 300};
static const int max_think_ms[NUM_PHILOSOPHERS] = {600, 600, 600, 600, 600};

/* Functions. */
static void philosopher_cycle(int NumThread, pthread_mutex_t *FourchetteGauche, pthread_mutex_t *FourchetteDroite, unsigned int *graine);
static void sleep_rand_r(int min_ms, int max_ms, unsigned int *graine);

int main(int argc, char **argv)
{
    pthread_mutex_t fourchette[NUM_PHILOSOPHERS];
    time_t t = time(NULL);
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) pthread_mutex_init(&fourchette[i], NULL);

#pragma omp parallel num_threads(NUM_PHILOSOPHERS)
    {
        int NumThread = omp_get_thread_num();
        pthread_mutex_t *FourchetteGauche = &fourchette[NumThread];
        pthread_mutex_t *FourchetteDroite = &fourchette[(NumThread + 1) % 5];

        unsigned int graine =(unsigned int) t + NumThread;
        philosopher_cycle(NumThread, FourchetteGauche, FourchetteDroite, &graine);
    }
    return  0;
}

static void philosopher_cycle(int NumThread, pthread_mutex_t *FourchetteGauche,
        pthread_mutex_t *FourchetteDroite, unsigned int *graine)
{
    printf("Le philosophe %d veux manger!\n", NumThread);

    if (NumThread == NUM_PHILOSOPHERS - 1) {
        pthread_mutex_lock(FourchetteDroite);
        printf("Le philosophe %d a pris la fourchette de droite.\n", NumThread);
        usleep((useconds_t) 5000);
        pthread_mutex_lock(FourchetteGauche);
        printf("Le philosophe %d a pris la fourchette de gauche et commence à manger.\n", NumThread);
    }
    else {
        pthread_mutex_lock(FourchetteGauche);
        printf("Le philosophe %d a pris la fourchette de gauche.\n", NumThread);
        usleep((useconds_t) 5000);
        pthread_mutex_lock(FourchetteDroite);
        printf("Le philosophe %d a pris la fourchette de gauche et à commencer à mangr.\n", NumThread);
    }

    sleep_rand_r(min_eat_ms[NumThread], max_eat_ms[NumThread], graine);

    pthread_mutex_unlock(FourchetteGauche);
    pthread_mutex_unlock(FourchetteDroite);
    printf("Le philosophe %d a fini de manger à pose sa fourchette.\n", NumThread);

    sleep_rand_r(min_think_ms[NumThread], max_think_ms[NumThread], graine);
}

static void sleep_rand_r(int min_ms, int max_ms, unsigned int *graine){
    int range = max_ms - min_ms + 1;
    int ms = rand_r(graine) % range + min_ms;
    usleep((useconds_t) ms*1000);
}