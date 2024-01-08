#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "time.h"

// afficher date
void afficheDate(Date d)
{
    printf(" %d/%d/%d\n", d.j, d.m, d.a);
}

// saisir date
void saisieDate(Date *d)
{
    do
    {
        printf("\n saisir la date sous form dd/mm/aa : ");
        scanf("%d/%d/%d", &d->j, &d->m, &d->a);
        getchar();
    } while (validateDate(*d) == 0);
    // on peut verifier si la date juste ou non ...
}

void saisieDateFilm(Date *d)
{
    do
    {
        printf("\n saisir la date sous form dd/mm/aa : ");
        scanf("%d/%d/%d", &d->j, &d->m, &d->a);
        getchar();
    } while (validateDateFilm(*d) == 0);
    // on peut verifier si la date juste ou non ...
}

void saisieDateProjection(Date *d, Date d2)
{
    do
    {
        printf("\n saisir la date sous form dd/mm/aa : ");
        scanf("%d/%d/%d", &d->j, &d->m, &d->a);
        getchar();
    } while (validateDateProjection(*d, d2) == 0);
    // on peut verifier si la date juste ou non ...
}

int est_annee_bissextile(int annee)
{
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

int validateDate(Date d)
{
    // Vérifier le mois
    if (d.m < 1 || d.m > 12)
    {
        printf("le mois doit etre compris entre 01 et 12 \n");
        return 0; // Mois invalide
    }

    // Vérifier le jour
    int jours_dans_mois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d.m == 2 && est_annee_bissextile(d.a))
    {
        jours_dans_mois[2] = 29; // Février a 29 jours dans une année bissextile
    }

    if (d.j < 1 || d.j > jours_dans_mois[d.m])
    {
        printf("");
        printf("Le jour doit être compris entre 01 et %d \n", jours_dans_mois[d.m]);
        return 0; // Jour invalide
    }

    // Si les vérifications précédentes sont passées, la date est valide
    return 1;
}

int validateDateFilm(Date d)
{
    return validateDate(d);
}

int comparer_dates(Date date1, Date date2)
{
    if (date1.a < date2.a)
    {
        return -1;
    }
    else if (date1.a > date2.a)
    {
        return 1;
    }
    else
    {
        if (date1.m < date2.m)
        {
            return -1;
        }
        else if (date1.m > date2.m)
        {
            return 1;
        }
        else
        {
            if (date1.j <= date2.j)
            {
                return -1;
            }
            else if (date1.j > date2.j)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

int validateDateProjectionFile(Date d)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    Date date_actuelle;
    date_actuelle.j = tm_info->tm_mday;
    date_actuelle.m = tm_info->tm_mon + 1;     // mois de 0 à 11
    date_actuelle.a = tm_info->tm_year + 1900; // année depuis 1900
    if (comparer_dates(d,date_actuelle) == -1)
    {
        printf("La date du projection ne peut pas etre dans le passe il Doit etre superieur a la date actuelle :\n");
        afficheDate(date_actuelle);
        return 0;
    }
    else
    {
        return 1;
    }
}
int validateDateProjection(Date d, Date d2)
{
    //  La validation de DateProjection se base sur DateFilm :
    //   - Elle ne peut pas etre inférieure à aujourd'hui
    int test = validateDate(d);
    if (test == 0)
    {
        return 0;
    }
    else
    {
        test = comparer_dates(d, d2);
        if (test == -1)
        {
            printf("La date du projection doit etre superieur aux date du film :  ");
            afficheDate(d2);
            return 0;
        }
        else
        {
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            Date date_actuelle;
            date_actuelle.j = tm_info->tm_mday;
            date_actuelle.m = tm_info->tm_mon + 1;     // mois de 0 à 11
            date_actuelle.a = tm_info->tm_year + 1900; // année depuis 1900
            if (comparer_dates(date_actuelle, d) == -1)
            {
                printf("La date du projection ne peut pas etre dans le passe il Doit etre superieur a la date actuelle :\n");
                afficheDate(date_actuelle);
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}
