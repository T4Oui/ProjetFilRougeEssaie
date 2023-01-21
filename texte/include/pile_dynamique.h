#ifndef PILE_DYNAMIQUE_H_INCLUS     
#define  PILE_DYNAMIQUE_H_INCLUS    

#include "descripteur_Txt.h"

PILE init_PILE();
	
void affiche_PILE(PILE p);

int PILE_estVide(PILE p);


PILE emPILE(PILE p, MOT mot);

PILE dePILE(PILE p, MOT * mot);


#endif
