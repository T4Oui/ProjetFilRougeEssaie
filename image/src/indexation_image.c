#include <stdio.h>
#include <stdlib.h>
#include <math.h>


FILE* openFile( const char * nomFichier , const char * m ) // Fonction pour ouvrir le fichier avec le mode qu'il le prend en parapmetre 
{
  FILE* file = fopen ( nomFichier , m) ; 
  if (file == NULL ) { 
    printf ( "error opening file ") ; 
  }
  return file ; 
}

int quantification (int tab[]  , int b , int n )  // Fonction pour faire la quantification qui prend en parametre un tableau et renvoie la nouvelle valeur de pixel 
{ 

int t[7] ;
int nouPix = 0 ;

int Nbr = (n *b)-1 ;
int i = 0;
while (( i<3) && (Nbr >=0 ))
    { 
    int  a = tab[i] ;
    for (int j = 0 ; j<8 ; j ++)
    {
    t[j] = a % 2 ;
    a = a / 2;
    } 
       nouPix   = nouPix + (t[7] * pow(2 , Nbr) )+ (t[6] * pow(2 , Nbr-1)) ;
       Nbr = Nbr - 2 ;
       i++ ;
       }
    
    
    return ( nouPix) ; 
    } 




 int ** pretraitement_image ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n)  // Fonction pour parcourir le fichier et appel la fonction quantification pour chaque pixel 
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"/home/pfr/pfr/image/fich_images/txt/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" );
   
    fscanf(f,"%d" , ptrNBLIG);  // nombre de ligne 
    
    fscanf(f,"%d" , ptrNBCOL ); // nombre de colonne

    fscanf(f,"%d", ptrB);   // nombre de composantes
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
      printf ("erreur ") ; 
     exit(1); }

    int tab[3];
    if ( (*ptrB) !=3 ) // image N/B
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = {pixel , 0 ,0}
               }
               } }
    else  // image en couleur 
      {  int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
         int rouge[taille] ;
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
          {
            for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
         {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0){ 
                  fscanf(f,"%d", &rouge[r]); 
                   r++ ; }
              else if (i==1){ 
                  fscanf(f,"%d", &vert[v]); 
                   v++ ; }
              else { 
                  fscanf(f,"%d", &bleu[bl]); 
                   bl++ ; }
                
           
           }
         }}
        int t =0 ; 

        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = { pixel_rouge,pixel_vert,pixel_bleu}
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }

int ** pretraitement_recherche ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n) // Fonction pour la recherche 
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"autre_chemin_pour_la_recherche/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" );  
   
    fscanf(f,"%d" , ptrNBLIG);
    
    fscanf(f,"%d" , ptrNBCOL );

    fscanf(f,"%d", ptrB);  
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
      printf ("erreur ") ; 
     exit(1); }

    int tab[3];
    if ( (*ptrB) !=3 )
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ;
               }
               } }
    else 
      {  int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
         int rouge[taille] ;
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
          {
            for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
         {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0){ 
                  fscanf(f,"%d", &rouge[r]); 
                   r++ ; }
              else if (i==1){ 
                  fscanf(f,"%d", &vert[v]); 
                   v++ ; }
              else { 
                  fscanf(f,"%d", &bleu[bl]); 
                   bl++ ; }
                
           
           }
         }}
        int t =0 ; 

        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ;
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }



int histogramme ( int ** tab , int nbr , int * ptrNBLIG , int * ptrNBCOL)  // Fonction pour calculer nombre d'accurrence d'un pixel dans le matrice 
{
     
int acc = 0  ;
for (int i = 0 ;i < *ptrNBLIG ; i++ )
       for ( int j =0 ; j < *ptrNBCOL ; j++)
            if (tab[i][j] ==  nbr)
                 acc++ ;

return acc ; }

