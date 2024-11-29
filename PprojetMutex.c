#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>

// Structure pour la mémoire partagée
typedef struct {
    int participants_arrives;
    pthread_mutex_t mutex; // Mutex POSIX pour synchronisation inter-processus
} SharedData;

int main() {
    int total_participants;

    printf("Entrez le nombre de participants : ");
    scanf("%d", &total_participants);

    // Création de la mémoire partagée
    SharedData* shared_data = mmap(NULL, sizeof(SharedData),
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_data == MAP_FAILED) {
        perror("Erreur lors de la création de la mémoire partagée");
        exit(EXIT_FAILURE);
    }

    // Initialisation des données partagées
    shared_data->participants_arrives = 0;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED); // Mutex inter-processus
    pthread_mutex_init(&shared_data->mutex, &attr);

    pid_t pids[total_participants];

    for (int i = 0; i < total_participants; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Erreur lors de la création du processus");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) { // Processus fils
            srand(getpid());
            printf("Participant %d arrive.\n", i + 1);
            sleep(rand() % 3 + 1); // Temps aléatoire avant d'arriver

            // Entrée dans la section critique
            pthread_mutex_lock(&shared_data->mutex);
            shared_data->participants_arrives++;
            if (shared_data->participants_arrives == total_participants) {
                printf("Participant %d est le dernier, le rendez-vous peut commencer !\n", i + 1);
            }
            pthread_mutex_unlock(&shared_data->mutex);

            // Simulation du travail après le rendez-vous
            printf("Participant %d commence le travail.\n", i + 1);
            exit(EXIT_SUCCESS); // Le processus fils termine
        } else {
            pids[i] = pid; // Sauvegarde des PIDs des processus fils
        }
    }

    // Attente de tous les processus fils
    for (int i = 0; i < total_participants; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // Nettoyage des ressources
    pthread_mutex_destroy(&shared_data->mutex);
    munmap(shared_data, sizeof(SharedData)); // Libération de la mémoire partagée

    printf("Tous les participants ont terminé. Rendez-vous terminé.\n");
    return 0;
}
