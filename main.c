#include <stdio.h>
#include "hash.h"

int main() {
    char * l[4] = {
            "rouge",
            "bleu",
            "vert",
            "violet"
    };
    char * l2[6] = {
            "bras",
            "oeil",
            "oreille",
            "ça",
            "micro-ondes",
            "salut"
    };
    tabmaj_t * adr_tab = creation();
    insertion("patate","potato",adr_tab);
    insertion("gachette","trigger",adr_tab);
    insertion("rouge","red",adr_tab);
    insertion("bleu","blue",adr_tab);
    insertion("vert","green",adr_tab);
    insertion("cuiller","spoon",adr_tab);
    insertion_fichier("./essai.txt",adr_tab);
    traduction("patate",*adr_tab);
    trad_liste(l,4,adr_tab);
    trad_liste(l2,6,adr_tab);
    traduction("cuiller",*adr_tab);
    traduction("patato",*adr_tab);
    liberation(adr_tab);
    return 0;
}