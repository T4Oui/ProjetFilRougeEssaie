#include <stdio.h>
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"
#include <stdlib.h>

PILE init_PILE(){
	PILE p = NULL;
	return p;
}

void affiche_PILE(PILE p){
	
	while(p != NULL){
		printf("\n ident = %d,",p->ident);
    	printf("mot = %s,",p->mot);
		printf(" nb_occur = %d",p->nb_occur);
		p=p->mot_suiv;
	}
}

int PILE_estVide(PILE p){

	return (p == NULL);
}
//Empile un mot dans la pile de mot
PILE emPILE(PILE p, MOT mot){
	
	PILE paux =(PILE)malloc(sizeof(struct MOT));
	if(!PILE_estVide(paux)){
		paux->ident = mot.ident;
		snprintf(paux->mot,sizeof(paux->mot),"%s",mot.mot);
		paux->nb_occur = mot.nb_occur;
		paux->mot_suiv = p;
	}
	return paux;
}

PILE dePILE(PILE p, MOT * mot){

	PILE paux=p;
	if(!PILE_estVide(p)) {
		mot->ident = paux->ident;
		snprintf(mot->mot,sizeof(mot->mot),"%s",paux->mot);
		mot->nb_occur = paux->nb_occur;
		p = p->mot_suiv;
		free(paux);
	}
	return p;
}