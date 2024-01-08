#ifndef DATE_H
#define DATE_H

struct date
{
unsigned int j ;
unsigned int m ;
unsigned int a ;
};
typedef struct date Date ; 

void afficheDate(Date d);
void saisieDate(Date *d);
void saisieDateFilm(Date *d);
void saisieDateProjection(Date *d,Date d2);
int validateDateProjectionFile(Date d);
int validateDate(Date d);
int validateDateFilm(Date d);
int validateDateProjection(Date d, Date d2);
#endif //DATE_H