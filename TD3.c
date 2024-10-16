// Question 1

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
/*
#define TAILLE 10

int main()
{

    // INITIALISATION DES VARIABLES
    // INITIALISATION DU TABLEAU
    const int TAILLE = 100;
    int tab[TAILLE];
    int somme = 0;
    int max = 0;
int case = 0;
    // INITIALISATION DU TUBE
    int tube[2];
    int x = pipe(tube);
    // CREATION DU PROCESSUS FILS
    pid_t pid = fork();

    // REMPLISSAGE DU TABLEAU
    for (case = 0; case <= TAILLE; case ++) {
        tab[case] = case;
    }

switch (pid) {
    // LE PROCESSUS NE SE CREE PAS, LA CONNEXION EST IMPOSSIBLE
    case -1:
    printf("Création impossible");
    exit(EXIT_FAILURE);
    break;

// PROCESSUS FILS
case 0:
    // FERMER LE TUBE EN LECTURE
    close(tube[0]);
    int calcul = 0;
    int i;

    // CALCUL POUR LA PREMIERE MOITIE DU TABLEAU
    for (i = 0; i < TAILLE / 2; i++)
    {
        calcul += tab[i];
    }
    // ENVOYER LE RESULTAT AU PERE
    write(tube[1], &calcul, sizeof(int));
    // FERMER LE TUBE EN ECRITURE
    close(tube[1]);
    exit(EXIT_SUCCESS);
    break;

default:
    //FERMETURE DU TUBE EN ECRITURE
    close(tube[1]);
    int calcul = 0;
    int i;

    //CALCUL DE LA SOMME DE LA SECONDE MOITIE DU TABLEAU
    for (i = TAILLE / 2; i < TAILLE; i++)
    {
        calcul += tab[i];
    }
    //LECTURE DU RESULTAT DU FILS
    read(tube[0], &somme, sizeof(int));
    //FERMETURE DU TUBE EN LECTURE
    close(tube[0]);
    //CALCUL DE LA SOMME TOTAL
    somme = somme + calcul;
    //ATTEND QUE LE PROCESSUS FILS SE TERMINE
    wait(pid);
    printf("cumul obtenu : %lu\n", somme);
    exit(EXIT_SUCCESS);
    break;
}
}*/

// Question 2 :
int lireVaw(*int, *int); // 1 si fichier fini, 0 sinon

pipe(tubeEnvoy);
pipe(tubeRecupMax);

int main()
{
    int pidfils;
    int tube_donnees[2], tube_resultat[];

    pidfils = fork();
    switch (pidfils)
    {
    case -1:
        exit(EXIT_FAILURE);
        break;

    case 0:
        int droite;
        long somme = 0;
        int maxGauche = 0;
        int cptGauche = 0;

        close(tube_donnees[1]);
        close(tube_resultat[0]);
        int fini = 0;
        while (fini == 0)
        {
            read(tube_donnees[0], &droite, sizeof(int));
            int(droite >) ///
        }
    default:
        break;
    }
}