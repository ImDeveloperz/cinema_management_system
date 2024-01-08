#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Client *clients = NULL;
int nb_clients = 0;
#define MAX_STRING_LENGTH 100

void saisirClient(Client *clt)
{
    if (clt != NULL)
    {
        clt->clientId = ++CC;
        clt->nomClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        clt->emailClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        clt->prenomClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        clt->numTelephone = malloc(sizeof(char) * MAX_STRING_LENGTH);
        clt->Cin = malloc(sizeof(char) * MAX_STRING_LENGTH);

        printf("\n=> Saisir le nom du client : ");
        scanf("%s", clt->nomClient);
        getchar();

        printf("\n=> Saisir le prenom du client : ");
        scanf("%s", clt->prenomClient);
        getchar();

        printf("\n=> Saisir l'email du client : ");
        scanf("%s", clt->emailClient);
        getchar();

        printf("\n=> Saisir le numero du telephone de client : ");
        scanf("%s", clt->numTelephone);
        getchar();

        printf("\n=> Saisir le Cin du client :");
        scanf("%s", clt->Cin);
        getchar();

        clt->nombreReservation = 0;
        clt->reservation = NULL;
    }
}

void ajoutClientDansLaListeDeClient(Client *tabSalles, int *nombreClient, Client sc)
{
    tabSalles[(*nombreClient)++] = sc;
}

// ----------------AjouterReservation-------------------------------

void ajouterReservationDansClient(Client *client, Reservation reservation)
{
    client->reservation = (Reservation *)realloc(client->reservation, (client->nombreReservation + 1) * sizeof(Reservation));
    client->nombreReservation++;
    client->reservation[client->nombreReservation - 1] = reservation;
}

// ---------------------------------suppression client ---------------------------------
void supprimerReservationsLieesAProjectionPourTousLesClients(Client *clients, unsigned int nb_clients, unsigned int projectionId)
{
    int i, j;
    for (i = 0; i < nb_clients; ++i)
    {
        for (j = 0; j < clients[i].nombreReservation; ++j)
        {
            if (clients[i].reservation[j].projectionId == projectionId)
            {
                // Supprimer la réservation en déplaçant les éléments suivants
                for (; j < clients[i].nombreReservation - 1; ++j)
                {
                    clients[i].reservation[j] = clients[i].reservation[j + 1];
                }

                // Mettre à jour le nombre de réservations pour le client
                --(clients[i].nombreReservation);

                // Réallouer la mémoire pour les réservations du client
                clients[i].reservation = realloc(clients[i].reservation, (clients[i].nombreReservation) * sizeof(Reservation));
                --j; // Pour vérifier la nouvelle réservation à la même position
            }
        }
    }
}

void supprimerReservationFromClient(Client *c, unsigned int reservationId)
{
    int i, j;
    for (i = 0; i < c->nombreReservation; i++)
    {
        if (c->reservation[i].reservationId == reservationId)
        {
            for (j = i; j < c->nombreReservation - 1; j++)
            {
                c->reservation[j] = c->reservation[j + 1];
            }
            --(c->nombreReservation);
            break;
        }
    }
}

void supprimerReservationFromClientNonpayer(Client *c){
    int i, j;
    for (i = 0; i < c->nombreReservation; i++)
    {
        if (strcmp(c->reservation[i].statuePaiment,"nonPayer") == 0)
        {
            for (j = i; j < c->nombreReservation - 1; j++)
            {
                c->reservation[j] = c->reservation[j + 1];
            }
            --(c->nombreReservation);
        }
    }
}
void setStatuePayementInClient(Client c,unsigned int idReservation){
    int i;
    for(i = 0; i < c.nombreReservation; i++){
        if(c.reservation[i].reservationId == idReservation){
            c.reservation[i].statuePaiment  = "paye";
            break;
        }
    }
}
// ----------------Recherche-------------------------------

Client *rechercheClientParNom(Client *clients, unsigned numClients, char *name)
{
    int i;
    for (i = 0; i < numClients; ++i)
    {
        if (strcmp(clients[i].nomClient, name) == 0)
        {
            return (Client *)&clients[i];
        }
    }
    return NULL; // Client non existe
}

