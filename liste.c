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

Liste* tabSymbol;

void initialise() {
    tabSymbol = malloc(sizeof(Liste));
    Cellule* cellule = malloc(sizeof(Cellule));
    if (tabSymbol == NULL || cellule == NULL)  {
        exit(EXIT_FAILURE);
    }
    cellule->nom = malloc(strlen(DEBUT)+1);
    strncpy(cellule->nom, DEBUT, strlen(DEBUT));
    cellule->suivante = NULL;
    tabSymbol->premiere = cellule;
}


void supprime(Liste* tabSymbol) {
    if (tabSymbol == NULL) {
        exit(EXIT_FAILURE);
    }
    if (tabSymbol->premiere != NULL)
    {
        Cellule* bientotPlusLa = tabSymbol->premiere;
        tabSymbol->premiere = tabSymbol->premiere->suivante;
        free(bientotPlusLa);
    }
}


int ajouter(char* nvNom) {
    Cellule* nouvelle = malloc(sizeof(*nouvelle));
    if (tabSymbol == NULL || nouvelle == NULL) {
        exit(EXIT_FAILURE);
    }
    nouvelle->nom = malloc(strlen(nvNom)+1);
    strncpy(nouvelle->nom, nvNom, strlen(nvNom));

    int compteur = 0;
    Cellule* actuelle = tabSymbol->premiere;
    //printf("compteur ");
    int found = 0;
    while (!found && actuelle->suivante != NULL) {
      if (strcmp(nvNom, actuelle->nom)==0) {
        found = 1;
        break;
      }
    //printf("%d ",compteur);
      compteur++;
        actuelle = actuelle->suivante;
    }
    //printf(" ; found %d\n",found);
    // on rajoute que s'il y a besoin
    if(!found && strcmp(nvNom, actuelle->nom)!=0) {
      actuelle->suivante = nouvelle;
      nouvelle->suivante = NULL;
      compteur++;  //on rajoute un element en plus
    }
    return compteur;
}


int trouver(char* nvNom) {
    int compteur = 0;
    int arg = -1;
    Cellule* actuelle = tabSymbol->premiere;
    while (actuelle != NULL && arg < 0) {
      if (strcmp(nvNom, actuelle->nom)==0)
        arg = compteur;
      compteur++;
      actuelle = actuelle->suivante;
    }
    return arg;
}


void afficher() {
    if (tabSymbol == NULL) {
        exit(EXIT_FAILURE);
    }
    Cellule* actuelle = tabSymbol->premiere;
    while (actuelle != NULL) {
        printf("%s -> ", actuelle->nom);
        actuelle = actuelle->suivante;
    }
    printf("NULL\n");
}

int main() {

    initialise();
    printf("ajouter titi: %d\n",ajouter( "titi"));
    printf("trouver titi: %d\n",trouver( "titi"));
    afficher(tabSymbol);
    printf("ajouter totodu31: %d\n",ajouter( "totodu31"));
    printf("trouver titi: %d\n",trouver( "titi"));
    printf("trouver totodu31: %d\n",trouver( "totodu31"));
    afficher(tabSymbol);
    printf("ajouter totodu31400: %d\n",ajouter( "totodu31400"));
    printf("trouver totodu31400: %d\n",trouver( "totodu31400"));
    afficher(tabSymbol);
    printf("ajouter totodu31: %d\n",ajouter( "totodu31"));
    printf("trouver totodu31: %d\n",trouver( "totodu31"));
    afficher(tabSymbol);
    printf("ajouter totodu31400: %d\n",ajouter( "totodu31400"));
    printf("trouver totodu31400: %d\n",trouver( "totodu31400"));
    afficher(tabSymbol);
    supprime(tabSymbol);

    return 0;
}
