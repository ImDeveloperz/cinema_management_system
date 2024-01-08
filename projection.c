#include "projection.h"
#include "heure.h"
#include "date.h"
#include "salleCenima.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Projection *projections = NULL;
int nb_projections = 0;

// ----------------CreeProjection-------------------------------

void creeProjection(Projection *p, unsigned int f, unsigned int S, Date d)
{
    p->projectionId = ++CP;
    printf("saisir la date du projection");
    saisieDateProjection(&p->dateProjection, d);
    printf("saisir l'heure du debut de projection");
    saisieHeureDebut(&p->heureDebut);
    printf("saisir l'heure du fin de projection");
    saisieHeureFin(&p->heureFin, p->heureDebut);
    printf("Saisie le prix dun billet de projection : ");
    scanf("%d", &p->prixBillet);
    getchar();
    // recherhe a la salle par idSalle
    p->nbPlacesDisponible = getCapaciterSalleFromSalleParId(S);
    //    p->nbPlacesDisponible = S.capaciteSalle;
    p->filmId = f;
    p->salleId = S;
    p->nbReservation = 0;
    p->reservations = NULL;
}

// ----------------AjouterReservationPourProjection-------------------------------

void ajouterReservationPourProjection(Projection *projection, Reservation reservation)
{
    projection->reservations = (Reservation *)realloc(projection->reservations, (projection->nbReservation + 1) * sizeof(Reservation));
    projection->nbReservation++;
    projection->reservations[projection->nbReservation - 1] = reservation;
}

// ajouter Projection Dans tous Les Projection
void ajoutDansTousLesProjections(Projection projec)
{
    if (projections == NULL)
    {
        projections = malloc(sizeof(Projection));
        nb_projections = 1;
        *(projections + nb_projections - 1) = projec;
    }
    else
    {
        projections = realloc(projections, sizeof(Projection) * (nb_projections + 1));
        *(projections + nb_projections) = projec;
        nb_projections++;
    }
}

void setStatuePayementInProjection(Projection *p, unsigned int nbP, unsigned int idReservation)
{
    int i, j;
    for (i = 0; i < nbP; i++)
    {
        for (j = 0; j < p[i].nbReservation; j++)
        {
            if (idReservation == p[i].reservations[j].reservationId)
            {
                p[i].reservations[j].statuePaiment = "paye";
                break;
            }
        }
    }
}
// ----------------Recherche-------------------------------

Projection *rechercheProjectionParId(Projection *projections, unsigned int numProjections, unsigned int projectionId)
{
    int i;
    for (i = 0; i < numProjections; ++i)
    {
        if (projections[i].projectionId == projectionId)
        {
            return (Projection *)&projections[i];
        }
    }
    return NULL; // Projection  non existe
}

// Projection* rechercheProjectionParDate( Projection *projections,unsigned int numProjections,char *nomSalle) {
//     int i;
//     for (i = 0; i < numProjections; ++i) {
//         if (projections[i].projectionId == projectionId) {
//             return (Projection*)&projections[i];
//         }
//     }
//     return NULL; // Projection non existe
// }

// ----------------AffichageProjection-------------------------------

void afficherProjection(Projection p)
{
    printf("\nl'id du projection : %u \n ", p.projectionId);
    printf("la date du projection est : ");
    afficheDate(p.dateProjection);
    printf("l'heure de debut : ");
    afficheHeure(p.heureDebut);
    printf("l'heure du Fin : ");
    afficheHeure(p.heureFin);
    printf("l'id du Film : %u \n", p.filmId);
    printf("le Prix du Billet de Projection : %u \n ", p.prixBillet);
    printf("Nombre de place disponible : %u \n ", p.nbPlacesDisponible);
    printf("l'id du salle: %d \n", p.salleId);
    printf("Film id : %u", p.filmId);
    printf("\n\n");
}

void afficherProjectionWithDetails(Projection p)
{
    printf("\nl'id du projection : %u \n ", p.projectionId);
    printf("la date du projection est : ");
    afficheDate(p.dateProjection);
    printf("l'heure de debut : ");
    afficheHeure(p.heureDebut);
    printf("l'heure du Fin : ");
    afficheHeure(p.heureFin);
    printf("l'id du Film : %u \n", p.filmId);
    printf("le Prix du Billet de Projection : %u \n ", p.prixBillet);
    printf("Nombre de place disponible : %u \n ", p.nbPlacesDisponible);
    printf("Nombre de places reservees: %u\n", p.nbReservation);
    printf("l'id du salle: %d \n", p.salleId);
    printf("Film id : %u", p.filmId);
    printf("\n\n");
    if (p.reservations != NULL)
    {
        printf("\nListe des reservation du Projection %d :\n\n", p.projectionId);
        int i;
        for (i = 0; i < p.nbReservation; i++)
        {
            afficherReservation(p.reservations[i]);
        }
        printf("\n\n");
    }
    else
    {
        printf("\n|=============Aucune reservation trouvé \n\n");
    }
}

// -------------------------------suppression d'une projection----------------------------------