int rechercheClientParCin(Client *clients, unsigned numClients, char *cin)
{
    int i;
    for (i = 0; i < numClients; ++i)
    {
        if (strcmp(clients[i].Cin, cin) == 0)
        {
            return i;
        }
    }
    return -1; // Client non existe
}

Client *rechercheClientParId(Client *clients, unsigned int numClients, unsigned int clientId)
{
    int i;
    for (i = 0; i < numClients; ++i)
    {
        if (clients[i].clientId == clientId)
        {
            return (Client *)&clients[i];
        }
    }
    return NULL; // Client non existe
}

// ----------------AffichageClient-------------------------------

void afficherClient(Client client)
{
    printf("ID du client : %d\n", client.clientId);
    printf("Nom du client : %s\n", client.nomClient);
    printf("Prenom du client : %s\n", client.prenomClient);
    printf("Email du client : %s\n", client.emailClient);
    printf("Numero de telephone du client : %s\n", client.numTelephone);
    printf("Nombre de reservation : %d\n", client.nombreReservation);
    printf("Le Cin du Client est : %s \n", client.Cin);
    printf("\n\n");
}

// afficher les projection d'un client
void afficherReservationClient(Client c)
{
    int i;
    for (i = 0; i < c.nombreReservation; i++)
    {
        afficherReservation(c.reservation[i]);
        printf("\n");
    }
}
void afficherListeDesClients(Client *clients, unsigned int nb)
{
    int i;
    printf("La liste des clients:\n");
    for (i = 0; i < nb; i++)
    {
        afficherClient(clients[i]);
    }
}

void afficherReservationClientNonPayer(Client c)
{
    int i;
    for (i = 0; i < c.nombreReservation; i++)
    {
        if (strcmp(c.reservation[i].statuePaiment,"nonPayer")==0)
        {
            afficherReservation(c.reservation[i]);
            printf("\n");
        }
    }
}
//--------------------------------File-----------------------------------------

void remplirClientFromFile()
{
    FILE *file1 = fopen("client.txt", "r");
    if (file1 == NULL)
    {
        printf("Impossible d'ouvrir le fichier client.txt ou reservation.txt.\n");
        return;
    }
    fscanf(file1, "%d\n", &CC);
    while (!feof(file1))
    {
        Client *c = malloc(sizeof(Client));
        if (c == NULL)
        {
            printf("Erreur d'allocation memoire pour le client.\n");
            return;
        }
        c->nomClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        c->prenomClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        c->emailClient = malloc(sizeof(char) * MAX_STRING_LENGTH);
        c->numTelephone = malloc(sizeof(char) * MAX_STRING_LENGTH);
        c->Cin = malloc(sizeof(char) * MAX_STRING_LENGTH);
        int result1 = fscanf(file1, "%u # %s # %s # %s # %s # %s \n", &c->clientId, c->nomClient, c->prenomClient, c->emailClient, c->numTelephone, c->Cin);
        // ajouter c dans la table clients
        if (result1 == 6)
        {
            c->reservation = NULL;
            c->nombreReservation = 0;
            clients = (Client *)realloc(clients, (++nb_clients) * sizeof(Client));
            clients[nb_clients - 1] = *c;
            // free(c); // Release memory if parsing fails
        }
        else
        {
            printf("Erreur lors de la lecture des donnees du client.\n");
            // Release memory if parsing fails
            free(c->nomClient);
            free(c->prenomClient);
            free(c->emailClient);
            free(c->numTelephone);
            free(c->Cin);
            free(c);
            return;
        }
    }
    fclose(file1);
}

void enregistrerClientsToFile(const Client *clients, int nb_clients)
{
    FILE *file = fopen("client.txt", "w");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier client.txt pour l'enregistrement.\n");
        return;
    }
    fprintf(file, "%u\n", CC);
    for (int i = 0; i < nb_clients; ++i)
    {
        fprintf(file, "%u # %s # %s # %s # %s # %s\n",
                clients[i].clientId, clients[i].nomClient, clients[i].prenomClient,
                clients[i].emailClient, clients[i].numTelephone, clients[i].Cin);
    }

    fclose(file);
}