#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Déclaration des variables globales
int participants_arrives = 0;       // Compteur des participants arrivés
int total_participants;            // Nombre total de participants
pthread_mutex_t mutex;             // Mutex pour protéger les données partagées
pthread_cond_t condition;          // Condition pour synchroniser les threads

// Fonction exécutée par chaque thread
void* participant(void* arg) {
    int id = *(int*)arg; // Récupération de l'ID du participant
    free(arg); // Libération de la mémoire allouée pour l'ID

    printf("Participant %d arrive.\n", id);
    sleep(rand() % 3 + 1); // Simulation d'un temps aléatoire avant d'arriver

    // Section critique protégée par le mutex
    pthread_mutex_lock(&mutex);
    participants_arrives++;

    if (participants_arrives == total_participants) {
        printf("Participant %d est le dernier, le rendez-vous peut commencer !\n", id);
        pthread_cond_broadcast(&condition); // Réveiller tous les threads
    } else {
        // Attente que tous les participants soient arrivés
        while (participants_arrives < total_participants) {
            pthread_cond_wait(&condition, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex); // Sortie de la section critique

    // Travail après le rendez-vous
    printf("Participant %d commence le travail.\n", id);
    return NULL;
}

int main() {
    printf("Entrez le nombre de participants : ");
    scanf("%d", &total_participants);

    pthread_t threads[total_participants]; // Tableau pour stocker les threads
    pthread_mutex_init(&mutex, NULL);     // Initialisation du mutex
    pthread_cond_init(&condition, NULL);  // Initialisation de la condition

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

    // Destruction des ressources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    printf("Tous les participants ont terminé. Rendez-vous terminé.\n");
    return 0;
}
