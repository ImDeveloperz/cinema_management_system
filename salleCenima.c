#include "salleCenima.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SalleCenima *salles = NULL;

int nb_salles = 0;

#define MAX_STRING_LENGTH 100

// ----------------InitialiserSalle-------------------------------

void saisieSalleCenima(SalleCenima *S)
{
    S->salleId = ++CSC;
    S->nomSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);
    S->equipementSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);
    S->emplacementSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);
    printf("Entrer le nom de la salle : ");
    scanf("%s", S->nomSalle);
    getchar();

    printf("Entrer l'equipement de la salle : ");
    scanf("%s", S->equipementSalle);
    getchar();

    printf("Entrer l'emplacement de la salle : ");
    scanf("%s", S->emplacementSalle);
    getchar();

    printf("\nNombre de places (capacite du salle) ?  \n");
    scanf("%d", &S->capaciteSalle);
    getchar();

    S->projection = NULL;
    S->nombreProjection = 0;
}

// -----------------------getteur----------------------------

int getCapaciterSalleFromSalleParId(int idSalle)
{
    int i;
    for (i = 0; i < nb_salles; i++)
    {
        if (salles[i].salleId == idSalle)
            return salles[i].capaciteSalle;
    }
    return 0;
}
// ----------------------------Ajouter---------------------------------------------

// -----------------------AjouterProjectionPourSalle-------------------------------

void ajouterProjectionPourSalle(SalleCenima *salle, Projection nouvelleProjection)
{
    //  realloc
    salle->projection = (Projection *)realloc(salle->projection, (salle->nombreProjection + 1) * sizeof(Projection));
    salle->nombreProjection++;
    salle->projection[salle->nombreProjection - 1] = nouvelleProjection;
}

void ajouterProjectionPourSalleParId(Projection p, unsigned int idSalle)
{
    int i;
    for (i = 0; i < nb_salles; i++)
    {
        if (salles[i].salleId == idSalle)
        {
            ajouterProjectionPourSalle(&salles[i], p);
            return;
        }
    }
}
// -------------------------------ajoutSalleDansLaListeDeSalles------------------------

void ajoutSalleDansLaListeDeSalles(SalleCenima **tabSalles, int *nombreSalle, SalleCenima sc)
{
    // Augmenter la taille du tableau
    *tabSalles = realloc(*tabSalles, (*nombreSalle + 1) * sizeof(SalleCenima));

    if (*tabSalles == NULL)
    {
        printf("Erreur d'allocation mémoire pour ajouter la salle.\n");
        return;
    }

    // Ajouter la salle à la liste
    (*tabSalles)[*nombreSalle] = sc;

    // Incrémenter le nombre de salles
    (*nombreSalle)++;
}

// ------------------------Recherche-------------------------------

SalleCenima *rechercheSalleParNom(SalleCenima *salles, unsigned int taille, char *salleNom)
{
    int i = 0;
    for (i = 0; i < taille; i++)
    {
        if ((strcmp(salleNom, salles[i].nomSalle)) == 0)
            return &salles[i];
    }
    return NULL; // si on ne trouve pas la salle
}

SalleCenima *rechercheSalleParId(SalleCenima *salles, unsigned int taille, unsigned int salleId)
{
    int i = 0;
    for (i = 0; i < taille; i++)
    {
        if (salles[i].salleId == salleId)
            return &salles[i];
    }
    return NULL; // si on ne trouve pas la salle
}

int estSallExiste(SalleCenima *tab, int nb, int salleId)
{
    if (nb == 0)
        return 0;
    int i;
    for (i = 0; i <= nb; i++)
    {
        if (tab[i].salleId == salleId)
        {
            return 1;
        }
    }
    return 0;
}

// ----------------AffichageSalleCenima-------------------------------

void AfficherSalleCinema(SalleCenima s)
{
    printf("\nID de la salle : %d ", s.salleId);
    printf("\nNom de la salle : %s", s.nomSalle);
    printf("\nEquipement de la salle : %s", s.equipementSalle);
    printf("\nEmplacement de la salle : %s", s.emplacementSalle);
    printf("\nCapacite de la salle : %d", s.capaciteSalle);
    printf("\nNombre Projection de cette salle : %d\n\n", s.nombreProjection);
}

void AfficherSalleCinemaWithDetails(SalleCenima s)
{
    printf("\nID de la salle : %d ", s.salleId);
    printf("\nNom de la salle : %s", s.nomSalle);
    printf("\nEquipement de la salle : %s", s.equipementSalle);
    printf("\nEmplacement de la salle : %s", s.emplacementSalle);
    printf("\nCapacite de la salle : %d\n\n", s.capaciteSalle);
    if (s.projection != NULL)
    {
        printf("\n|===========Liste des projections du salle %s :\n", s.nomSalle);
        for (int i = 0; i < s.nombreProjection; i++)
        {
            afficherProjectionWithDetails(s.projection[i]);
        }
    }
    else
    {
        printf("\nAucune projection dans cette salle.\n");
    }
}

