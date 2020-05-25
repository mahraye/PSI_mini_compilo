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


Liste* initialise() {
    Liste* liste = malloc(sizeof(*liste));
    Cellule* cellule = malloc(sizeof(*cellule));

    if (liste == NULL || cellule == NULL)  {
        exit(EXIT_FAILURE);
    }

    cellule->nom = malloc(strlen(DEBUT)+1);
    strncpy(cellule->nom, DEBUT, strlen(DEBUT));    
    cellule->suivante = NULL;
    liste->premiere = cellule;

    return liste;
}


void supprime(Liste* liste) {
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    if (liste->premiere != NULL)
    {
        Cellule* bientotPlusLa = liste->premiere;
        liste->premiere = liste->premiere->suivante;
        free(bientotPlusLa);
    }
}


int ajouter(Liste* liste, char* nvNom) {
    Cellule* nouvelle = malloc(sizeof(*nouvelle));
    if (liste == NULL || nouvelle == NULL) {
        exit(EXIT_FAILURE);
    }
    nouvelle->nom = malloc(strlen(nvNom)+1);
    strncpy(nouvelle->nom, nvNom, strlen(nvNom));    

    int compteur = 0; 
    Cellule* actuelle = liste->premiere;
    //printf("compteur ");
    int found = 0;
    while (!found && actuelle->suivante != NULL){
    	if (strcmp(nvNom, actuelle->nom)==0){
    		found = 1;
    		break;    		
    	}
		//printf("%d ",compteur);
    	compteur++;
        actuelle = actuelle->suivante;
    }
    //printf(" ; found %d\n",found);
    // on rajoute que s'il y a besoin
    if(!found && strcmp(nvNom, actuelle->nom)!=0){
	    actuelle->suivante = nouvelle;
	    nouvelle->suivante = NULL;  
	    compteur++;  //on rajoute un element en plus	
    }
    return compteur;
}


int trouver(Liste* liste, char* nvNom) {
    int compteur = 0; 
    int arg = -1;
    Cellule* actuelle = liste->premiere;
    while (actuelle != NULL && arg < 0) {
    	if (strcmp(nvNom, actuelle->nom)==0)
    		arg = compteur;
    	compteur++;
        actuelle = actuelle->suivante;
    }
    return arg;
}


void afficher(Liste* liste) {
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Cellule* actuelle = liste->premiere;

    while (actuelle != NULL) {
        printf("%s -> ", actuelle->nom);
        actuelle = actuelle->suivante;
    }
    printf("NULL\n");
}


int main() {
    Liste* maListe = initialise();

    printf("ajouter titi: %d\n",ajouter(maListe, "titi"));
    printf("trouver titi: %d\n",trouver(maListe, "titi"));
    afficher(maListe);
    printf("ajouter totodu31: %d\n",ajouter(maListe, "totodu31"));
    printf("trouver titi: %d\n",trouver(maListe, "titi"));
    printf("trouver totodu31: %d\n",trouver(maListe, "totodu31"));
    afficher(maListe);
    printf("ajouter totodu31400: %d\n",ajouter(maListe, "totodu31400"));
    printf("trouver totodu31400: %d\n",trouver(maListe, "totodu31400"));
    afficher(maListe);
    printf("ajouter totodu31: %d\n",ajouter(maListe, "totodu31"));
    printf("trouver totodu31: %d\n",trouver(maListe, "totodu31"));
    afficher(maListe);
    printf("ajouter totodu31400: %d\n",ajouter(maListe, "totodu31400"));
    printf("trouver totodu31400: %d\n",trouver(maListe, "totodu31400"));
    afficher(maListe);
    supprime(maListe);

    return 0;
}