#ifndef RESERVATION_H
#define RESERVATION_H
struct reservation
{
  unsigned int reservationId;
  unsigned int clientId;
  unsigned int nombreBilletReserver;
  unsigned int montantTotal;
  char *statuePaiment;
  unsigned int projectionId;
};
typedef struct reservation Reservation ; 

static unsigned int CR = 0;

// Reservation *reservations ;

// int nb_reservation = 0;
extern Reservation *reservations;
extern int nb_reservation;

// ----------------CreeReservation-------------------------------
void creeReservation(Reservation *r,unsigned int c,unsigned int p);

// ----------------Recherche-------------------------------

Reservation* rechercherReservationParID(Reservation * tableauReservations,unsigned int taille,unsigned int idRecherche);

// ----------------AffichageReservation-------------------------------

void afficherReservation(Reservation r);
void setStatuePaiment(Reservation *reservations,unsigned int nb_reservations,unsigned int idReservation);
void ajoutDansToutesLesReservations(Reservation reserv);
// -------------------------suppression-----------------------------------------
void supprimerProjectionsDansReservation(Reservation *reservations, unsigned int *nb_reservations, unsigned int projectionId);
void supprimerReserationFromReservations(Reservation *reservations, unsigned int *nb_reservations,unsigned int reservationId);
// ----------------File--------------------------------------
void enregistrerReservationsToFile(const Reservation *reservations, int nb_reservations);
void remplirReservationFromFile();

#endif // RESERVATION_H