#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pfr/pfr_code/texte/include/descripteur_Txt.h"
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"

//initialise un mot
MOT initMot(){
    MOT mot;
    mot.ident = 0;
    mot.nb_occur = 0;
    mot.mot_suiv = NULL;
    return mot;
}

//ajoute les caractéristique d'un mot d'un fichier.tok
MOT addMot(char * motTxt, int ident,char * fileName){
    MOT mot;
    mot.ident = ident;
    snprintf(mot.mot,sizeof(mot.mot),"%s",motTxt);
    mot.nb_occur = chercheNbOccur(motTxt,fileName);
    mot.mot_suiv = NULL;
    return mot;
}

//Créé une pile de mot relatif à un fichier et met à jour le paramètre nbMotDiff du fichier.tok
void creerPileMot(PILE * pileMot , char * fileName, int * nbMotDiff, int ident, char * cheminRepertoireTok){
    char recupTokUniq[256]={0};   
    char motRecup[256]={0};
    char pathFile[256]={0};
    *pileMot = init_PILE();
    MOT mot = initMot();
    *nbMotDiff = 0;
    int nb_occ_min = 0;

    //Création  du fichier CloneTok avec une seule occurence pas mot du fichier .tok
    snprintf(recupTokUniq,sizeof(recupTokUniq),"sort %s/%s.tok | uniq > /home/pfr/pfr_code/traitement/CloneTok/%sClone.tok",cheminRepertoireTok,fileName,fileName);
    system(recupTokUniq);

    //ouverture du fichier Clone.tok
    snprintf(pathFile,sizeof(pathFile),"/home/pfr/pfr_code/traitement/CloneTok/%sClone.tok",fileName);
    FILE * fichier_CloneTok = fopen(pathFile,"r");

    //récupération du nombre d'occurrence minimum pour qu'un mot soit ajouter au descripteur
    FILE * fichier_config = fopen("/home/pfr/pfr_code/config.txt","r");
    fscanf(fichier_config,"%d",&nb_occ_min);
    fclose(fichier_config);
    
    //ajout des mots au descripteur (création de la pile de mot) 
    while(fscanf(fichier_CloneTok,"%s",motRecup)==1){
        mot = addMot(motRecup,ident,fileName);
        if((mot.nb_occur >= nb_occ_min)&&(strlen(mot.mot)>2)){
            *pileMot = emPILE(*pileMot,mot);
        }
    }
    //comptage du nombre de mot unique
    *nbMotDiff = comptageNbMot(pathFile);

    fclose(fichier_CloneTok);
}

//initialise le descripteur avec des valeurs par défaut
DESCRIPT_TXT initDescript(){
    DESCRIPT_TXT descript;
    descript.ident = 0;
    descript.pile_mot = init_PILE();
    descript.nb_mot_diff = 0;
    descript.taille_txt = 0;
    return descript;
}

//créé le descripteur d'un fichier.tok à partir du chemin du fichier source .xml (identifiant) et du fichier tok accessible dans l'arborescence de répertoires
DESCRIPT_TXT creerDescript(char * fileName, int ident,char * cheminRepertoireTok){

    DESCRIPT_TXT descript = initDescript();
    char pathFile[256]={0};
    char motRecup[256]={0};

    descript.ident = ident;
    creerPileMot(&descript.pile_mot,fileName,&(descript.nb_mot_diff),ident,cheminRepertoireTok);
    snprintf(pathFile,sizeof(pathFile),"%s/%s.tok",cheminRepertoireTok,fileName);
    //Détermination de la taille du texte en nombre de mot
    descript.taille_txt= comptageNbMot(pathFile);
    return descript;
}

int chercheNbOccur(char * mot, char * fileName){

    char cptnbMot[256]={0};
    int nb_occurrence = 0;

    //comptage du nombre d'occurrence d'un mot dans le fichier passé en paramètre
    snprintf(cptnbMot, sizeof(cptnbMot), "grep -ow '%s' /home/pfr/pfr/texte/tok/%s.tok | wc -l > /home/pfr/pfr_code/data/nbOccur.txt",mot,fileName);
    system(cptnbMot);

    //récupération du nombre d'occurrence du mot dans le fichier nbOccur.txt
    FILE * nbOccur = fopen("/home/pfr/pfr_code/data/nbOccur.txt","r");
    fscanf(nbOccur,"%d",&nb_occurrence);
    fclose(nbOccur);
    return nb_occurrence;
}

//ajout du descripteur au fichier bas descripteur texte
void concatBaseDescript(DESCRIPT_TXT descript){

    //ajout de l'identifiant
    char ajoutIdentDescript[256]={0};
    snprintf(ajoutIdentDescript,sizeof(ajoutIdentDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.ident);
    system(ajoutIdentDescript);

    //ajout des mots
    char ajoutMotDescript[256]={0};
    MOT mot = initMot();
    while(!PILE_estVide(descript.pile_mot)){
        descript.pile_mot=dePILE(descript.pile_mot, &mot);
        snprintf(ajoutMotDescript,sizeof(ajoutMotDescript),"echo %d %s %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",mot.ident,mot.mot,mot.nb_occur);
        system(ajoutMotDescript);
    }
    //ajout du nombre de mot différents
    char ajoutNbMotDiffDescript[256]={0};
    snprintf(ajoutNbMotDiffDescript,sizeof(ajoutNbMotDiffDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.nb_mot_diff);
    system(ajoutNbMotDiffDescript);

    //ajout de la taille du texte en nombre de mot
    char ajoutNbMotDescript[256]={0};
    snprintf(ajoutNbMotDescript,sizeof(ajoutNbMotDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.taille_txt);
    system(ajoutNbMotDescript);
} 

int comptageNbMot(char * pathFile){

    int ctpMot=0;
    char comptageMot[256]={0};
    //comptage du nombre de mot du fichier passer en paramètre
    snprintf(comptageMot,sizeof(comptageMot),"wc -w %s > /home/pfr/pfr_code/data/comptage.txt",pathFile);
    system(comptageMot);
    
    //récupération du nombre de mot dans le fichier comptage.txt
    FILE * comptage = fopen("/home/pfr/pfr_code/data/comptage.txt","r");
    fscanf(comptage,"%d",&ctpMot);
    fclose(comptage);
    return ctpMot;
}