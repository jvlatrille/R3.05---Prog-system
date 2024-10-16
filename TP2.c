#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* boucle_infinie(void* arg) {
    while (1) {
        printf(".\n");
        sleep(1); // Attend 1 seconde
    }
    return NULL;
}

void* attendre_entree(void* arg) {
    printf("Tapez un caractère : ");
    getchar(); // Attend une entrée clavier

    return NULL;
}

int main(){
    // Question 1
    // ça fonctionne pas car le programme s'arrête avant que le thread 1 finisse
    pthread_t thread1, thread2;
    pthread_attr_t attr;

    // Initialiser les attributs du thread
    pthread_attr_init(&attr);
    
    //Question 4
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // ça ne fonctionne pas car le thread 1 est détaché et ne peut pas être joint
    
    // Crée le premier thread
    pthread_create(&thread1, &attr, boucle_infinie, NULL);
    // Crée le deuxième thread
    pthread_create(&thread2, &attr, attendre_entree, NULL);

    printf("Les 2 threads sont lancés\n");
    pthread_attr_destroy(&attr); 

    // Question 2
    pthread_join(thread2, NULL);

    // Question 3
    // Il s'arrête plus
    
    return 0;
}