void mise_a_jour_base_image (  FILE* LBI , FILE* BDI, const char* f ,int*  descripteur , int n , int* d ) // Fonction pour faire le mise a jour des fichiers base_descripteur_image et base_image
         {  int c = pow ( 2 , ((*d)*n) ) + 1 ; 
             fprintf (LBI, "%d  %s \n" , descripteur[0] ,f) ;  
             for  ( int i=0  ; i < c ; i++ )
                fprintf ( BDI , "%d  " , descripteur[i]) ;
             fprintf(BDI , "\n") ; 
         }



int configuration (FILE* fichier)  //Fonction pour recupere le nombre de bits utilisés pour la quantification

{
  int carac=0;
  fseek(fichier,35,SEEK_SET); //permet de placer le curseur au niveau du caractère 13 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseu
  return carac;
  }
 /* int nb;
  char carac;
  for(int i=0;i<4;i++){ // dans le config, la valeur voulue est à la ligne 4
    fscanf(fichier,"%d",&nb); // lis le caractère au niveau du curseur
    fscanf(fichier,"%s",&carac); 
  }
  return nb;*/

int* descripteur_image ( int ** tab , int n , int * ptrNBCOL , int * ptrNBLIG , int * d) // Fonction pour construiure le descripteur 
{
int c = pow ( 2 , ((*d)*n) )  ; //  c+1 : taille d'un descripteur 
int* D =  (int*) malloc ((c+1) *sizeof( int)); 
 D[0]=0 ; 
for (int i = 0 ; i < c ; i++ ){ 
    D[i+1] = histogramme( tab , i  , ptrNBLIG , ptrNBCOL) ; 
    }
  return D ; 
} 
int* indexation_recherche (const char * image )  // fonction pour la recherche  
{      FILE* config = openFile("./config.txt" , "r" ); 
         int  n = configuration(config); 
         int NBLIG ;
         int NBCOL ;
         int id =  100 ; 
         int d ; 
         int ** tab = pretraitement_recherche(image , &NBLIG ,&NBCOL , &d  , n ) ; 
         int * Descripteur = descripteur_image  ( tab , n , &NBCOL, &NBLIG , &d  ) ; 
         if (d==3){ 
         Descripteur[0]= 3000 + id;
          }
         else { 
          Descripteur[0]= 4000 +id; 
          }
         for (int i = 0 ; i< NBLIG ;i++ )
               free (tab[i]) ; 
         free(tab) ;  
         return (Descripteur) ;
}


void indexation_image () //Une fonction pour indexer le fichier image qui appelle toutes les fonctions précédentes
{ 
 int id =0 ; 
 char fileName[200] ;
 system("ls /home/pfr/pfr/image/fich_images/txt > /home/pfr/pfr_code/data/listeFichierImage.txt " ); 
 FILE * listeFichier = openFile("/home/pfr/pfr_code/data/listeFichierImage.txt","r") ; 

 while ( fscanf ( listeFichier ,"%s",fileName )==1)
 { 

 printf ( "/home/pfr/pfr/image/fich_images/txt/%s\n",fileName);
 id++ ;
 FILE* config = openFile("./config.txt" , "r" ); 
 int n = configuration(config); 
 fclose(config);
 int NBLIG ;
 int NBCOL ;
 int d ; 
 int ** tab = pretraitement_image( fileName , &NBLIG ,&NBCOL , &d , n ) ; 
 int * Descripteur = descripteur_image ( tab , n , &NBCOL, &NBLIG , &d ) ; 
 FILE* BDI = NULL ;
 FILE * LBI = NULL ;
 if (d==3){ 
 Descripteur[0]= 3000 + id;
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt" ,"a" ) ;
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt","a" ) ;
 }
 
 else { 
 Descripteur[0]= 4000 +id; 
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt" ,"a" ) ;
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt","a" ) ;
 }
 mise_a_jour_base_image ( LBI , BDI, fileName, Descripteur , n , &d) ;
 for (int i = 0 ; i< NBLIG ;i++ )
 free (tab[i]) ; 
 free(tab) ; 
 free (Descripteur ) ; 
 
 fclose( BDI );
 fclose( LBI ) ; 
 }
 fclose(listeFichier) ; 
}




