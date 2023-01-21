#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/home/pfr/pfr_code/texte/include/piles2.h"

/*Pile1*/

Table initT() { return NULL; }

Table addT(Table p, int fich, int nb)
{
    Table paux = (Table)malloc(sizeof(Cel1));
    paux->fich = fich;
    paux->nb = nb;
    paux->suiv = p;
    return paux;
}

void affT(Table p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("    %s %d\n", p->fich,p->nb);
        snprintf(chaine, 256, "echo '%d %d'>> /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->fich, p->nb);
        system(chaine);
        p = p->suiv;
    }
}

/*Pile2*/

MotTable initM() { return NULL; }

MotTable addM(MotTable p, char *mot)
{
    MotTable paux = (MotTable)malloc(sizeof(Cel2));
    snprintf(paux->mot, sizeof(paux->mot), "%s", mot);
    paux->table = NULL;
    paux->motTableSuiv = p;
    return paux;
}

MotTable add(MotTable p, int nb, char *mot, int fich)
{
    int nb_min;
    FILE *config = fopen("/home/pfr/pfr_code/config.txt", "r");
    fscanf(config, "%d", &nb_min);
    fclose(config);

    MotTable paux = p;
    MotTable posC2 = NULL;
    if (nb >= nb_min)
    {
        while (paux != NULL)
        {
            if (strcmp(paux->mot, mot) == 0)
                posC2 = paux;
            paux = paux->motTableSuiv;
        }
        if (posC2 == NULL)
        {
            p = addM(p, mot);
            p->table = addT(p->table, fich, nb);
        }
        else
        {
            if (posC2->table->fich != fich)
            {
                posC2->table = addT(posC2->table, fich, nb);
            }
        }
    }
    return p;
}

void aff(MotTable p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("%s\n",p->mot);
        snprintf(chaine, 256, "echo '%s' >> /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->mot);
        system(chaine);
        if (p->table != NULL)
        {
            affT(p->table);
        }
        p = p->motTableSuiv;
    }
}
