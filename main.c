#include <stdio.h>
#include "hash.h"

int main() {
    char * ListeATraduire1[4] = {
            "rouge",
            "bleu",
            "vert",
            "violet"
    };
    char * ListeATraduire2[7] = {
            "bras",
            "oeil",
            "oreille",
            "ça",
            "orange",
            "micro-ondes",
            "salut"
    };
    tabmaj_t * adr_tab_vide = creation();
    tabmaj_t * adr_tab_normal = creation();
    printf("Insertion d'un fichier texte :\n\n");
    insertion_fichier("normal.txt",adr_tab_normal);
    printf("Test traduction table vide :\n\n");
    trad_liste(ListeATraduire1,4,adr_tab_vide);
    printf("\n");
    printf("Test traduction table normale :\n\n");
    trad_liste(ListeATraduire1,4,adr_tab_normal);
    printf("\n");
    trad_liste(ListeATraduire2,7,adr_tab_normal);
    printf("Libération des tables :\n\n");
    liberation(adr_tab_normal);
    liberation(adr_tab_vide);
    printf("Fin des tests\n");
    return 0;
}
