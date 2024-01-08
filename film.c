#include "film.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

Film *films = NULL;

unsigned int nb_films = 0;

#define MAX_STRING_LENGTH 100

// ----------------InitialiserFilm-------------------------------

void saisieFilm(Film *f)
{
    f->filmId = ++CF;
    f->realisateur = malloc(sizeof(char) * MAX_STRING_LENGTH);
    f->titreFilm = malloc(sizeof(char) * MAX_STRING_LENGTH);
    f->discriptionFilm = malloc(sizeof(char) * MAX_STRING_LENGTH);
    f->genre = malloc(sizeof(char) * MAX_STRING_LENGTH);
    f->studio = malloc(sizeof(char) * MAX_STRING_LENGTH);
    printf("Veuillez saisir le titre du film : ");
    scanf("%s", f->titreFilm);
    getchar();
    printf("Veuillez saisir le realisateur du film : ");
    scanf("%s", f->realisateur);
    getchar();
    printf("Veuillez saisir la duree du film : ");
    scanf("%d", &f->dureeFilm);
    getchar();
    printf("Veuillez saisir le discription du film : ");
    scanf("%s", f->discriptionFilm);
    getchar();
    printf("Veuillez saisir le genre du film : ");
    scanf("%s", f->genre);
    getchar();
    printf("Veuillez saisir la date de sortie du film : ");
    saisieDateFilm(&f->dateSortie);

    f->projection = NULL;
    f->nombreProjection = 0;

    printf("\n|-------Le film a ete ajoute avec succes!------------|\n");
}
// -------------------------Ajout-------------------------------------------
// ----------------AjouterProjectionPourFilm-------------------------------

void ajouterProjectionPourFilm(Film *film, Projection projection)
{
    film->projection = (Projection *)realloc(film->projection, (film->nombreProjection + 1) * sizeof(Projection));
    film->nombreProjection++;
    film->projection[film->nombreProjection - 1] = projection;
}

void ajouterProjectionPourFilmParId(Projection p, unsigned int idFilm)
{
    int i;
    for (i = 0; i < nb_films; i++)
    {
        if (films[i].filmId == idFilm)
        {
            ajouterProjectionPourFilm(&films[i], p);
            return;
        }
    }
}

// ---------------------------ajouterFilmDansLatableDesFilms--------------------------
void ajouterFilmDansLaTableDesFilms(Film *tabFilms, int *tailleTabFilms, Film film)
{
    tabFilms[(*tailleTabFilms)++] = film;
}

// ----------------Recherche-------------------------------

Film *chercherFilmParId(Film *films, unsigned int numFilms, unsigned int filmId)
{
    int i;
    for (i = 0; i < numFilms; i++)
    {
        if (films[i].filmId == filmId)
        {
            return (Film *)&films[i];
        }
    }
    return NULL; // Film non existe
}

Film *chercherFilmParTitle(Film *films, unsigned int numFilms, char *title)
{
    int i;
    for (i = 0; i < numFilms; ++i)
    {
        if (strcmp(films[i].titreFilm, title) == 0)
        {
            return (Film *)&films[i];
        }
    }
    return NULL; // Film non existe
}

int estFilmExist(Film *f, int nb, int id)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        if (f[i].filmId == id)
            return 1;
    }
    return 0;
}

Date getDateFilm(Film *f, int nb, int id){
    int i;
    for (i = 0; i < nb; i++)
    {
        if (f[i].filmId == id)
            return f[i].dateSortie;
    }
}
// -------------------------------supprision du films--------------------------------------

void supprimerProjectionsDansFilm(Film *films, unsigned int *nb_films, unsigned int projectionId)
{
    int i, j;
    for (i = 0; i < *nb_films; ++i)
    {
        for (j = 0; j < films[i].nombreProjection; ++j)
        {
            if (films[i].projection[j].projectionId == projectionId)
            {
                // Supprimer la référence à la projection dans le film
                for (; j < films[i].nombreProjection - 1; ++j)
                {
                    films[i].projection[j] = films[i].projection[j + 1];
                }

                // Mettre à jour le nombre de projections dans le film
                --(films[i].nombreProjection);

                // Réallouer la mémoire pour les projections dans le film
                films[i].projection = realloc(films[i].projection, (films[i].nombreProjection) * sizeof(Projection));
                break;
            }
        }
    }
}
// ----------------AffichageFilm-------------------------------

