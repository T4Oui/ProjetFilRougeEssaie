#include <stdio.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/clean.h"

// Ecrire le chemin du fichier sans l'extension .xml
void nettoyage(char *fileName, char * pathStockageFich, char * pathTraitement)
{
    //initialisation du chemin du fichier dans le répertoire de travail
    char pathFile[256]={0};
    int ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    copieRepTravail(pathStockageFich, fileName, pathFile);
    enleverBalise(pathFile);
    changerMajMin(pathFile);
    supprNPremLig(3,pathFile);
    supprApostrophe(pathFile);
    supprChiffre(pathFile);
    supprPonctu(pathFile);
    supprTiret(pathFile);
    supprXml(pathFile);
}

// copier le fichier .xml du répertoire de stockage vers le répertoire de travail
void copieRepTravail(char * pathStockageFich, char *fileName, char * pathFile){

    char copieRepTravail[256] = {0};
    int ret = snprintf(copieRepTravail, sizeof(copieRepTravail), "cp %s/%s.xml %s.xml",pathStockageFich, fileName, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(copieRepTravail);
    }
}

// enlever les balises dans ls fichier .xml
void enleverBalise(char * pathFile){

    char enleverBalise[256] = {0};
    int ret = snprintf(enleverBalise, sizeof(enleverBalise), "sed -i -e 's/<[^>]*>//g' %s.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(enleverBalise);
    }
}

// Changer les majuscules en minuscules
void changerMajMin(char * pathFile){
    char changeMajMin[256] = {0};
    int ret = snprintf(changeMajMin, sizeof(changeMajMin), "cat %s.xml | tr A-Z a-z > %sV2.xml", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(changeMajMin);
    }
}

// Supprimer les n première lignes (car lignes vides)
void supprNPremLig(int n, char * pathFile){
    char supprPremLig[256] = {0};
    int ret = snprintf(supprPremLig, sizeof(supprPremLig), "sed -i '1,%dd' %sV2.xml",n, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprPremLig);
    }
}

// suppression ' et "
void supprApostrophe(char * pathFile){
    char supprApostrophe[256] = {0}; 
    system("chmod +x /home/pfr/pfr_code/texte/src/remove_apostrophe.sh");
    int ret = snprintf(supprApostrophe, sizeof(supprApostrophe), "/home/pfr/pfr_code/texte/src/remove_apostrophe.sh %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprApostrophe);
    }
}

// Supprimer les chiffres
void supprChiffre(char * pathFile){
    char supprChiffre[256] = {0};
    int ret = snprintf(supprChiffre, sizeof(supprChiffre), "sed -i -e 's/[0-9]//g' %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprChiffre);
    }
}

// Remplace de la ponctuation et des symboles (hors -) par des " "
void supprPonctu(char * pathFile){
    char supprPonctu[256] = {0};
    int ret = snprintf(supprPonctu, sizeof(supprPonctu), "sed -i -e 's/[.,;:?!()%%_<>/$€]/ /g' %sV2.xml", pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprPonctu);
}

// Suppression des "-" et création du fichier .clean
void supprTiret(char * pathFile){
    char supprTiret[256] = {0};
    int ret = snprintf(supprTiret, sizeof(supprTiret), "sed 's/-/ /g' %sV2.xml > %s.clean", pathFile, pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprTiret);
}

// Suppression des fichiers .xml
void supprXml(char * pathFile){
    char supprXmlV2[256] = {0};
    int ret = snprintf(supprXmlV2, sizeof(supprXmlV2), "rm %sV2.xml;rm %s.xml ", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprXmlV2);
    }
}