#include <stdio.h>              // Inclut la bibliothèque standard pour les entrées/sorties (printf, scanf, etc.)
#include <pthread.h>            // Inclut la bibliothèque pour la gestion des threads en C.
#include <unistd.h>             // Inclut la bibliothèque pour les fonctions Unix standard (comme sleep).
#include <stdlib.h>             // Inclut les fonctions standards C comme malloc, exit, etc.
#include <time.h>               // Inclut la bibliothèque pour la gestion du temps (comme clock).

// Variables globales
int nbThreadsPresents = 0;      // Compteur pour suivre le nombre de threads actifs.
int X;                          // Nombre de threads à créer, défini par l'utilisateur.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex pour protéger les accès concurrents à nbThreadsPresents.
int nbPersonnes;                // Variable pour stocker temporairement le nombre de threads actifs.
int nbSec = 0;                  // Compteur de secondes, utilisé dans le travail des threads.

/* Manque la temporisation aléatoire */
// TODO : Ajouter une fonctionnalité pour générer un délai aléatoire.

void* travail() {
    // Fonction exécutée par chaque thread.
    
    // Attendre 2 secondes avant de commencer le travail.
    sleep(2);
    printf("Je suis là \n");

    // Accès protégé à la variable partagée nbThreadsPresents.
    pthread_mutex_lock(&mutex); // Verrouille le mutex pour éviter les accès concurrents.
    nbThreadsPresents++;       // Incrémente le compteur de threads actifs.
    nbPersonnes = nbThreadsPresents; // Copie le nombre de threads actifs dans nbPersonnes.
    pthread_mutex_unlock(&mutex); // Déverrouille le mutex.

    // Boucle pour vérifier les conditions avant d'effectuer la tâche.
    while(1) {
        sleep(1);               // Attendre une seconde entre chaque itération.
        pthread_mutex_lock(&mutex); // Verrouille le mutex pour lire nbSec en toute sécurité.
        if(nbSec == 10) {       // Vérifie si le temps écoulé est de 10 secondes.
            break;              // Sort de la boucle si le temps est écoulé.
        }
        pthread_mutex_unlock(&mutex); // Déverrouille le mutex après lecture.
        if(nbPersonnes == X) {  // Vérifie si tous les threads sont présents.
            break;              // Sort de la boucle si tous les threads sont prêts.
        }
    }

    // Si le temps limite est atteint avant que les conditions soient remplies.
    if(nbSec == 10) {
        printf("Je suis ban :/\n"); // Affiche un message pour signaler l'abandon de la tâche.
        pthread_exit(NULL);        // Termine le thread.
    }
    // Si les conditions sont remplies, exécute la tâche.
    printf("J'effectue ma tâche \n");
    pthread_exit(NULL);            // Termine le thread après avoir effectué la tâche.
}

int main(void) {
    // Fonction principale du programme.
    
    // Variables locales.
    clock_t horloge = clock();     // Initialise une horloge pour mesurer le temps.
    pthread_attr_t attr;           // Attributs pour les threads.

    // Récupérer le nombre de threads à créer.
    printf("Combien de personnes ? ");
    scanf("%d", &X);               // Demande à l'utilisateur le nombre de threads à créer.

    // Création d'un tableau pour stocker les identifiants des threads.
    pthread_t threads[X];

    // Initialisation des attributs des threads.
    pthread_attr_init(&attr);
    for(int i = 0; i < X; i++) {   // Boucle pour créer X threads.
        pthread_create(&threads[i], &attr, travail, NULL); // Crée un thread qui exécute la fonction travail.
    }

    // Attendre que tous les threads terminent leur exécution.
    for(int i = 0; i < X; i++) {
        pthread_join(threads[i], NULL); // Bloque jusqu'à la fin de chaque thread.
    }

    // Tous les threads ont terminé leur travail.

    return 0;                      // Termine le programme avec succès.
}
