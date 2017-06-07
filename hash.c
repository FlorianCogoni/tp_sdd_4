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

liste_chaine_t * recherche(char mot[], tabmaj_t t){
    liste_chaine_t * cour = t.tab[hash_string(mot)];
    while(cour != NULL && (strcmp(cour->mot,mot))){
        cour = cour->suiv;
    }
    return cour;
}

tabmaj_t * creation(){
    int i;
    tabmaj_t * adr_tab =(tabmaj_t *)malloc(sizeof(tabmaj_t));
    for(i=0;i<HASH_MAX;i++){
        adr_tab->tab[i] = NULL;
    }
    return adr_tab;
}

void insertion(char mot[], char trad[], tabmaj_t * t){
    int hash = hash_string(mot);
    liste_chaine_t * adr_mot = (liste_chaine_t *) malloc(sizeof(liste_chaine_t));
    strcpy(adr_mot->mot,mot);
    strcpy(adr_mot->trad,trad);
    adr_mot->suiv = t->tab[hash];
    t->tab[hash] = adr_mot;
}

void traduction(char mot[], tabmaj_t t){
    liste_chaine_t * adr_mot = recherche(mot,t);
    if(adr_mot != NULL) {
        printf("La traduction de %s est %s \n", mot, adr_mot->trad);
    }
    else{
        printf("%s n'est pas dans le dictionnaire \n",mot);
    }
}

void liberation(tabmaj_t * t){
    int i;
    liste_chaine_t * cour;
    for(i=0;i<HASH_MAX;i++){
        cour = t->tab[i];
        while(cour!= NULL){
            cour = cour->suiv;
            free(cour);
        }
        free(t->tab[i]);
    }
    free(t);
}

void trad_liste(char * l[], int n, tabmaj_t * t){
    int i;
    for(i=0;i<n;i++){
        traduction(l[i],*t);
    }
}

void insertion_fichier (char nom[], tabmaj_t * t){
    int i;
    char c;
    FILE * fichier = NULL;
    char mot[30];
    char trad[30];
    fichier = fopen(nom,"r");
    if(fichier != NULL){
        while(!feof(fichier)) {
            fscanf(fichier,"%c",&c);
            i = 0;
            while (c != ';') {
                mot[i] = c;
                i++;
                fscanf(fichier,"%c",&c);
            }
            fgets(trad, 30, fichier);
            insertion(mot, trad, t);
        }
        fclose(fichier);
    }
}