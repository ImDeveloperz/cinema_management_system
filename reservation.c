#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>
// ----------------CreeReservation-------------------------------
Reservation *reservations = NULL;
int nb_reservation = 0;
#define MAX_STRING_LENGTH 100

void creeReservation(Reservation *r, unsigned int c, unsigned int p)
{
    r->reservationId = ++CR;
    printf("saisir le nombre de Billet reserver : ");
    scanf("%d", &r->nombreBilletReserver);
    r->clientId = c;
    r->projectionId = p;
    r->montantTotal = 0;
    r->statuePaiment = "nonPayer";
    getchar();
}


void ajoutDansToutesLesReservations(Reservation reserv)
{
    if (reservations == NULL)
    {
        reservations = malloc(sizeof(Reservation));
        reservations[nb_reservation]=reserv;
        nb_reservation = 1;
    }
    else
    {
        reservations = realloc(reservations, sizeof(Reservation) * (nb_reservation + 1));
        reservations[nb_reservation] = reserv;
        nb_reservation++;
    }
}

// -------------------------------------Recherche-------------------------------

Reservation *rechercherReservationParID(Reservation *tableauReservations, unsigned int taille, unsigned int idRecherche)
{
    int i;
    for (i = 0; i < taille; i++)
    {
        if (tableauReservations[i].reservationId == idRecherche)
        {
            return &tableauReservations[i];
        }
    }
    return NULL;
}

// --------------------------------AffichageReservation-------------------------------

void afficherReservation(Reservation r)
{
    printf("\n Reservation : \n");
    printf("ID de la reservation : %d\n", r.reservationId);
    printf("Nombre de billets reserver : %d\n", r.nombreBilletReserver);
    printf("Montant total : %d\n", r.montantTotal);
    printf("Statut du paiement : %s\n", r.statuePaiment);
    printf("Id de Projection %d\n", r.projectionId);
}

// ---------------------------------suppresion des reservation--------------------------------------

void supprimerProjectionsDansReservation(Reservation *reservations, unsigned int *nb_reservations, unsigned int projectionId)
{
    int i;
    for (i = 0; i < *nb_reservations; ++i)
    {
        if (reservations[i].projectionId == projectionId)
        {
            // Supprimer la référence à la projection dans la réservation
            reservations[i].projectionId = 0;
        }
    }
}
// ----------------------------------File----------------------------------

void remplirReservationFromFile()
{
    FILE *file = fopen("reservation.txt", "r");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier reservation.txt.\n");
        return;
    }
    fscanf(file,"%d\n",&CR);
    while (!feof(file))
    {
        Reservation *reservation = malloc(sizeof(Reservation));

        if (reservation == NULL)
        {
            printf("Erreur d'allocation memoire pour la reservation.\n");
            return;
        }
        reservation->statuePaiment = malloc(sizeof(char) * MAX_STRING_LENGTH);
        int result = fscanf(file, "%u # %u # %d # %d # %s # %u\n", &reservation->reservationId, &reservation->clientId, &reservation->nombreBilletReserver, &reservation->montantTotal, reservation->statuePaiment, &reservation->projectionId);
        if (result == 6)
        {
            // Ajouter la reservation dans la table reservations
            reservations = (Reservation *)realloc(reservations, (++nb_reservation) * sizeof(Reservation));
            reservations[nb_reservation - 1] = *reservation;
        }
        else{
            printf("Erreur lors de la lecture des donnees du client.\n");
            free(reservation->statuePaiment);
            free(reservation);
            return;
        }
    }

    fclose(file);
}
