#include <stdio.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/tok.h"
#include <string.h>

#define CHEMIN_FICHIER_STOPWORD "/home/pfr/pfr_code/data/stop_words_french.txt"

// Création du fichier .tok, retourne 1 si elle s'est bien passée
void filtrage(char *fileName, char * pathTraitement)
{
    char mot[256] = {0};
    char pathChaine[256] = {0};
    char pathFile[256] = {0};
    int ret;
    int test;

    ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    ret = snprintf(pathChaine, sizeof(pathChaine), "%s.clean", pathFile);
    if (ret < 0) {
        abort();
    }

    creerFichTok(pathFile);

    FILE *fichier_clean = fopen(pathChaine, "r");

    if (fichier_clean != NULL)
    {
        while (fscanf(fichier_clean, "%s", mot) == 1)
        {
            enleverStopWord(mot,pathFile);
        }
    }
    fclose(fichier_clean);
}

void enleverStopWord(char * mot, char * pathFile){

    char stopWord[256] = {0};
    char ajoutMotTok[256] = {0};
    FILE *fichierStopWord = fopen(CHEMIN_FICHIER_STOPWORD, "r");
    int is_stopword = 0;

    //lecture du stopword dans le fichier stop_words_french.txt
    while (fscanf(fichierStopWord,"%s", stopWord) == 1)
    {
        if ((strcmp(mot, stopWord) == 0) || (strlen(mot) <=2))
        {
            is_stopword = 1;
            break;
        }
    }

    //ajout du mot dans le .tok si ce n'est pas un stopword
    if (is_stopword == 0)
    {
        int ret = snprintf(ajoutMotTok, sizeof(ajoutMotTok), "echo %s >> %s.tok", mot, pathFile);
        if (ret < 0)
        {
            abort();
        }
        else system(ajoutMotTok);
    }
    fclose(fichierStopWord);    
}

// On vide ou créé le fichier .tok à partir du nom du fichier
void creerFichTok(char * pathFile){

    char creerFichTok[256]={0};
    int ret = snprintf(creerFichTok, sizeof(creerFichTok), "echo '' > %s.tok", pathFile);
    if (ret < 0) {
        abort();
    }
    else system(creerFichTok);
}