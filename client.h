#ifndef CLIENT_H
#define CLIENT_H

#include "reservation.h"
struct client
{
  unsigned int clientId;
  char *nomClient;
  char *prenomClient;
  char *emailClient;
  char *numTelephone;
  char *Cin;
  Reservation *reservation;
  unsigned int nombreReservation;
};
typedef struct client Client;

static unsigned int CC = 0;

extern Client *clients;

extern int nb_clients;

// ----------------InitialiserClient-------------------------------

void saisirClient(Client *c);

// ----------------AjouterReservationPourClient-------------------------------

void ajouterReservationDansClient(Client *client, Reservation reservation);

void ajoutClientDansLaListeDeClient(Client *tabSalles, int *nombreClient, Client sc);

void setStatuePayementInClient(Client c,unsigned int idReservation);
// ----------------Recherche-------------------------------

Client *rechercheClientParNom(Client *clients, unsigned numClients, char *name);
Client *rechercheClientParId(Client *clients, unsigned int numClients, unsigned int clientId);
int rechercheClientParCin(Client *clients, unsigned numClients, char *cin);
// ---------------------------------suppression client ---------------------------------

void supprimerReservationsLieesAProjectionPourTousLesClients(Client *clients, unsigned int nb_clients, unsigned int projectionId);

void supprimerReservationFromClient(Client c,unsigned int reservationId);
// ----------------AffichageClient-------------------------------

void afficherClient(Client client);

void afficherReservationClient(Client c);
void afficherReservationClientNonPayer(Client c);
// --------------------------File-----------------------------------------

void remplirClientFromFile();
void enregistrerClientsToFile(const Client *clients, int nb_clients);
#endif
