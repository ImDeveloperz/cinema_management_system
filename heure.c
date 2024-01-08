#include <stdio.h>
#include <stdlib.h>
#include "heure.h"

// afficher heure
void afficheHeure(Heure h)
{
    printf(" %d:%d:%d \n", h.h, h.m, h.s);
}

// saisir heure
void saisieHeureDebut(Heure *h)
{
    do
    {
        printf("\n saisir l'heure sous form hh:mm:ss : ");
        scanf("%d:%d:%d", &h->h, &h->m, &h->s);
        getchar();
    } while (validateHeureDebut(*h) == 0);
    // on peut verifier si la date juste ou non ...
}


void saisieHeureFin(Heure *h,Heure h2)
{
    do
    {
        printf("\n saisir l'heure sous form hh:mm:ss : ");
        scanf("%d:%d:%d", &h->h, &h->m, &h->s);
        getchar();
    } while (validateHeureFin(*h,h2) == 0);
    // on peut verifier si la date juste ou non ...
}

int validateHeure(Heure heure) {
    if (heure.h< 0 || heure.h > 23) {
        printf("\nl'heure doit etre Comprit entre 00 et 23\n");
        return 0; // Heure invalide
    }

    if (heure.m < 0 || heure.m > 59) {
        printf("\nle minute doit etre Comprit entre 00 et 59\n");
        return 0; // Minutes invalides
    }

    if (heure.s < 0 || heure.s > 59) {
        printf("\nla seconde  doit etre Comprit entre 00 et 59\n");
        return 0; // Secondes invalides
    }

    // Si les vérifications précédentes sont passées, l'heure est valide
    return 1;
}

int compareHeures(Heure heure1, Heure heure2)
{
if (heure1.h < heure2.h + 2 )
    {
        printf("la date du fin doit etre superieure par 2h a la date de debut : \n");
        afficheHeure(heure2);
        return -1;
    }
    else if (heure1.h >= heure2.h + 2)
    {
        return 1;
    }
}

int validateHeureDebut(Heure heure){
    return validateHeure(heure);
}


int validateHeureFin(Heure heure1,Heure heure2){
    int test = validateHeure(heure1);
    if(test == 0){
        return 0;
    }else{
        if(compareHeures(heure1,heure2) == -1){
            return 0;
        }else{
            return 1;
        }
    }
}

