#include<stdio.h>
#include<stdlib.h>
#include"heure.h"


// afficher heure
void afficheHeure(Heure h) {
    printf(" %d:%d:%d \n",h.h,h.m,h.s);
}

// saisir heure
void saisieHeure(Heure *h){
    printf("\n saisir l'heure sous form hh:mm:ss : ");
    scanf("%d:%d:%d",&h->h, &h->m , &h->s );
    // on peut verifier si la date juste ou non ...
}
