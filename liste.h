#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUT "<debut>"

typedef struct Cellule Cellule;
struct Cellule {
    char* nom;
    Cellule* suivante;
};

typedef struct Liste Liste;
struct Liste {
    Cellule* premiere;
};


Liste* initialise();


void supprime(Liste* liste);


int ajouter(Liste* liste, char* nvNom);


int trouver(Liste* liste, char* nvNom);


void afficher(Liste* liste);
