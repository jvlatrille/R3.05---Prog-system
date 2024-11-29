#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Variables globales
int participants_arrives = 0;  // Compteur des participants arrivés
int total_participants;       // Nombre total de participants
sem_t mutex;                  // Sémaphore pour protéger la section critique
sem_t rendezvous;             // Sémaphore pour synchroniser les threads

// Fonction exécutée par chaque thread
void* participant(void* arg) {
    int id = *(int*)arg; // Récupération de l'ID du participant
    free(arg); // Libération de la mémoire

    printf("Participant %d arrive.\n", id);
    sleep(rand() % 3 + 1); // Simulation d'un temps aléatoire avant d'arriver

    // Section critique protégée par le sémaphore
    sem_wait(&mutex);
    participants_arrives++;
    if (participants_arrives == total_participants) {
        printf("Participant %d est le dernier, le rendez-vous peut commencer !\n", id);
        for (int i = 0; i < total_participants; i++) {
            sem_post(&rendezvous); // Débloquer tous les threads
        }
    }
    sem_post(&mutex); // Libération de la section critique

    // Attente que le rendez-vous commence
    sem_wait(&rendezvous);
    printf("Participant %d commence le travail.\n", id);
    return NULL;
}

int main() {
    printf("Entrez le nombre de participants : ");
    scanf("%d", &total_participants);

    pthread_t threads[total_participants]; // Tableau pour stocker les threads
    sem_init(&mutex, 0, 1);                // Initialisation du sémaphore mutex (valeur initiale : 1)
    sem_init(&rendezvous, 0, 0);           // Initialisation du sémaphore rendezvous (valeur initiale : 0)

    // Création des threads
    for (int i = 0; i < total_participants; i++) {
        int* id = malloc(sizeof(int)); // Allocation dynamique pour éviter les conflits
        *id = i + 1;
        if (pthread_create(&threads[i], NULL, participant, id) != 0) {
            perror("Erreur lors de la création du thread");
            exit(EXIT_FAILURE);
        }
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < total_participants; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruction des sémaphores
    sem_destroy(&mutex);
    sem_destroy(&rendezvous);

    printf("Tous les participants ont terminé. Rendez-vous terminé.\n");
    return 0;
}
