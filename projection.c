#include "projection.h"
#include "heure.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

Projection *projections = NULL;
int nb_projections = 0;

// ----------------CreeProjection-------------------------------

void creeProjection(Projection *p, unsigned int f, unsigned int S)
{
    p->projectionId = ++CP;
    printf("saisir la date du projection");
    saisieDate(&p->dateProjection);
    printf("saisir l'heure du debut de projection");
    saisieHeure(&p->heureDebut);
    printf("saisir l'heure du fin de projection");
    saisieHeure(&p->heureFin);
    printf("Saisie le prix dun billet de projection : ");
    scanf("%d", &p->prixBillet);
    getchar();
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
    printf("Nombre de places reservees: %u\n", p.nbReservation);
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
        printf("\nAucune projection dans cette salle.\n\n");
    }
}

// -------------------------------suppression d'une projection----------------------------------

void supprimerProjectionsDansUneSalle(Projection *projection,int *nb,unsigned int salleId){
    int i,j;
    for(i=0 ; i<*nb ; i++){
        if(projection[i].salleId == salleId){
            // supprimer projection
            for(j = i; j < *nb - 1 ; j++){
                projection[j]=projection[j+1];
            }
            (*nb)--;
            i--;
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
            projection->reservations = NULL;
            projection->nbReservation = 0;
            // Ajouter la projection dans la table projections
            projections = (Projection *)realloc(projections, (++nb_projections) * sizeof(Projection));
            projections[nb_projections - 1] = *projection;
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