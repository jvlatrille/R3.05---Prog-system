#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
// Question 1 : 
// Non, à cause de l'accès concurrent non synchronisé à la variable
// Les threads interfèrent entre eux lors de l'incrémentation de cpt, ce qui entraîne des pertes d'incréments.
unsigned long cpt = 0;
pthread_t thread1, thread2;

void* compteur(){
    int tmp;
    int i;
    for (i = 0; i < 10000000; i++) {
        tmp = cpt;
        tmp++;
        cpt = tmp;
    }
    printf("cpt = %lu\n", cpt);
}

int main() {

    pthread_create(&thread1, NULL, compteur, NULL);
    pthread_create(&thread2, NULL, compteur, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("valeur finale du compteur = %lu\n", cpt);

    return 0;
}
*/



/*
// Question 2 : 
// Ui, ça donne 20 millions

unsigned long cpt = 0;
pthread_t thread1, thread2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* compteur(){
    int tmp;
    int i;
    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        tmp = cpt;
        tmp++;
        cpt = tmp;
        pthread_mutex_unlock(&mutex);
    }
    printf("cpt = %lu\n", cpt);
}

int main() {

    pthread_create(&thread1, NULL, compteur, NULL);
    pthread_create(&thread2, NULL, compteur, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("valeur finale du compteur = %lu\n", cpt);

    return 0;
}
*/

/**/
// Question 3 :

unsigned long cpt = 0;
pthread_t thread1, thread2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* compteur(){
    int tmp;
    int i;
    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        tmp = cpt;
        tmp++;
        cpt = tmp;
        pthread_mutex_unlock(&mutex);
    }
    printf("cpt = %lu\n", cpt);
}

int main() {

    pthread_create(&thread1, NULL, compteur, NULL);
    pthread_create(&thread2, NULL, compteur, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("valeur finale du compteur = %lu\n", cpt);

    return 0;
}