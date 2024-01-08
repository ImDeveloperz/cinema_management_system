#include<stdio.h>
#include"cenima.h"

int main()
{
    remplirToutLesTableFromFile();
    printf("|==========Bienvenue dans le systeme de gestion de cinema=========|\n");
    menu();
    return 0;
}
