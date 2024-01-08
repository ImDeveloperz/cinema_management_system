#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include "client.h"
#include "projection.h"
#include "film.h"
#include "salleCenima.h"

void remplirToutLesTableToFile()
{
    enregistrerClientsToFile(clients, nb_clients);
    enregistrerProjectionsToFile(projections, nb_projections);
    enregistrerReservationsToFile(reservations, nb_reservation);
    enregistrerFilmsToFile(films, nb_films);
    enregistrerSallesCinemaToFile(salles, nb_salles);
}

void remplirToutLesTableFromFile()
{
    int i;
    // initialiser la base de donnee
    printf("\nTelechargement des donnees...\n");
    remplirClientFromFile();
    remplirProjectionFromFile();
    remplirReservationFromFile();
    remplirFilmFromFile();
    remplirSalleCenimaFromFile();

    // metre les relations entre les tables
    // Entre Client et Reservation

    for (i = 0; i < nb_reservation; i++)
    {
        unsigned int clientId = reservations[i].clientId;

        // Recherche du client correspondant dans la table clients
        Client *client = rechercheClientParId(clients, nb_clients, clientId);

        if (client != NULL)
        {
            // Ajouter la reservation au client
            client->reservation = realloc(client->reservation, (++client->nombreReservation) * sizeof(Reservation));
            client->reservation[client->nombreReservation - 1] = reservations[i];
        }
    }

    // Entre Reservation et Projection

    for (i = 0; i < nb_reservation; ++i)
    {
        unsigned int projectionId = reservations[i].projectionId;

        // Recherche de la projection correspondante dans la table projections
        Projection *projection = rechercheProjectionParId(projections, nb_projections, projectionId);

        if (projection != NULL)
        {
            // Ajouter la rÃ©servation Ã  la projection
            projection->reservations = realloc(projection->reservations, (projection->nbReservation + 1) * sizeof(Reservation));
            projection->reservations[projection->nbReservation] = reservations[i];
            projection->nbReservation++;
        }
    }

    // Entre SalleCenima Et Projection

    for (i = 0; i < nb_projections; ++i)
    {
        unsigned int salleId = projections[i].salleId;
        // Recherche de la salle correspondante dans la table salleCenimas
        SalleCenima *salle = rechercheSalleParId(salles, nb_salles, salleId);
        if (salle != NULL)
        {
            // Ajouter la projection Ã  la salle
            salle->projection = realloc(salle->projection, (salle->nombreProjection + 1) * sizeof(Projection));
            salle->projection[salle->nombreProjection] = projections[i];
            salle->nombreProjection++;
        }
        // AfficherToutesLesSalles(salles,nb_salles);
    }

    // Entre Film Et Projection

    for (i = 0; i < nb_projections; ++i)
    {
        unsigned int filmId = projections[i].filmId;

        // Recherche du film correspondant dans la table films
        Film *film = chercherFilmParId(films, nb_films, filmId);

        if (film != NULL)
        {
            // Ajouter la projection au film
            film->projection = realloc(film->projection, (film->nombreProjection + 1) * sizeof(Projection));
            film->projection[film->nombreProjection] = projections[i];
            film->nombreProjection++;
        }
    }
    printf("\nDonnees recuperer avec succee\n");
}
void afficherProjectionsAvecPlacesDisponibles(Projection *projections, unsigned int nb_projections, Film *films, unsigned int nb_films, SalleCenima *salles, unsigned int nb_salles)
{
    int i;
    printf("Projections avec places disponibles :\n");

    for (i = 0; i < nb_projections; ++i)
    {
        if (projections[i].nbPlacesDisponible > 0)
        {
            Film *film = chercherFilmParId(films, nb_films, projections[i].filmId);
            SalleCenima *salle = rechercheSalleParId(salles, nb_salles, projections[i].salleId);
            if (film != NULL && salle != NULL)
            {
                printf("\nProjectionId : %d \n", projections[i].projectionId);
                printf("\nFilm : %s \n", film->titreFilm);
                printf("\nLa salle : %s ", salle->nomSalle);
                printf("\nLa Date : ");
                afficheDate((projections[i].dateProjection));
                printf("\nL'Heure Debut  ");
                afficheHeure(projections[i].heureDebut);
                printf("\nL'Heure Fin : ");
                afficheHeure(projections[i].heureFin);
                printf("\nNombre des places disponible : %u\n", projections[i].nbPlacesDisponible);
                printf("\nPrix du projection : %d\n", projections[i].prixBillet);
                printf("\n\n\n");
            }
        }
    }
}
// Menu pour l'admin
int menuAdmin()
{
    int choixAdmin;
    unsigned int choixSalle;
    unsigned int choixFilm;
    int test;
    int id;
    Film *f;
    Date d;
    SalleCenima *sc = (SalleCenima *)malloc(sizeof(SalleCenima));
    Projection *p;
    while (1) // Infinite loopjusqua l-utilisatuer choisie 10 ou 11
    {
        printf("\nMenu Admin :\n");
        printf("|-------------- 1. Ajouter un film -----------------------------------|\n");
        printf("|-------------- 2. Ajouter une salle ---------------------------------|\n");
        printf("|-------------- 3. Ajouter une projection ----------------------------|\n");
        printf("|-------------- 4. Supprimer une Projection --------------------------|\n");
        printf("|-------------- 5. Afficher les projection En Details ----------------|\n");
        printf("|-------------- 6. Afficher les clients ------------------------------|\n");
        printf("|---------------7. Afficher les films --------------------------------|\n");
        printf("|-------------- 8. Afficher les salle --------------------------------|\n");
        printf("|-------------- 9. Afficher les projections --------------------------|\n");
        printf("|-------------- 10.Revenue vers la menu ------------------------------|\n");
        printf("|-------------- 11.Quitter le programme ------------------------------|\n");
        printf("Votre choix : ");
        scanf("%d", &choixAdmin);
        switch (choixAdmin)
        {
        case 1:
            // Appel de la fonction pour ajouter un film
            // ajouterFilm();
            f = (Film *)malloc(sizeof(Film));
            saisieFilm(f);
            ajouterFilmDansLaTableDesFilms(films, &nb_films, *f);
            printf("\n|------------Film ajouter avec succee-------------|\n");
            break;
        case 2:
            // Appel de la fonction pour ajouter une salle
            saisieSalleCenima(sc);
            ajoutSalleDansLaListeDeSalles(&salles, &nb_salles, *sc);
            printf("\n|------------Salle ajouter avec succee-------------|\n");
            break;
        case 3:
            // Appel de la fonction pour ajouter une projection
            // ajouterProjection();
            p = (Projection *)malloc(sizeof(Projection));
            // afficher Tout les salle
            AfficherToutesLesSalles(salles, nb_salles);
            printf("\n|--------------------Choisie Une salle Par idSalle ou annuler Par 0 :  ");
            scanf("%u", &choixSalle);
            getchar();
            while (choixSalle != 0)
            {
                if (estSallExiste(salles, nb_salles, choixSalle) == 1)
                {
                    afficherTousLesFilms(films, nb_films);
                    printf("\n|--------------------Choisie Un Film Par idFilm ou annuler Par 0 :  ");
                    scanf("%u", &choixFilm);
                    getchar();
                    if (choixFilm == 0)
                    {
                        printf("\n\t Vous avez decide d'annuler l'ajout");
                        choixSalle = 0; // annulation
                    }
                    else
                    {
                        if (estFilmExist(films, nb_films, choixFilm) == 1)
                        {
                            printf("\n|-------------------Ajout de Projection...\n\n");
                            d = getDateFilm(films, nb_films, choixFilm);
                            creeProjection(p, choixFilm, choixSalle, d);
                            ajoutDansTousLesProjections(*p);
                            ajouterProjectionPourFilmParId(*p, choixFilm);
                            ajouterProjectionPourSalleParId(*p, choixSalle);
                            choixSalle = 0; // Fin de l'ajout
                            choixFilm = 0;
                            printf("\n\n|------------------Projection Ajoutee avec succes.\n");
                        }
                        else
                        {
                            printf("\n|------------Le Film %d n'exist Pas--------------------|\n", choixFilm);
                        }
                    }
                }
                else
                {
                    printf("\n|------------La Salle %d n'exist Pas--------------------|\n", choixSalle);
                    printf("\n|--------------------Choisie Une salle Par idSalle ou annuler Par 0 :  ");
                    scanf("%u", &choixSalle);
                    getchar();
                }
            }
            break;
        case 4:
            // Appel de la fonction pour supprimer une projection
            afficherToutLesProjections(projections, nb_projections);
            printf("choisir Une Projection que veux supprimer avec l'id de Projection : ");
            scanf("%d", &id);
            supprimerProjectionsDansSalleCenima(salles, &nb_salles, id);
            supprimerProjectionsDansReservation(reservations, &nb_reservation, id);
            supprimerReservationsLieesAProjectionPourTousLesClients(clients, nb_clients, id);
            supprimerProjectionsDansFilm(films, &nb_films, id);
            supprimerProjection(projections, &nb_projections, id);
            break;
        case 5:
            // Appel de la fonction pour supprimer une salle
            afficherToutLesProjectionsWithDetails(projections, nb_projections);
            break;
        case 6:
            afficherListeDesClients(clients, nb_clients);
            break;
        case 7:
            // afficher Tout les Films
            afficherTousLesFilms(films, nb_films);
            break;
        case 8:
            // Affiche Tout les salles
            AfficherToutesLesSalles(salles, nb_salles);
            break;
        case 9:
            // Afficher les projections
            afficherToutLesProjections(projections, nb_projections);
            break;
        case 10:
            // Appel de la fonction pour ajouter une salle
            menu();
            return 1;
        case 11:
            // enregistrer tous les donnee dons la base du donee
            // quiter le pregramme
            printf("\n|----------Vous avez quiter le Programe-------------|\n\n");
            remplirToutLesTableToFile();
            return 1;
        default:
            printf("Choix invalide.\n");
            break;
        }
    }
}

