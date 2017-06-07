#ifndef HASH
#define HASH
#define HASH_MAX 29

typedef struct liste_chaine{
    char mot[30];
    char trad[30];
    struct liste_chaine * suiv;
}liste_chaine_t;

typedef struct tabmaj{
    liste_chaine_t * tab[HASH_MAX];
} tabmaj_t;

liste_chaine_t * recherche(char mot[], tabmaj_t t);
tabmaj_t * creation();
void insertion(char mot[], char trad[], tabmaj_t *t);
void traduction(char mot[], tabmaj_t t);
void liberation(tabmaj_t * t);
void trad_liste(char * l[], int n, tabmaj_t * t);
void insertion_fichier(char nom[], tabmaj_t * t);

#endif