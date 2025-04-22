#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nume[30];
    int nota;
}Student;

Student *citeste_studenti(int n)
{
    Student *studenti;

    if((studenti = malloc(n * sizeof(Student))) == NULL)
    {
        perror("Nu s-a putut aloca memorie. \n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++)
    {
        printf("Nume : ");
        fgets(studenti[i].nume, 30, stdin);
        studenti[i].nume[strcspn(studenti[i].nume, "\n")] = '\0';

        do{
            printf("Nota : ");
            scanf("%d", &studenti[i].nota);
        }
        while(studenti[i].nota > 10);
        getchar();
    }

    return studenti;
}

void afiseaza_studenti(Student *studenti, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%s - %d \n", studenti[i].nume, studenti[i].nota);
    }
}

int compara (const void *elem1, const void *elem2)
{
    const Student *pa = (const Student *) elem1;
    const Student *pb = (const Student *) elem2;

    if(pa -> nota != pb -> nota)
    {
        return -(pa -> nota - pb -> nota);
    }
    else
    {   
        return strcmp(pa -> nume, pb -> nume);
    }
}

int main(void)
{   
    int n;
    printf("Introduceti numarul de studenti: ");
    if(scanf("%d", &n) != 1)
    {
        perror("Nu s-a citit bn nr de studenti.\n");
        exit(EXIT_FAILURE);
    }

    getchar();
    Student *studenti = citeste_studenti(n);

    qsort(studenti, n, sizeof(Student), compara);
    printf("\n");

    afiseaza_studenti(studenti, n);

    free(studenti);
    return 0;
}