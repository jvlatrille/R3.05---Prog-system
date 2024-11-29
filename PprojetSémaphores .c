#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Définition des opérations P (wait) et V (signal) pour les sémaphores
struct sembuf P = {0, -1, 0}; // Décrémenter le sémaphore
struct sembuf V = {0, 1, 0};  // Incrémenter le sémaphore

int main() {
    int total_participants;
    printf("Entrez le nombre de participants : ");
    scanf("%d", &total_participants);

    key_t key = IPC_PRIVATE; // Clé pour les sémaphores
    int sem_id = semget(key, 2, IPC_CREAT | 0666); // Création de 2 sémaphores
    if (sem_id == -1) {
        perror("Erreur lors de la création des sémaphores");
        exit(EXIT_FAILURE);
    }

    // Initialisation des sémaphores
    semctl(sem_id, 0, SETVAL, 1); // Mutex pour protéger la section critique
    semctl(sem_id, 1, SETVAL, 0); // Synchronisation du rendez-vous

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

            // Entrée en section critique
            semop(sem_id, &P, 1); // P(mutex)
            static int participants_arrives = 0;
            participants_arrives++;
            if (participants_arrives == total_participants) {
                printf("Participant %d est le dernier, le rendez-vous commence !\n", i + 1);
                for (int j = 0; j < total_participants; j++) {
                    semop(sem_id + 1, &V, 1); // Débloquer tous les participants
                }
            }
            semop(sem_id, &V, 1); // V(mutex)

            // Attente pour commencer le travail
            semop(sem_id + 1, &P, 1); // P(rendezvous)
            printf("Participant %d commence le travail.\n", i + 1);
            exit(EXIT_SUCCESS); // Le processus fils termine
        } else {
            pids[i] = pid; // Sauvegarde du PID du processus fils
        }
    }

    // Attente de tous les processus fils
    for (int i = 0; i < total_participants; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // Suppression des sémaphores
    semctl(sem_id, 0, IPC_RMID, 0);
    semctl(sem_id + 1, 0, IPC_RMID, 0);

    printf("Tous les participants ont terminé. Rendez-vous terminé.\n");
    return 0;
}
