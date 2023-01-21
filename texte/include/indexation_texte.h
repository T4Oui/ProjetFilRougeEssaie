#ifndef INDEXATION_TEXTE_H_INCLUS
#define INDEXATION_TEXTE_H_INCLUS

#include "descripteur_Txt.h"

void indexation_texte(void);

void recupListeFichierTxt();
void redirCleanTok();
DESCRIPT_TXT crea_descript_txt(char * fileName,int ident,char * cheminRepertoireTok);
void ajoutListeBaseTxt(char * fileName, int ident);

#endif