// Menu pour le client
int menuClient()
{
    int choixClient;
    int choixReservation;
    char *Cin;
    int test, payment;
    Client *c;
    Reservation *r;
    Projection *p;
    printf("\nLogin...\n");
    printf("Entrer votre Cin : ");
    Cin = malloc(sizeof(char) * 100);
    scanf("%s", Cin);
    test = rechercheClientParCin(clients, nb_clients, Cin);
    if (test == -1)
    {
        printf("CIN Incorrect !\n");
        printf("\nRemplir vos Info svp !!!\n\n");
        c = (Client *)malloc(sizeof(Client));
        saisirClient(c);
        ajoutClientDansLaListeDeClient(clients, &nb_clients, *c);
        test = nb_clients - 1;
        printf("\n|------------Vous etes Registrer avec succee-------------|\n");
        printf("\nBienvenu %s \n", clients[test].nomClient);
    }
    else
    {
        printf("\nBienvenu %s \n", clients[test].nomClient);
    }
    while (1)
    {
        printf("\n\nMenu Client :\n");
        printf("|-------------------1. Afficher Les Films A voir-----------------------|\n");
        printf("|-------------------2. Reserver un ticket------------------------------|\n");
        printf("|-------------------3. Afficher Vos Reservation -----------------------|\n");
        printf("|-------------------4. Annuler Une Reservation ------------------------|\n");
        printf("|-------------------5. Payer Une Reservation --------------------------|\n");
        printf("|-------------------6. Revenir Vers Menu Principal --------------------|\n");
        printf("|-------------------7. Quitez le programme-----------------------------|\n");
        printf("Votre choix : ");
        scanf("%d", &choixClient);
        getchar();
        switch (choixClient)
        {
        case 1:
            afficherProjectionsAvecPlacesDisponibles(projections, nb_projections, films, nb_films, salles, nb_salles);
            break;
        case 2:
            // Appel de la fonction pour reserver un ticket
            afficherProjectionsAvecPlacesDisponibles(projections, nb_projections, films, nb_films, salles, nb_salles);
            printf("\nChoix du type de reservation En choisisant L'id de Projection :");
            scanf("%d", &choixReservation);
            p = rechercheProjectionParId(projections, nb_projections, choixReservation);
            r = (Reservation *)malloc(sizeof(Reservation));
            creeReservation(r, clients[test].clientId, choixReservation);
            if (p->nbPlacesDisponible < r->nombreBilletReserver)
            {
                printf("\n!!!------- Vous pouver pas Reserver %d place(s) Car il reste juste %d place(s) pour la projection : \n", r->nombreBilletReserver, p->nbPlacesDisponible);
                afficherProjection(*p);
            }
            else
            {
                printf("Reservation en cours ...\n\n");
                // calcule Montant
                p->nbPlacesDisponible = p->nbPlacesDisponible - r->nombreBilletReserver;
                r->montantTotal = r->nombreBilletReserver * p->prixBillet;
                ajoutDansToutesLesReservations(*r);
                ajouterReservationDansClient(&clients[test], *r);
                ajouterReservationPourProjection(p, *r);
                printf("Reservation effectuee.\n\n");
                printf("le montant Totale est: %d\n", r->montantTotal);
                printf("Remarque : Si vous payer pas votre reservation va etre annuler automatiquement\n");
                printf("Merci de Payer avant deconnecter en cliquant sur 5.\n\n");
            }
            free(r);
            break;
        case 3:
            printf("Les Reservation Effectuer Par Vous %s %s", clients[test].nomClient, clients[test].prenomClient);
            afficherReservationClient(clients[test]);
            break;
        case 4:
            afficherReservationClient(clients[test]);
            printf("\n\n|---------------Choisir l'id de la reservation a annuler : ");
            scanf("%d", &choixReservation);
            r = rechercherReservationParID(reservations, nb_reservation, choixReservation);
            p = rechercheProjectionParId(projections, nb_projections, r->projectionId);
            p->nbPlacesDisponible += r->nombreBilletReserver;
            supprimerReserationFromReservations(reservations, &nb_reservation, choixReservation);
            // supprimmer reservation from client
            supprimerReservationFromClient(&clients[test], choixReservation);
            supprimerReservationFromProjection(projections, &nb_projections, choixReservation);
            printf("\n\n");
            break;
        case 5:
            // payment
            afficherReservationClientNonPayer(clients[test]);
            printf("\n\nChoisir La reservation a payer par id reservation: ");
            scanf("%d", &choixReservation);
            printf("Choisir la methode du paiment :\n\n");
            printf("1. Credit Card \n2. Paypal \n3. Visa \n\n");
            printf("Votre choix : ");
            scanf("%d", &payment);
            setStatuePaiment(reservations, nb_reservation, choixReservation);
            setStatuePayementInClient(clients[test], choixReservation);
            setStatuePayementInProjection(projections, nb_projections, choixReservation);
            break;
        case 6:
            supprimerReserationFromReservationsNonpayer(reservations, &nb_reservation);
            // supprimmer reservation from client
            supprimerReservationFromClientNonpayer(&clients[test]);
            supprimerReservationFromProjectionNonpayer(projections, nb_projections);
            menu();
            return 1;
        case 7:
            printf("\n|----------Vous avez quiter le Programe-------------|\n\n");
            supprimerReserationFromReservationsNonpayer(reservations, &nb_reservation);
            // supprimmer reservation from client
            supprimerReservationFromClientNonpayer(&clients[test]);
            supprimerReservationFromProjectionNonpayer(projections, nb_projections);
            remplirToutLesTableToFile();
            return 1;
        default:
            printf("Choix invalide Choisir 1, 2 Ou. quiter Par 3\n");
            break;
        }
    }
}

int menu()
{
    int choix;
    printf("Veuillez choisir l'option :\n");
    printf("1. Admin\n");
    printf("2. Client\n");
    printf("3.pour quiter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    while (1) // Infinite loopjusqua l-utilisatuer choisie 1 ou 2 ou 3
    {
        switch (choix)
        {
        case 1:
            menuAdmin();
            printf("\n|=============Merci Pour Votre visite===============|\n");
            return 1;
        case 2:
            menuClient();
            printf("\n|=============Merci Pour Votre visite===============|\n");
            return 1;
        case 3:
            printf("\n|----------Vous avez quiter le Programe-------------|\n\n");
            printf("\n|=============Merci Pour Votre visite===============|\n");
            remplirToutLesTableToFile();
            return 1;
        default:
            printf("Choix invalide. Veuillez choisir 1 pour admin ou 2 pour client ou 3 pour quiter : ");
            scanf("%d", &choix);
            break;
        }
    }
}
