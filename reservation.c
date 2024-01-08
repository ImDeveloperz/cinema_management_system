#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        reservations[nb_reservation] = reserv;
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

void setStatuePaiment(Reservation *reservations, unsigned int nb_reservations, unsigned int idReservation)
{
    int i;
    for (i = 0; i < nb_reservations; i++)
    {
        if (reservations[i].reservationId == idReservation)
        {
            reservations[i].statuePaiment = "paye";
            break;
        }
    }
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

void supprimerReserationFromReservations(Reservation *reservations, unsigned int *nb_reservations, unsigned int reservationId)
{
    int i, j;
    for (i = 0; i < *nb_reservations; i++)
    {
        if (reservations[i].reservationId == reservationId)
        {
            for (j = i; j < *nb_reservations - 1; j++)
            {
                reservations[j] = reservations[j + 1];
            }
            *nb_reservations--;
            printf("\n|=========================la reservation est annuler\n");
            break;
        }
    }
}

void supprimerReserationFromReservationsNonpayer(Reservation *reservations, unsigned int *nb_reservations){
    int i, j;
    for (i = 0; i < *nb_reservations; i++)
    {
        if (strcmp(reservations[i].statuePaiment,"nonPayer") == 0)
        {
            printf("\n|=========================la reservation %d est annuler\n",reservations[i].reservationId);
            for (j = i; j < *nb_reservations - 1; j++)
            {
                reservations[j] = reservations[j + 1];
            }
            *nb_reservations = *nb_reservations -1;
            i--;
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
    fscanf(file, "%d\n", &CR);
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
        else
        {
            printf("Erreur lors de la lecture des donnees du client.\n");
            free(reservation->statuePaiment);
            free(reservation);
            return;
        }
    }

    fclose(file);
}

void enregistrerReservationsToFile(const Reservation *reservations, int nb_reservations)
{
    FILE *file = fopen("reservation.txt", "w");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier reservation.txt pour l'enregistrement.\n");
        return;
    }
    fprintf(file, "%u\n", CR);
    for (int i = 0; i < nb_reservations; ++i)
    {  
            fprintf(file, "%u # %u # %d # %d # %s # %u\n",
                    reservations[i].reservationId, reservations[i].clientId,
                    reservations[i].nombreBilletReserver, reservations[i].montantTotal,
                    reservations[i].statuePaiment, reservations[i].projectionId);
    }
    fclose(file);
}
