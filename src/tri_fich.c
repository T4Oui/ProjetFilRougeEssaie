#include <stdio.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/include/tri_fich.h"

//creation de l'environnement de travail (dossier)

void crea_dossiers(){
    system("cd ~; mkdir pfr");
    system("mkdir ~/pfr/texte");
    system("mkdir ~/pfr/texte/fich_textes");
    system("mkdir ~/pfr/texte/clean");
    system("mkdir ~/pfr/texte/tok");
    system("mkdir ~/pfr/texte/descripteurs_textes");
    system("mkdir ~/pfr/texte/recherche_texte");
    system("mkdir ~/pfr/son");
    system("mkdir ~/pfr/son/fich_sons");
    system("mkdir ~/pfr/son/descripteurs_sons");
    system("mkdir ~/pfr/son/recherche_texte");
    system("mkdir ~/pfr/image");
    system("mkdir ~/pfr/image/fich_images/txt");
    system("mkdir ~/pfr/image/fich_images");
    system("mkdir ~/pfr/image/descripteurs_images");
    system("mkdir ~/pfr/image/recherche_texte");
}

//gestion des fichiers avant l'indexation
//chemin: chemin du dossier contenant les fichiers pour l'indexation
void tri_texte(char * chemin){ 
    char * chaine;
    FILE * text = fopen("texte.txt","r");
    while(fscanf(text,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s ~/pfr/texte/fich_textes",chemin,chaine);
        system(chaine1);
    }
    fclose(text);
}

void tri_son(char * chemin){
    char * chaine;
    FILE * so = fopen("son.txt","r");
    while(fscanf(so,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s ~/pfr/son/fich_sons",chemin,chaine);
        system(chaine1);
    }
    fclose(so);
}

void tri_image(char * chemin){
    char * chaine;
    FILE * imag = fopen("image.txt","r");
    while(fscanf(imag,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s ~/pfr/image/fich_images",chemin,chaine);
        system(chaine1);
    }
    fclose(imag);
    imag = fopen("imagetxt.txt","r");
    while(fscanf(imag,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s ~/pfr/image/fich_images/txt",chemin,chaine);
        system(chaine1);
    }
    fclose(imag);
}

void tri_fich(char * chemin){ //tri les fichiers avant l'indexation (son,texte,image)
    char chaine[256]={0};
    snprintf(chaine,256,"ls %s| grep '.xml' >texte.txt",chemin);
    system(chaine);
    snprintf(chaine,256,"ls %s| grep '.wav' >son.txt",chemin);
    system(chaine);
    snprintf(chaine,256,"ls %s| grep '.bin' >>son.txt",chemin);
    system(chaine);
    snprintf(chaine,256,"ls %s| grep '.jpg' >image.txt",chemin);
    system(chaine);
    snprintf(chaine,256,"ls %s| grep '.bmp' >>image.txt",chemin);
    system(chaine);
    snprintf(chaine,256,"ls %s| grep '.txt' >imagetxt.txt",chemin);
    system(chaine);
    tri_texte(chemin);
    tri_son(chemin); 
    tri_image(chemin);
    system("rm texte.txt son.txt image.txt imagetxt.txt");
}



