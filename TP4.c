#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/*
Question 1 et question 2 mdr

int main()
{
    int tube[2];
    pid_t pid;

    // Crée le tube (et envoie erreur si problème)
    if (pipe(tube) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    // Si erreur
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // dans le tube, le fils récupère ces caractères et les affiche après les avoir mis 
    // en majuscule (fonction toupper)
    if (pid == 0)
    {
        close(tube[1]); // On ferme le tube en écriture
        char sortie;
        // Tant qu'il y a des caractères à lire
        while (read(tube[0], &sortie, 1) > 0) {
            // 'Envoie de $ par père pour que' le fils s'en serve pour se terminer
            if (sortie == '$') {
                printf("\nProcessus fils reçoit le '$'\n");
                break;
            }
            putchar(toupper(sortie)); // Un put les caractères en majuscule
        }
    }

    // Le père lit des caractères au clavier (getchar) et les écrit dans le tube
    else
    {
        close(tube[0]); // On ferme le tube en lecture
        char entree;
        while ((entree = getchar()) != EOF) // On récup l'entrée 
        {
            write(tube[1], &entree, 1); // On écrit l'entrée dans le tube
            // La saisie du caractère '$' termine le programme
            if (entree == '$')
            {
                printf("Processus père envoie le '$'\n");
                close(tube[1]);
                exit(EXIT_SUCCESS);
                break;
            }
        }
    }
}*/


int main()
{
    int tube[2];
    pid_t pid;

    // Crée le tube (et envoie erreur si problème)
    if (pipe(tube) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    // Si erreur
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // dans le tube, le fils récupère ces caractères et les affiche après les avoir mis 
    // en majuscule (fonction toupper)
    if (pid == 0)
    {
        close(tube[1]); // On ferme le tube en écriture
        char sortie;
        // Tant qu'il y a des caractères à lire
        while (read(tube[0], &sortie, 1) > 0) {
            // 'Envoie de $ par père pour que' le fils s'en serve pour se terminer
            if (sortie == '$') {
                printf("\nProcessus fils reçoit le '$'\n");
                break;
            }
            putchar(toupper(sortie)); // Un put les caractères en majuscule
        }
    }

    // Le père lit des caractères au clavier (getchar) et les écrit dans le tube
    else
    {
        close(tube[0]); // On ferme le tube en lecture
        char entree;
        while ((entree = getchar()) != EOF) // On récup l'entrée 
        {
            write(tube[1], &entree, 1); // On écrit l'entrée dans le tube
            // La saisie du caractère '$' termine le programme
            if (entree == '$')
            {
                printf("Processus père envoie le '$'\n");
                close(tube[1]);
                exit(EXIT_SUCCESS);
                break;
            }
        }
    }
}