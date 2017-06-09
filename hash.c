#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"


unsigned int hash_string(const char *str)
{
    unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
    const char *s;
    for (s = str; *s; s++)
        hash = ((hash << 5) + hash) + tolower(*s);
    return (hash & 0x7FFFFFFF)%HASH_MAX;
}


tabmaj_t * creation()
{
    int i;
    tabmaj_t * adr_tab =(tabmaj_t *)malloc(sizeof(tabmaj_t));
    for(i=0;i<HASH_MAX;i++) /* création des 29 cases de la table majeur */
    {
        adr_tab->tab[i] = NULL; /* il n'y a pour l'instant aucun mot, on pointe vers NULL */
    }
    return adr_tab;
}



liste_chaine_t * recherche(char mot[], tabmaj_t t)
{
    liste_chaine_t * cour = t.tab[hash_string(mot)];  /* on récupère l'adresse de la liste où le mot est présent */
    while(cour != NULL && (strcmp(cour->mot,mot)))  /* on suppose que les mots ne sont pas triés */
    {
        cour = cour->suiv;
    }
    return cour;  /* on retourne l'adresse du mot */
}


void insertion(char mot[], char trad[], tabmaj_t * t)
{
    int hash = hash_string(mot);  /* on récupère le hash du mot */
    liste_chaine_t * adr_mot = (liste_chaine_t *) malloc(sizeof(liste_chaine_t)); /* on alloue l'espace suffisant */
    strcpy(adr_mot->mot,mot); /* on ajoute le mot */
    strcpy(adr_mot->trad,trad); /* on ajoute la trad */
    adr_mot->suiv = t->tab[hash]; /* on met le bloc au début de la liste */
    t->tab[hash] = adr_mot;
}

void insertion_fichier (char nom[], tabmaj_t * t)
{
    int i;
    char c;
    FILE * fichier = NULL;
    char mot[30]="";
    char trad[30]="";
    fichier = fopen(nom,"r");
    if(fichier != NULL)
    {
        while(!feof(fichier)) /* tant qu'on est pas à la fin du fichier */
        {
            fscanf(fichier,"%c",&c);  /* on prend caractère par caractère ... */
            i = 0;
            while (c != ';')  /* ... jusqu'au point-virgule */
            {
                mot[i] = c;
                i++;
                fscanf(fichier,"%c",&c);
            }
            mot[i]='\0';  /* on marque la fin du mot */
            fgets(trad, 30, fichier); /* on récupère le reste de la ligne qui est la trad */
            insertion(mot, trad, t);  /* on insère le mot et la trad */
        }
        fclose(fichier);
    }
}


void traduction(char mot[], tabmaj_t t)
{
    liste_chaine_t * adr_mot = recherche(mot,t);  /* on récupère l'adresse du bloc de mot */
    if(adr_mot != NULL) /* le mot existe dans le dico */
    {
        printf("La traduction de %s est %s \n", mot, adr_mot->trad);
    }
    else  /* le mot n'existe pas dans le dico */
    {
        printf("%s n'est pas dans le dictionnaire \n\n",mot);
    }
}

void trad_liste(char * l[], int n, tabmaj_t * t)
{
    int i;
    for(i=0;i<n;i++)  /* on traduit chaque élément de l[] */
    {
        traduction(l[i],*t);
    }
}


void liberation(tabmaj_t * t)
{
    int i;
    liste_chaine_t * cour;
    for(i=0;i<HASH_MAX;i++) /* pour chaque liste */
    {
        cour = t->tab[i];
        while(cour!= NULL)  /* on libère la liste */
        {
            cour = cour->suiv;
            free(cour);
        }
        free(t->tab[i]);  /* on libère l'adresse de la liste */
    }
    free(t);  /* on libère l'adresse du dico */
}
