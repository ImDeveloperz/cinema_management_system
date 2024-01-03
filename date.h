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

#endif //DATE_H