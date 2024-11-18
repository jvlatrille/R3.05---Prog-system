#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Question 1 :

// Fonction appelée quand l'alarme sonne
void msgAlarm(int sig){
    printf("\nAlors ça vient ?\n"); // Affiche un message
    alarm(15); // Relance l'alarme pour 15 secondes
}

int main(){
    // Variables
    char c;
    struct sigaction sig_relance, ancien;
    sig_relance.sa_handler = msgAlarm; // Associe la fonction msgAlarm au signal
    sig_relance.sa_flags = SA_RESTART; // Redémarre les appels système interrompus
    sigemptyset(&sig_relance.sa_mask); // Vide le masque de signaux

    // Créer le signal
    sigaction(SIGALRM, &sig_relance, &ancien); // Configure le signal SIGALRM

    // Créer l'alarme
    alarm(15); // Lance une alarme pour 15 secondes

    // Attendre la saisie utilisateur
    printf("Entrez quelque chose : ");
    scanf("%c", &c); // Attend que l'utilisateur entre un caractère

    // Annuler l'alarme
    alarm(0); // Annule l'alarme

    // Simuler un calcul
    printf("Traitement en cours...\n");
    sigaction(SIGALRM, &ancien, NULL); // Restaure l'ancienne action du signal
    sleep(10); // Attend 10 secondes
}













// Question 2 :

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Structure sigaction
struct sigaction sig_abandon;

void msgAlarm(int sig){
    printf("\nAlors ça vient ?\n");$
    // odification du signal 
    sig_abandon.sa_handler = msgAlarm2;
    sig_abandon.sa_flags = SA_RESETHAND;
    sigemptyset(&sig_abandon.sa_mask);
    sigaction(SIGALRM, &sig_abandon, NULL);
    alarm(30);
}


void msgAlarm2(int sig){
    printf("\nBon j'abandonne !\n");
    exit(0);
}  


int main(){
    // Variables
    char c;
    struct sigaction sig_relance, ancien;
    sig_relance.sa_handler = msgAlarm;
    sig_relance.sa_flags = SA_RESTART;
    sigemptyset(&sig_relance.sa_mask);

    // Créer le signal
    sigaction(SIGALRM, &sig_relance, &ancien);

    // Créer l'alarme
    alarm(15);

    // Attendre la saisie utilisateur
    printf("Entrez quelque chose : ");
    scanf("%c", &c);

    // Annuler l'alarme
    alarm(0);

    // Simuler un calcul
    printf("Traitement en cours...\n");
    sigaction(SIGALRM, &ancien, NULL);
    sleep(10);
}

// Question 3 :

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1000000  // Taille du tableau
#define TARGET 123456 // Élément à rechercher

// Variable globale pour le fils afin de savoir s'il doit interrompre sa recherche
volatile sig_atomic_t arret_fils = 0;

// Gestionnaire du signal SIGUSR1
void handle_sigusr1(int sig) {
    arret_fils = 1;  // Le signal indique d'arrêter la recherche
}

// Fonction de recherche utilisée par le fils
bool search_fils(int *arr, int start, int end, const char *who) {
    for (int i = start; i < end; i++) {
        if (arret_fils) {
            // Si le signal a été reçu, le fils arrête la recherche
            printf("%s a été interrompu\n", who);
            return false;
        }

        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            return true;
        }
    }
    return false;
}

bool search_pere(int *arr, int start, int end, const char *who) {
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            return true;
        }
    }
    return false;
}

int main() {
    int *arr = malloc(SIZE * sizeof(int));
    if (arr == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation du tableau avec des valeurs quelconques
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    pid_t pid = fork();  // Création d'un processus fils

    if (pid < 0) {
        perror("Erreur lors de la création du processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Code du processus fils : il explore la 2ème moitié du tableau
        signal(SIGUSR1, handle_sigusr1);  // Installation du gestionnaire de signal

        bool fils_trouve = search_fils(arr, SIZE / 2, SIZE, "Le fils");

        if (fils_trouve) {
            // Si le fils trouve l'élément, il sort
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else {
        // Code du processus père : il explore la 1ère moitié du tableau
        bool pere_trouve = search_pere(arr, 0, SIZE / 2, "Le père");

        if (pere_trouve) {
            // Si le père trouve l'élément, il envoie SIGUSR1 au fils
            kill(pid, SIGUSR1);
        }

        // Le père attend que le fils termine
        wait(NULL);

        // Si ni le père ni le fils n'ont trouvé l'élément
        if (!pere_trouve) {
            printf("L'élément n'a pas été trouvé\n");
        }
    }

    free(arr);  // Libération de la mémoire
    return 0;
}




//Question 3 corrigée : 
DEFINE TAILLE 1000000

struct sigaction pere_trouve;

void trouve(int sig){
    exit(EXIT_SUCCESS);
}

int main(){
    int tableau[TAILLE];
    pid_t id;
    id = fork();
    
    switch (id)
    {
    case -1:
        printf("Erreur lors de la création du processus\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        pere_trouve.sa_handler = trouve;
        pere_trouve.sa_flags = SA_RESTART;
        sig_emptyset(&pere_trouve.sa_mask);
        sigaction(SIGUSR1, pere_trouve, NULL);
        break;
    default:
        kill(id, SIGUSR1);
        wait(&etat);
        exit(EXIT_SUCCESS);
        break;
    }
}


// Question 4 correction :

DEFINE TAILLE 1000000
int arreter = 0;

struct sigaction pere_trouve, fils_trouve;

void ptrouve(int sig){
    exit(EXIT_FAILURE);
}

void ftrouve(int sig){
    wait(&etat);
    if(WEXIT_STATUS(etat) == EXIT_SUCCESS){
        exit(EXIT_SUCCESS);
        printf("L'élément a été trouvé\n");
        arreter = 1;
    }
    else{
        exit(EXIT_FAILURE);
    }
}

int main(){
    int tableau[TAILLE];
    pid_t id;
    id = fork();
    
    switch (id)
    {
    case -1:
        printf("Erreur lors de la création du processus\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        pere_trouve.sa_handler = trouve;
        pere_trouve.sa_flags = SA_RESTART;
        sig_emptyset(&pere_trouve.sa_mask);
        sigaction(SIGUSR1, pere_trouve, NULL);
        break;
    default:
        fils_trouve.sa_handler = arret;
        fils_trouve.sa_flags = SA_RESTART;
        sig_emptyset(&fils_trouve.sa_mask);
        sigaction(SIGUSR1, fils_trouve, NULL);
        while ((j<TAILLE) && (tableau[j] != valeur) && (arreter == 0))
        {
            j++;
        }
        
        if((j<TAILLE/2) && (arreter==0){
            kill(id, SIGUSR1);
        }
        wait(&etat);
        exit(EXIT_SUCCESS);
        break;
    }
}