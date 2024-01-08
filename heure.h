#ifndef HEURE_H
#define HEURE_H

struct heure {
   unsigned int h;
   unsigned int m;
   unsigned int s;
};
typedef struct heure Heure;

void afficheHeure(Heure h);
// void saisieHeure(Heure *h);
void saisieHeureDebut(Heure *h);
void saisieHeureFin(Heure *h,Heure h2);
int validateHeure(Heure heure);
int compareHeures(Heure heure1, Heure heure2);
int validateHeureDebut(Heure heure);
int validateHeureFin(Heure heure1,Heure heure2);
#endif // HEURE_H