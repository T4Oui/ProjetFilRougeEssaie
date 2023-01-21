#include <stdio.h> 
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/clean.h"
#include "/home/pfr/pfr_code/texte/include/tok.h"
#include "/home/pfr/pfr_code/texte/include/descripteur_Txt.h"
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"
#include "/home/pfr/pfr_code/texte/include/indexation_texte.h"
#include "/home/pfr/pfr_code/texte/include/piles2.h"
#include "/home/pfr/pfr_code/texte/include/table_index.h"


#define CHEMIN_STOCKAGE_FICH_IDX "/home/pfr/pfr/texte/fich_textes"
#define CHEMIN_TRAITEMENT_FICH_IDX "/home/pfr/pfr_code/traitement"
#define CHEMIN_LISTE_FICHIER_IDX "/home/pfr/pfr_code/data/listeFichierTxt.txt"
#define CHEMIN_FICHIER_SOURCE "/home/pfr/pfr/texte/fich_textes/%s.tok"
#define CHEMIN_FICHIER_TOK_IDX "/home/pfr/pfr/texte/tok"


void indexation_texte(void){

    char fileName[256]={0};
    char pathFileSRC[256]={0};
    char cheminListFich[256]={0};
    char cheminFich[256]={0};
    
    recupListeFichierTxt();

    FILE * listeFichier = fopen(CHEMIN_LISTE_FICHIER_IDX,"r");
    
    if(listeFichier != NULL){
        while(fscanf(listeFichier,"%s",fileName)==1){
            nettoyage(fileName,CHEMIN_STOCKAGE_FICH_IDX ,CHEMIN_TRAITEMENT_FICH_IDX);
            filtrage(fileName,CHEMIN_TRAITEMENT_FICH_IDX);
        }
        redirCleanTok();
    }
    
    DESCRIPT_TXT descript;
    MotTable pMotTable = initM();
    int ident = 1;
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt");
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt");
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt");
    
    fseek(listeFichier,0,SEEK_SET);

    while(fscanf(listeFichier,"%s",fileName)==1){
        int ret = snprintf(pathFileSRC,sizeof(pathFileSRC),CHEMIN_FICHIER_SOURCE,fileName);
        if(ret<0){
            abort();
        }
        descript = crea_descript_txt(fileName,ident,CHEMIN_FICHIER_TOK_IDX);
        concatBaseDescript(descript);
        ajoutListeBaseTxt(pathFileSRC,ident);
        pMotTable = table(pMotTable,ident,fileName);
        ident ++;
    }
    aff(pMotTable);
    fclose(listeFichier);
}

// Créé un fichier avec la liste des textes dans le répertoire et supprime l'extension .xml du nom des fichier
void recupListeFichierTxt()
{
    system("ls /home/pfr/pfr/texte/fich_textes > /home/pfr/pfr_code/data/listeFichierTxt.txt");
    system("sed -i -e 's/.xml//g' /home/pfr/pfr_code/data/listeFichierTxt.txt");
}

//Redirection des fichier Clean et Tok dans le bon répertoire
void redirCleanTok(){
    system("cd /home/pfr/pfr_code/traitement/");
    system("mv /home/pfr/pfr_code/traitement/*.tok /home/pfr/pfr/texte/tok;mv /home/pfr/pfr_code/traitement/*.clean /home/pfr/pfr/texte/clean");
}

//Créer un descripteur texte .xml à partir du nom du fichier, de l'identifiant et du chemin vers le répertoire tok
DESCRIPT_TXT crea_descript_txt(char * fileName,int ident, char * cheminRepertoireTok){

    DESCRIPT_TXT descripteur;

    descripteur = initDescript();
    return descripteur = creerDescript(fileName,ident,cheminRepertoireTok);
}

void ajoutListeBaseTxt(char * pathFileSRC, int ident){

    char echoList[256]={0};

    int ret = snprintf(echoList,sizeof(echoList),"echo %d %s >> /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt",ident,pathFileSRC);
    if(ret<0){
        abort();
    }
    else system(echoList);
}