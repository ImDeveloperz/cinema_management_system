#ifndef SALLECENIMA_H
#define SALLECENIMA_H

#include"projection.h"

struct salleCenima
{
    unsigned int salleId;
    char *nomSalle;
    char *equipementSalle;
    char *emplacementSalle;
    unsigned int capaciteSalle;
    Projection *projection;
    unsigned int nombreProjection;
};
typedef struct salleCenima SalleCenima ; 

static unsigned int CSC = 0;

extern SalleCenima *salles ;

extern int nb_salles;

// ----------------InitialiserSalle-------------------------------

void saisieSalleCenima(SalleCenima *S);
// -----------------------getteur----------------------------

int getCapaciterSalleFromSalleParId(int idSalle);

// ---------------------------Ajout----------------------------
// --------------------AjouterProjectionPourSalle-------------------------------

void ajouterProjectionPourSalle(SalleCenima *salle, Projection nouvelleProjection);

void ajouterProjectionPourSalleParId(Projection p,unsigned int idSalle);

// --------------------AjouterProjectionPourSalle-------------------------------

void ajoutSalleDansLaListeDeSalles(SalleCenima **tabSalles, int *nombreSalle, SalleCenima sc) ;

// ---------------------Recherche-------------------------------

SalleCenima* rechercheSalleParNom( SalleCenima *salles,unsigned int taille, char* salleNom);
SalleCenima* rechercheSalleParId(SalleCenima *salles,unsigned int taille, unsigned int salleId);
int estSallExiste(SalleCenima * tab,int nb,int salleId);

// ----------------------------------supprission salle cenima -----------------------------------

void supprimerProjectionsDansSalleCenima(SalleCenima *salles, unsigned int *nb_salles, unsigned int projectionId);

// ----------------AffichageSalleCenima-------------------------------

void AfficherSalleCinema(SalleCenima s);

// --------------------------afficher Tout Les Salle------------------------

void AfficherToutesLesSalles(SalleCenima *tab, int nb);

void AfficherToutesLesSallesWithDetails(SalleCenima *tab, int nb);

void AfficherSalleCinemaWithDetails(SalleCenima s);

//--------------------------- File-------------------------------------

void remplirSalleCenimaFromFile();
void enregistrerSallesCinemaToFile(const SalleCenima *salles, int nb_salles);

#endif //SALLECENIMA_H