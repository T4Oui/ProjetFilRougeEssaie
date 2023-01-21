#ifndef CLEAN_H_INCLUS
#define CLEAN_H_INCLUS 


void nettoyage (char * fileName, char * pathStockageFich, char * pathTraitement);

void copieRepTravail(char * pathStockageFich, char *fileName, char * pathFile);
void enleverBalise(char * pathFile);
void changerMajMin(char * pathFile);
void supprNPremLig(int n, char * pathFile);
void supprApostrophe(char * pathFile);
void supprChiffre(char * pathFile);
void supprPonctu(char * pathFile);
void supprTiret(char * pathFile);
void supprXml(char * pathFile);

#endif