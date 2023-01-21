#ifndef indexation_image_H_INCLUS     
#define indexation_image_H_INCLUS 
#include <stdlib.h>

int quantification (int tab[]  , int b , int n );
int ** pretraitement_image( const char* fechier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n);
int ** pretraitement_recherche ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n);
int histogramme ( int ** tab , int nbr , int * ptrNBLIG , int * ptrNBCOL);
void mise_a_jour_base_image (FILE* LBI ,FILE* BDI , const char* f ,int*  descripteur ,int n ,int* d );
FILE* openFile( const char * nomFichier , const char * m );
int* descripteur_image ( int ** tab , int n , int * ptrNBCOL , int * ptrNBLIG , int * d);
int configuration (FILE* fichier);
int* indexation_recherche (const char * image );
void indexation_image () ;

#endif