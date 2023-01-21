#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pfr/pfr_code/texte/include/table_index.h"

MotTable table(MotTable p, int ident, char *fichier)
{
    char chaine1[256] = {0};
    char mot[256];
    int ret = snprintf(chaine1, 256, "/home/pfr/pfr/texte/tok/%s.tok", fichier);
    if (ret < 0)
    {
        abort();
    }
    FILE *fich = fopen(chaine1, "r");
    while (fscanf(fich, "%s", mot) == 1)
    {
        p = add(p, chercheNbOccur(mot, fichier), mot, ident);
    }
    fclose(fich);
    return p;
}