void afficherFilm(Film f)
{
    printf("\nl'id du film : %d \n", f.filmId);
    printf("Titre du film : %s\n", f.titreFilm);
    printf("Realisateur : %s\n", f.realisateur);
    printf("Annee de sortie : ");
    afficheDate(f.dateSortie);
    printf("genre : %s\n", f.genre);
    printf("discription du film : %s\n", f.discriptionFilm);
    // printf("Studio : %s\n", f.studio);
    printf("Nombre de projection : %d \n\n", f.nombreProjection);
}

void afficherFilmWithDetails(Film f)
{
    printf("\nl'id du film : %d \n", f.filmId);
    printf("Titre du film : %s\n", f.titreFilm);
    printf("Realisateur : %s\n", f.realisateur);
    printf("Annee de sortie : ");
    afficheDate(f.dateSortie);
    printf("genre : %s\n", f.genre);
    printf("discription du film : %s\n", f.discriptionFilm);
    printf("Studio : %s\n", f.studio);
    printf("Nombre de projection : %d \n\n", f.nombreProjection);
    if (f.projection != NULL)
    {
        int i;
        printf("\nListe des projections du film %s :\n\n", f.titreFilm);
        for (i = 0; i < f.nombreProjection; i++)
        {
            afficherProjectionWithDetails(f.projection[i]);
        }
        printf("\n\n");
    }
    else
    {
        printf("\nAucune projection dans cette salle.\n");
    }
}
// ------------------------aficher Tous Les film-------------------------
void afficherTousLesFilms(Film *tabFilms, int nb)
{
    int i;
    printf("|-----------------Films :\n\n\n");
    for (i = 0; i < nb; i++)
    {
        afficherFilm(tabFilms[i]);
    }
}

void afficherTousLesFilmsWithDetails(Film *tabFilms, int nb)
{
    int i;
    printf("|-----------------Films :\n\n\n");
    for (i = 0; i < nb; i++)
    {
        afficherFilmWithDetails(tabFilms[i]);
    }
}


// ---------------------------File---------------------------------

void remplirFilmFromFile()
{
    FILE *file = fopen("film.txt", "r");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier film.txt.\n");
        return;
    }
    fscanf(file, "%d\n", &CF);
    while (!feof(file))
    {
        Film *film = malloc(sizeof(Film));

        if (film == NULL)
        {
            printf("Erreur d'allocation mÃ©moire pour le film.\n");
            return;
        }
        film->realisateur = malloc(sizeof(char) * MAX_STRING_LENGTH);
        film->titreFilm = malloc(sizeof(char) * MAX_STRING_LENGTH);
        film->discriptionFilm = malloc(sizeof(char) * MAX_STRING_LENGTH);
        film->genre = malloc(sizeof(char) * MAX_STRING_LENGTH);
        film->studio = malloc(sizeof(char) * MAX_STRING_LENGTH);

        int result = fscanf(file, "%u # %u # %s # %d %d %d # %s # %s # %s # %s # %d\n", &film->filmId, &film->dureeFilm, film->realisateur, &film->dateSortie.j, &film->dateSortie.m, &film->dateSortie.a, film->titreFilm, film->genre, film->discriptionFilm, film->studio, &film->nombreProjection);

        if (result == 11)
        {
            // Initialize projection to NULL for each film
            film->projection = NULL;
            film->nombreProjection = 0;
            // Ajouter le film dans la table films
            films = (Film *)realloc(films, (++nb_films) * sizeof(Film));
            films[nb_films - 1] = *film;
        }
        else
        {
            printf("Erreur de lecture du donnee de fichier film : %d\n", result);
            free(film->discriptionFilm);
            free(film->genre);
            free(film->realisateur);
            free(film->titreFilm);
            free(film);
            return;
        }
    }
    fclose(file);
}


void enregistrerFilmsToFile(const Film *films, int nb_films)
{
    FILE *file = fopen("film.txt", "w");

    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier film.txt pour l'enregistrement.\n");
        return;
    }
    fprintf(file,"%u\n",CF);
    for (int i = 0; i < nb_films; ++i)
    {
        fprintf(file, "%u # %u # %s # %d %d %d # %s # %s # %s # %s # %d\n",
                films[i].filmId, films[i].dureeFilm, films[i].realisateur,
                films[i].dateSortie.j, films[i].dateSortie.m, films[i].dateSortie.a,
                films[i].titreFilm, films[i].genre, films[i].discriptionFilm,
                films[i].studio, films[i].nombreProjection);
    }

    fclose(file);
}