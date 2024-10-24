#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

unsigned long cptQ1 = 0;
unsigned long cptQ2 = 0;
unsigned long cptOpti = 0;
unsigned long cptOptiMegaTurbo = 0;
pthread_t thread1, thread2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* compteurQ1() {
    int tmp;
    int i;
    for (i = 0; i < 10000000; i++) {
        tmp = cptQ1;
        tmp++;
        cptQ1 = tmp;
    }
    printf("cptQ1 = %lu\n", cptQ1);
    return NULL;
}


void* compteurQ2() {
    int tmp;
    int i;
    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        tmp = cptQ2;
        tmp++;
        cptQ2 = tmp;
        pthread_mutex_unlock(&mutex);
    }
    printf("cptQ2 = %lu\n", cptQ2);
    return NULL;
}

void* compteurOpti() {
    int tmp;
    int i = 0;
    while (i < 10000000) {
        pthread_mutex_lock(&mutex);
        tmp = cptOpti;
        tmp++;
        cptOpti = tmp;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    printf("cptQ2 = %lu\n", cptOpti);
    return NULL;
}

void* compteurOptiMegaTurbo() {
    unsigned long tmp = 0;
    int i = 0;
    while (i < 10000000) {
        tmp++;
        i++;
    }
    pthread_mutex_lock(&mutex);
    cptOptiMegaTurbo += tmp;
    pthread_mutex_unlock(&mutex);
    printf("cptOpti = %lu\n", cptOptiMegaTurbo);
    return NULL;
}

int main() {
    struct timespec start, end;
    double elapsed;

    // Question 1
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&thread1, NULL, compteurQ1, NULL);
    pthread_create(&thread2, NULL, compteurQ1, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Valeur finale du compteur Q1 = %lu\n", cptQ1);
    printf("Temps écoulé pour Q1: %.9f secondes\n", elapsed);

    // Question 2
    cptQ2 = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&thread1, NULL, compteurQ2, NULL);
    pthread_create(&thread2, NULL, compteurQ2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Valeur finale du compteur Q2 = %lu\n", cptQ2);
    printf("Temps écoulé pour Q2: %.9f secondes\n", elapsed);

    // Optimisation

    cptOpti = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&thread1, NULL, compteurOpti, NULL);
    pthread_create(&thread2, NULL, compteurOpti, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Valeur finale du compteur optimisé = %lu\n", cptOpti);
    printf("Temps écoulé pour l'optimisation: %.9f secondes\n", elapsed);


    // Optimisation Mega Turbo (tkt)

    cptOptiMegaTurbo = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&thread1, NULL, compteurOptiMegaTurbo, NULL);
    pthread_create(&thread2, NULL, compteurOptiMegaTurbo, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Valeur finale du compteur optimisé Mega Turbo = %lu\n", cptOptiMegaTurbo);
    printf("Temps écoulé pour l'optimisation Mega Turbo: %.9f secondes\n", elapsed);
    return 0;
}
