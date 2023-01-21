#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "/home/pfr/pfr_code/texte/include/tok.h"
#include "/home/pfr/pfr_code/texte/include/clean.h"
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"
#include "/home/pfr/pfr_code/texte/include/indexation_texte.h"

#define CHEMIN_STOCKAGE_FICH_RECH "/home/pfr/pfr/texte/recherche_texte"
#define CHEMIN_TRAITEMENT_FICH_RECH "/home/pfr/pfr_code/traitement"
#define CHEMIN_FICHIER_TOK_RECH "/home/pfr/pfr_code/traitement"
#define CHEMIN_BASE_DESCIPTEUR_TEXTE "/home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt"
#define CHEMIN_FICHIER_OCCURENCE_COMMUN "/home/pfr/pfr_code/data/OccurenceCommun.txt"
#define CHEMIN_LISTE_RECHERCHE_TRIEE "/home/pfr/pfr_code/data/liste_recherche_triee.txt"
#define CHEMIN_LISTE_RECHERCHE "/home/pfr/pfr_code/data/liste_recherche.txt"

void nbOccurCommun(int * tabOccurCommun, DESCRIPT_TXT descriptRech, int nbFichierTxt){

    //initialisation du nombez d'occurrence de chaque fichier à 0
    for(int i=0; i<nbFichierTxt;i++){
        *(tabOccurCommun+i)=0;
    }
    MOT mot;
    char recupFichMotCommun[256]={0};
    system("echo '' > "CHEMIN_FICHIER_OCCURENCE_COMMUN);
    FILE * OccurenceCommun = fopen(CHEMIN_FICHIER_OCCURENCE_COMMUN,"r");
    int identFich;
    char motRecup[50]={0};
    int occur;

    //recherche parmis le mots de la pile de mot
    while(descriptRech.pile_mot != NULL){
        fseek(OccurenceCommun,0,SEEK_SET);
        descriptRech.pile_mot = dePILE(descriptRech.pile_mot, &mot);

        //Récupération de la liste des ideantifiants et du nombre d'occurrence pour le mot.mot
        int ret = snprintf(recupFichMotCommun,sizeof(recupFichMotCommun),"grep '%s ' %s > %s",mot.mot,CHEMIN_BASE_DESCIPTEUR_TEXTE,CHEMIN_FICHIER_OCCURENCE_COMMUN);
        if(ret<0){
            abort();
        }
        else system(recupFichMotCommun);

        //Récupération des données
        while(fscanf(OccurenceCommun,"%d",&identFich)==1){
            fscanf(OccurenceCommun,"%s",motRecup);
            fscanf(OccurenceCommun,"%d",&occur);
            if(strlen(motRecup)==strlen(mot.mot)){
                //ajout des occurrences au tableau
                if(occur <= mot.nb_occur){
                    *(tabOccurCommun+identFich-1)+= occur;
                }
                else *(tabOccurCommun+identFich-1)+= mot.nb_occur;
            }
        }
    }
    fclose(OccurenceCommun);
}

int compareNbOccurComm(int * tabOccurCommun,int nbFichierTxt){
    int occurMax = 0;
    int identFichier = 0;
    char addListeFichTriee[256]={0};
    char addListeFich[256]={0};

    system("echo '' > "CHEMIN_LISTE_RECHERCHE_TRIEE);

    for(int i=nbFichierTxt-1; i>=0; i--){

        if(*(tabOccurCommun+i)> occurMax){
            occurMax = *(tabOccurCommun+i);
            identFichier = i+1;
            int ret = snprintf(addListeFich,sizeof(addListeFich),"echo %d %d  >> "CHEMIN_LISTE_RECHERCHE,identFichier,*(tabOccurCommun+i));
            if(ret<0){
                abort();
            }
            system(addListeFich);
        }
    }
    int ret = snprintf(addListeFichTriee,sizeof(addListeFichTriee),"sort -k2nr "CHEMIN_LISTE_RECHERCHE" > "CHEMIN_LISTE_RECHERCHE_TRIEE);
        if(ret<0){
            abort();
        }
        system(addListeFichTriee);
    return identFichier;
}

void recherche_comparaison_texte(char * pathFileRecherchee, int nbFichierTxt){

    char fileName[256]={0};
    char recupNom[256]={0};
    int recherTxt = 0;
    int * tabOccurCommun = (int *) malloc(sizeof(int)*nbFichierTxt);
    int identRessemble=0;

    system("echo '' > /home/pfr/pfr_code/data/liste_recherche_triee.txt");
    system("echo '' > /home/pfr/pfr_code/data/liste_recherche.txt");

    int ret = snprintf(recupNom,sizeof(recupNom),"basename %s > /home/pfr/pfr_code/data/recupNomRech.txt",pathFileRecherchee);
    if(ret<0){
        abort();
    }
    else system(recupNom);

    FILE * recupNomRech = fopen("/home/pfr/pfr_code/data/recupNomRech.txt","r");
    if(fscanf(recupNomRech,"%s",fileName)==1){
        system("rm -f /home/pfr/pfr_code/traitement/*.tok;rm -f /home/pfr/pfr_code/traitement/*.clean;");
        nettoyage(fileName,CHEMIN_STOCKAGE_FICH_RECH,CHEMIN_TRAITEMENT_FICH_RECH);
        filtrage(fileName,CHEMIN_TRAITEMENT_FICH_RECH);
    }
    fclose(recupNomRech);
    DESCRIPT_TXT descriptRech = initDescript();
    descriptRech = crea_descript_txt(fileName,0,CHEMIN_FICHIER_TOK_RECH);

    nbOccurCommun(tabOccurCommun, descriptRech, nbFichierTxt);
    identRessemble = compareNbOccurComm(tabOccurCommun,nbFichierTxt);

    free(tabOccurCommun);

    system("cat /home/pfr/pfr_code/data/liste_recherche_triee.txt");
}