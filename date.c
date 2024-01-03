#include<stdio.h>
#include<stdlib.h>
#include"date.h"


// afficher date
void afficheDate(Date d) {
    printf(" %d/%d/%d\n",d.j,d.m,d.a);
}

// saisir date
void saisieDate(Date *d){
    printf("\n saisir la date sous form dd/mm/aa : ");
    scanf("%d/%d/%d",&d->j, &d->m , &d->a );
    // on peut verifier si la date juste ou non ...
}