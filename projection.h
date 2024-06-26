#ifndef PROJECTION_H
#define PROJECTION_H
#include "date.h"
#include "heure.h"
#include "reservation.h"
struct projection
{
    unsigned int projectionId;
    Date dateProjection;
    Heure heureDebut;
    Heure heureFin;
    unsigned int prixBillet; // En dh
    unsigned int nbPlacesDisponible;
    unsigned int filmId;
    unsigned int salleId;
    Reservation *reservations;
    unsigned int nbReservation;
};
typedef struct projection Projection;

extern Projection *projections;
extern int nb_projections;

static unsigned int CP = 0;

// ----------------CreeProjection-------------------------------

void creeProjection(Projection *p, unsigned int f, unsigned int S,Date d);

// ----------------AjouterReservationPourProjection-------------------------------

void ajouterReservationPourProjection(Projection *projection, Reservation reservation);

// ajouter Projection Dans tous Les Projection

void ajoutDansTousLesProjections(Projection projec);

void setStatuePayementInProjection(Projection *p, unsigned int nbP, unsigned int idReservation);
// ----------------Recherche-------------------------------

// Projection* rechercheProjectionParNom(Projection *projections,unsigned int numProjections, char *nomSalle);
Projection *rechercheProjectionParId(Projection *projections, unsigned int numProjections, unsigned int projectionId);

// ---------------------------suppresion d'une projection---------------------------

void supprimerProjectionsDansUneSalle(Projection *projection, int *nb, unsigned int salleId);
void supprimerProjection(Projection *projections, unsigned int *nb_projections, unsigned int projectionId);
void supprimerReservationFromProjection(Projection *p, int *nb_projections, unsigned int reservationId);
void supprimerReservationFromProjectionNonpayer(Projection *p, int nb_projections);
// ----------------AffichageProjection-------------------------------

void afficherProjection(Projection p);
void afficherProjectionWithDetails(Projection p);

// ---------------------afficher Tout les projection ------------------------

void afficherToutLesProjections(Projection *p, int nb);
void afficherToutLesProjectionsWithDetails(Projection *p, int nb);

// -------------------------File--------------------------------

void remplirProjectionFromFile();

void enregistrerProjectionsToFile(const Projection *projections, int nb_projections);

#endif // SALLECENIMA_H
