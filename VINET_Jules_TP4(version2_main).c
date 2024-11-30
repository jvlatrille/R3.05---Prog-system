/************************************************
 * Fichier : projet.c (anciennement main.c)
 * Auteur  : VINET LATRILLE Jules
 * Classe  : TD2 / TP4
 * Date    : 30 / 11 / 2024
 * Version : 2.0
 ************************************************/


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

int X = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int nbParticipantsActuels = 0;


void* fonction(void* arg) {
    int id = *(int*)arg; // Identifiant du thread
    free(arg); // Libère la mémoire pour l'id # XD

    printf("Lance\n");
    sleep(rand() % 3 + 1); // Temps aléatoire avant d'arriver

    // On ajoute dans la zone critique
    pthread_mutex_lock(&mutex);
    nbParticipantsActuels++;
    pthread_mutex_unlock(&mutex);

    // Réaliser la tâche SSI tout les processus sont lancés
    while (1) {
        pthread_mutex_lock(&mutex);
        if (nbParticipantsActuels == X) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
        usleep(500000); // Pause pour éviter une boucle trop rapide et que ça consomme trop de ressources
    }

    printf("Début du travail\n");
    sleep(3); // Temps de travail de 3s
    printf("Travail terminé.\n");

    return NULL; // On return parce que c'est une fonction et sinon il est pas content
}

// Fonction principale
int main(void) {
    printf("Nombre de personnes participant :");
    scanf("%d", &X);

    pthread_t threads[X]; // Tableau pour stocker les threads

    // Création des threads
    for (int i = 0; i < X; i++) {
        int* id = malloc(sizeof(int)); // Alloue de la mémoire pour l'id du thread
        *id = i + 1;

        if (pthread_create(&threads[i], NULL, fonction, id) != 0) {
            perror("Erreur lors de la création du thread");
            exit(EXIT_FAILURE);
        }
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < X; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nDestruction dans bientôt...\n");
    // sleep(rand() % 6 + 5);  // Temps aléatoire entre 5 et 10 secondes
    sleep(rand() % 3 + 1); // Temps aléatoire mais pas entre 5 et 10 secondes parce que c'est trop long
    pthread_mutex_destroy(&mutex);
    printf("Fin du programme.\n\n");

    return 0;
}
