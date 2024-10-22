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

// Question 3 :

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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