// ----------------------------------supprission salle cenima -----------------------------------

void supprimerSalle(SalleCenima *salles, unsigned int *nb_salles, unsigned int salleId)
{
    // // Supprimer toutes les projections dans la salle et les réservations associées
    // supprimerProjectionsDansSalle(projections, nb_projections, salleId, reservations, nb_reservations);

    // // Supprimer toutes les projections liées à la salle dans les films
    // supprimerProjectionsLieesASallePourTousLesFilms(projections, nb_projections, salleId);

    int i;
    for (i = 0; i < *nb_salles; ++i)
    {
        if (salles[i].salleId == salleId)
        {
            for (; i < *nb_salles - 1; ++i)
            {
                salles[i] = salles[i + 1];
            }
            // Mettre à jour le nombre de salles
            --(*nb_salles);
            // Réallouer la mémoire pour les salles
            salles = realloc(salles, (*nb_salles) * sizeof(SalleCenima));
            break; // Sortir de la boucle car la salle est supprimée
        }
    }
}

void supprimerProjectionsDansSalleCenima(SalleCenima *salles, unsigned int *nb_salles, unsigned int projectionId)
{
    int i, j;
    for (i = 0; i < *nb_salles; ++i)
    {
        for (j = 0; j < salles[i].nombreProjection; ++j)
        {
            if (salles[i].projection[j].projectionId == projectionId)
            {
                // Supprimer la référence à la projection dans la salleCenima
                for (; j < salles[i].nombreProjection - 1; ++j)
                {
                    salles[i].projection[j] = salles[i].projection[j + 1];
                }

                // Mettre à jour le nombre de projections dans la salleCenima
                --(salles[i].nombreProjection);

                // Réallouer la mémoire pour les projections dans la salleCenima
                salles[i].projection = realloc(salles[i].projection, (salles[i].nombreProjection) * sizeof(Projection));
            }
        }
    }
}

// --------------------------afficher Tout Les Salle------------------------

void AfficherToutesLesSalles(SalleCenima *tab, int nb)
{
    int i;
    printf("|-----------------Salles :\n");
    for (i = 0; i < nb; i++)
    {
        AfficherSalleCinema(tab[i]);
    }
}

void AfficherToutesLesSallesWithDetails(SalleCenima *tab, int nb)
{
    int i;
    printf("|-----------------Salles :\n");
    for (i = 0; i < nb; i++)
    {
        AfficherSalleCinemaWithDetails(tab[i]);
    }
}

//--------------------------- File-------------------------------------

void remplirSalleCenimaFromFile()
{
    FILE *file = fopen("salleCenima.txt", "r");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier salleCenima.txt.\n");
        return;
    }
    fscanf(file, "%u\n", &CSC);
    while (!feof(file))
    {
        SalleCenima *salle = malloc(sizeof(SalleCenima));

        if (salle == NULL)
        {
            printf("Erreur d'allocation mÃ©moire pour la salleCenima.\n");
            return;
        }
        salle->nomSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);
        salle->equipementSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);
        salle->emplacementSalle = malloc(sizeof(char) * MAX_STRING_LENGTH);

        int result = fscanf(file, "%u # %s # %s # %s # %u # %u  \n", &salle->salleId, salle->nomSalle, salle->equipementSalle, salle->emplacementSalle, &salle->capaciteSalle, &salle->nombreProjection);

        if (result == 6)
        {
            // Initialize projection to NULL for each salle
            salle->projection = NULL;
            salle->nombreProjection = 0;
            // Ajouter la salle dans la table salleCenimas
            salles = (SalleCenima *)realloc(salles, (++nb_salles) * sizeof(SalleCenima));
            salles[nb_salles - 1] = *salle;
        }
        else
        {
            free(salle->equipementSalle);
            free(salle->nomSalle);
            free(salle->emplacementSalle);
            free(salle);
            return;
        }
    }
    fclose(file);
}

void enregistrerSallesCinemaToFile(const SalleCenima *salles, int nb_salles)
{
    FILE *file = fopen("salleCenima.txt", "w");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier salleCenima.txt pour l'enregistrement.\n");
        return;
    }
    fprintf(file, "%u\n", CSC);
    for (int i = 0; i < nb_salles; ++i)
    {
        fprintf(file, "%u # %s # %s # %s # %u # %u\n",
                salles[i].salleId, salles[i].nomSalle, salles[i].equipementSalle,
                salles[i].emplacementSalle, salles[i].capaciteSalle, salles[i].nombreProjection);
    }

    fclose(file);
}