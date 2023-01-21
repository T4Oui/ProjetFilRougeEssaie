#ifndef RECHERCHE_TEXTE_H_INCLUS
#define RECHERCHE_TEXTE_H_INCLUS

#include "/home/pfr/pfr_code/texte/include/descripteur_Txt.h"

void recherche_comparaison_texte(char * pathFileRecherchee, int nbFichierTxt);
void nbOccurCommun(int * tabOccurCommun, DESCRIPT_TXT descriptMotRech, int nbFichierTxt);
int compareNbOccurComm(int * tabOccurCommun,int nbFichierTxt);

#endif
