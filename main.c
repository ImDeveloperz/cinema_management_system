#include<stdio.h>
#include"cenima.h"
#include"time.h"
int main()
{
    remplirToutLesTableFromFile();
    printf("|==========Bienvenue dans le systeme de gestion de cinema=========|\n");
    menu();
    return 0;
}
