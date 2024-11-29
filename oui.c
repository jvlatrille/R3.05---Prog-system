#include <stdio.h>              // (1) Bibliothèque standard pour les entrées/sorties (printf pour afficher, scanf pour lire).
#include <stdlib.h>             // (2) Bibliothèque pour la gestion de la mémoire dynamique (malloc, free).
#include <pthread.h>            // (3) Bibliothèque pour la gestion des threads et des mécanismes de synchronisation.
#include <unistd.h>             // (4) Bibliothèque pour des fonctions comme sleep (simuler une pause).

// Déclaration des variables globales
int participants = 0;           // (5) Initialise le compteur de participants déjà arrivés (commence à 0).
int totalParticipants;          // (6) Stocke le nombre total de participants (saisi par l'utilisateur plus tard).
pthread_mutex_t mutex;          // (7) Mutex pour gérer les accès concurrents aux données partagées (comme participants).
pthread_cond_t condition;       // (8) Condition utilisée pour bloquer ou réveiller les threads selon un état donné.

// Fonction exécutée par chaque thread (simulate un participant)
void* participant(void* arg) {
    int id = *(int*)arg;        // (9) Récupère l'ID unique du participant, passé lors de la création du thread.
    free(arg);                  // (10) Libère la mémoire allouée pour l'ID, car elle n'est plus utile.

    printf("Participant %d arrive.\n", id); // (11) Indique qu'un participant vient d'arriver.
    sleep(rand() % 3 + 1);      // (12) Simule une arrivée avec un délai aléatoire (entre 1 et 3 secondes).

    pthread_mutex_lock(&mutex); // (13) Verrouille le mutex pour accéder au compteur partagé `participants` en toute sécurité.
    participants++;             // (14) Incrémente le compteur pour indiquer qu'un participant de plus est arrivé.

    if (participants == totalParticipants) { // (15) Si tous les participants sont arrivés...
        printf("Participant %d est le dernier, le rendez-vous peut commencer !\n", id); // (16) Message spécial pour le dernier.
        pthread_cond_broadcast(&condition); // (17) Réveille tous les threads en attente, car la condition est remplie.
    } else {
        // (18) Si tous les participants ne sont pas encore là, le thread doit attendre.
        while (participants < totalParticipants) { // (19) Vérifie si la condition (tous présents) est atteinte.
            pthread_cond_wait(&condition, &mutex); // (20) Bloque ce thread jusqu'à ce qu'il soit réveillé par `broadcast`.
        }
    }
    pthread_mutex_unlock(&mutex); // (21) Déverrouille le mutex pour permettre aux autres threads de continuer.

    printf("Participant %d commence le travail.\n", id); // (22) Une fois réveillé, le participant commence sa tâche.
    return NULL;                // (23) Termine le thread une fois que le travail est fait.
}

int main() {
    printf("Entrez le nombre de participants : "); // (24) Demande à l'utilisateur combien de participants il veut simuler.
    scanf("%d", &totalParticipants); // (25) Lit le nombre total de participants et le stocke dans `totalParticipants`.

    pthread_t threads[totalParticipants]; // (26) Tableau pour stocker les identifiants des threads (un pour chaque participant).
    pthread_mutex_init(&mutex, NULL);     // (27) Initialise le mutex pour qu'il soit prêt à être utilisé.
    pthread_cond_init(&condition, NULL);  // (28) Initialise la condition pour synchroniser les threads.

    // Création des threads pour chaque participant
    for (int i = 0; i < totalParticipants; i++) { // (29) Boucle pour créer `totalParticipants` threads.
        int* id = malloc(sizeof(int));   // (30) Alloue dynamiquement un ID unique pour ce thread (nécessaire pour éviter les conflits).
        *id = i + 1;                     // (31) Définit l'ID du participant (1, 2, 3, ...).
        if (pthread_create(&threads[i], NULL, participant, id) != 0) { // (32) Crée un thread pour ce participant.
            perror("Erreur lors de la création du thread"); // (33) Si la création échoue, affiche un message d'erreur.
            exit(EXIT_FAILURE);        // (34) Quitte le programme immédiatement en cas d'échec critique.
        }
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < totalParticipants; i++) { // (35) Boucle pour attendre que chaque thread termine son exécution.
        pthread_join(threads[i], NULL);          // (36) Bloque le programme principal jusqu'à ce que le thread `i` termine.
    }

    // Nettoyage des ressources
    pthread_mutex_destroy(&mutex);        // (37) Détruit le mutex pour libérer les ressources système associées.
    pthread_cond_destroy(&condition);    // (38) Détruit la variable de condition pour éviter les fuites de mémoire.

    printf("Tous les participants ont terminé. Rendez-vous terminé.\n"); // (39) Message final pour indiquer que tout est fini.
    return 0;                       // (40) Quitte le programme avec succès.
}