void supprimerProjectionsDansUneSalle(Projection *projection, int *nb, unsigned int salleId)
{
    int i, j;
    for (i = 0; i < *nb; i++)
    {
        if (projection[i].salleId == salleId)
        {
            // supprimer projection
            for (j = i; j < *nb - 1; j++)
            {
                projection[j] = projection[j + 1];
            }
            (*nb)--;
            i--;
        }
    }
}
void supprimerReservationFromProjection(Projection *p, int *nb_projections, unsigned int reservationId)
{
    int i, j, k;
    for (i = 0; i < *nb_projections; i++)
    {
        for (j = 0; j < p[i].nbReservation; j++)
        {
            if (p[i].reservations[j].reservationId == reservationId)
            {
                for (k = j; k < p[i].nbReservation - 1; k++)
                {
                    p[i].reservations[k] = p[i].reservations[k + 1];
                }
                p[i].nbReservation--;
                break;
            }
        }
    }
}
void supprimerProjection(Projection *projections, unsigned int *nb_projections, unsigned int projectionId)
{
    int i;
    for (i = 0; i < *nb_projections; ++i)
    {
        if (projections[i].projectionId == projectionId)
        {
            // Libérer la mémoire des réservations liées à la projection
            free(projections[i].reservations);

            // Supprimer la projection
            for (; i < *nb_projections - 1; ++i)
            {
                projections[i] = projections[i + 1];
            }

            // Mettre à jour le nombre de projections
            --(*nb_projections);

            // Réallouer la mémoire pour les projections
            projections = realloc(projections, (*nb_projections) * sizeof(Projection));
            break;
        }
    }
}

void supprimerReservationFromProjectionNonpayer(Projection *p, int nb_projections)
{
    int i, j, k;
    for (i = 0; i < nb_projections; i++)
    {
        for (j = 0; j < p[i].nbReservation; j++)
        {
            if (strcmp(p[i].reservations[j].statuePaiment, "nonPayer") == 0)
            {
                p[i].nbPlacesDisponible += p[i].reservations[j].nombreBilletReserver;
                for (k = j; k < p[i].nbReservation - 1; k++)
                {
                    p[i].reservations[k] = p[i].reservations[k + 1];
                }
                p[i].nbReservation--;
            }
        }
    }
}
// ---------------------afficher Tout les projection ------------------------
void afficherToutLesProjections(Projection *p, int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        afficherProjection(p[i]);
    }
}

void afficherToutLesProjectionsWithDetails(Projection *p, int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        afficherProjectionWithDetails(p[i]);
    }
}

// -------------------------File--------------------------------

void remplirProjectionFromFile()
{
    FILE *file = fopen("projection.txt", "r");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier projection.txt.\n");
        return;
    }
    fscanf(file, "%d\n", &CP);
    while (!feof(file))
    {
        Projection *projection = malloc(sizeof(Projection));

        if (projection == NULL)
        {
            printf("Erreur d'allocation mémoire pour la projection.\n");
            return;
        }

        int result = fscanf(file, "%u # %d %d %d # %d %d %d # %d %d %d # %u # %u # %u # %u # %u \n",
                            &projection->projectionId,
                            &projection->dateProjection.j, &projection->dateProjection.m, &projection->dateProjection.a,
                            &projection->heureDebut.h, &projection->heureDebut.m, &projection->heureDebut.s, &projection->heureFin.h, &projection->heureFin.m, &projection->heureFin.s,
                            &projection->prixBillet, &projection->nbPlacesDisponible,
                            &projection->filmId, &projection->salleId, &projection->nbReservation);

        if (result == 15)
        {
            // Initialize reservations to NULL for each projection
            if (validateDateProjectionFile(projection->dateProjection) == 1)
            {
                projection->reservations = NULL;
                projection->nbReservation = 0;
                // Ajouter la projection dans la table projections
                projections = (Projection *)realloc(projections, (++nb_projections) * sizeof(Projection));
                projections[nb_projections - 1] = *projection;
            }
        }
        else
        {
            printf("Erreur de lecture du fichier projection.txt. %d\n", result);
            free(projection);
            return;
        }
    }

    fclose(file);
}

void enregistrerProjectionsToFile(const Projection *projections, int nb_projections)
{
    FILE *file = fopen("projection.txt", "w");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier projection.txt pour l'enregistrement.\n");
        return;
    }
    fprintf(file, "%u\n", CP);
    for (int i = 0; i < nb_projections; ++i)
    {
        fprintf(file, "%u # %d %d %d # %d %d %d # %d %d %d # %u # %u # %u # %u # %u\n",
                projections[i].projectionId,
                projections[i].dateProjection.j, projections[i].dateProjection.m, projections[i].dateProjection.a,
                projections[i].heureDebut.h, projections[i].heureDebut.m, projections[i].heureDebut.s,
                projections[i].heureFin.h, projections[i].heureFin.m, projections[i].heureFin.s,
                projections[i].prixBillet, projections[i].nbPlacesDisponible,
                projections[i].filmId, projections[i].salleId, projections[i].nbReservation);
    }

    fclose(file);
}
