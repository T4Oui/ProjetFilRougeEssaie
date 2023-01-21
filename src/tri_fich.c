#include <stdio.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/include/tri_fich.h"

//creation de l'environnement de travail (dossier)

void crea_dossiers(){
    system("mkdir /home/pfr/pfr");
    system("mkdir /home/pfr/pfr/texte");
    system("mkdir /home/pfr/pfr/texte/fich_textes");
    system("mkdir /home/pfr/pfr/texte/clean");
    system("mkdir /home/pfr/pfr/texte/tok");
    system("mkdir /home/pfr/pfr/texte/descripteurs_textes");
    system("mkdir /home/pfr/pfr/texte/recherche_texte");
    system("mkdir /home/pfr/pfr/son");
    system("mkdir /home/pfr/pfr/son/fich_sons");
    system("mkdir /home/pfr/pfr/son/descripteurs_sons");
    system("mkdir /home/pfr/pfr/son/recherche_son");
    system("mkdir /home/pfr/pfr/image");
    system("mkdir /home/pfr/pfr/image/fich_images");
    system("mkdir /home/pfr/pfr/image/fich_images/txt");
    system("mkdir /home/pfr/pfr/image/descripteurs_images");
    system("mkdir /home/pfr/pfr/image/recherche_image");
}

//gestion des fichiers avant l'indexation
//chemin: chemin du dossier contenant les fichiers pour l'indexation
void tri_texte(char * chemin){ 
    char chaine[100];
    FILE * text = fopen("texte.txt","r");
    while(fscanf(text,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s /home/pfr/pfr/texte/fich_textes",chemin,chaine);
        system(chaine1);
    }
    fclose(text);
}

void tri_son(char * chemin){
    char chaine[100];
    FILE * so = fopen("son.txt","r");
    while(fscanf(so,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s /home/pfr/pfr/son/fich_sons",chemin,chaine);
        system(chaine1);
    }
    fclose(so);
}

void tri_image(char * chemin){
    char chaine[100];
    FILE * imag = fopen("image.txt","r");
    while(fscanf(imag,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s /home/pfr/pfr/image/fich_images",chemin,chaine); //JPG
        system(chaine1);
    }
    fclose(imag);
    imag = fopen("imagetxt.txt","r");
    while(fscanf(imag,"%s",chaine)==1){
        char chaine1[256]={0};
        snprintf(chaine1,256,"cp %s/%s /home/pfr/pfr/image/fich_images/txt",chemin,chaine); //txt
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
    //system("rm texte.txt son.txt image.txt imagetxt.txt");
}



