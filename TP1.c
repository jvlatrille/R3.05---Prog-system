#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int choix;
    printf("Question : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        printf("\n");
        question1();
        break;
    case 2:
        printf("\n");
        question2();
        break;
    case 3:
        printf("\n");
        question3();
        break;
    default:
        printf("J'ai pas ça.%d\n", choix);
        break;
    }

    return 0;
};

void question1()
{
    printf("Exercice 1\n");
    pid_t pid = getpid();
    printf("Je suis le processus numéro %x\n", pid);
    int pidF = fork();
    printf("Fork m'a renvoyé la valeur %x\n", pidF);
    if (pidF == 0)
    {
        printf("Je suis le fils, mon pid est %x et mon père est %x\n", getpid(), getppid());
    }
    else
    {
        printf("Je suis le père, mon pid est %x et mon fils est %x\n", getpid(), pidF);
    }
}

void question2()
{
    // Créer le processus fils
    int fils = fork();

    if (fils < 0)
    {
        printf("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }

    else if (fils == 0)
    {
        printf("Processus fils\n");
        for (int i = 0, count = 0; count < 10; i += 2, count++)
        {
            printf("%d ", i);
        }
        printf("\n");
    }

    else
    {
        printf("Processus père\n");
        for (int i = 1, count = 0; count < 10; i += 2, count++)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}

void question3()
{
    
}