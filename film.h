#ifndef FILM_H
#define FILM_H
#include "date.h"
#include "projection.h"

struct film
{
  unsigned int filmId;
  unsigned int dureeFilm;
  char *realisateur;
  Date dateSortie;
  char *titreFilm;
  char *genre;
  char *discriptionFilm;
  char *studio;
  Projection *projection;
  unsigned int nombreProjection;
};
typedef struct film Film;

static unsigned int CF = 0;

extern Film *films;

extern unsigned int nb_films;
// ----------------InitialiserFilm-------------------------------

void afficherFilm(Film f);

// -------------------------Ajout-------------------------------------------

// ----------------AjouterProjectionPourFilm-------------------------------

void ajouterProjectionPourFilm(Film *film, Projection projection);

void ajouterProjectionPourFilmParId(Projection p,unsigned int idFilm);
// ---------------------------AjouterFilmDansLatableDesFilms--------------------------

void ajouterFilmDansLaTableDesFilms(Film *tabFilms, int * tailleTabFilms, Film film);

// -----------------------Recherche-------------------------------

Film *chercherFilmParId(Film *films, unsigned int numFilms, unsigned int filmId);
Film *chercherFilmParTitle(Film *films, unsigned int numFilms, char *title);
int estFilmExist(Film *f, int nb, int id);

// ------------------------------suppression des films ----------------------------

void supprimerProjectionsDansFilm(Film *films, unsigned int *nb_films, unsigned int projectionId);
// ----------------AffichageFilm-------------------------------

void afficherFilm(Film f);
void afficherFilmWithDetails(Film f);
void afficherTousLesFilmsWithDetails(Film *tabFilms, int nb);
void afficherTousLesFilms(Film *tabFilms, int nb);

// --------------------------File-------------------------------------

void remplirFilmFromFile();
void enregistrerFilmsToFile(const Film *films, int nb_films);

#endif // FILM_H
