#ifndef HEURE_H
#define HEURE_H

struct heure {
   unsigned int h;
   unsigned int m;
   unsigned int s;
};
typedef struct heure Heure;

void afficheHeure(Heure h);
void saisieHeure(Heure *h);

#endif // HEURE_H