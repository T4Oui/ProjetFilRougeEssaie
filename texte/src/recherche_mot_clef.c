#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/recherche_mot_clef.h"



void rech_MC(MotTable p,char * mot){
    system("echo >/home/pfr/pfr_code/data/rech_mot_clef.txt");
    MotTable paux=p;
    char chaine[210];
    int id_courant;
    int id_fich;
    int nb;
    char chemin[100] ={0};
    while(paux!=NULL){
        if(strcmp(paux->mot,mot)==0){
            Table taux=paux->table;
            Table M_max=taux;
            int id=0;
            while (taux!=NULL){
                snprintf(chaine, 150,"echo '%d %d'>> /home/pfr/pfr_code/data/rech_mot_clef.txt", taux->fich, taux->nb);
                system(chaine);
                taux=taux->suiv;
                id++;
            }
            snprintf(chaine,270,"sort -k 2 -nr /home/pfr/pfr_code/data/rech_mot_clef.txt > /home/pfr/pfr_code/data/rech_mot_clef_tri.txt");
            system(chaine);
            FILE *rech = fopen("/home/pfr/pfr_code/data/rech_mot_clef_tri.txt","r");
            while (fscanf(rech,"%d",&id_fich)==1){
                fscanf(rech,"%d",&nb);
                FILE *base = fopen("/home/pfr/pfr/texte/descripteurs_textes/liste_base_texte.txt", "r");
                while (fscanf(base,"%d",&id_courant) == 1){
                    fscanf(base,"%s",chemin);
                    if(id_courant==id_fich){
                        printf("%s %d\n",chemin,nb);
                    }
                }
                fclose(base);
                //snprintf(chaine,250,"sed -e 's/^%d/$chemin/' ../../data/rech_mot_clef.txt >> ../../data/rech_mot_clef_chemin.txt" ,id_courant);
                //system(chaine);
            }
            fclose(rech);
            //system("cat /home/pfr/pfr_code/data/rech_mot_clef_tri.txt");
            break;
        }
        paux=paux->motTableSuiv;
    }
}

void open_fich(){
    int ident;
    int id_courant;
    char chemin[150] ={0};
    char chaine1[150] = {0};
    char chaine[150] = {0};
    FILE * rech = fopen("/home/pfr/pfr_code/data/rech_mot_clef_tri.txt","r");
    fscanf(rech,"%d",&ident);
    fclose(rech);
    FILE *fich = fopen("/home/pfr/pfr/texte/descripteurs_textes/liste_base_texte.txt", "r");
    while (fscanf(fich,"%d",&id_courant) == 1){
        fscanf(fich,"%s",chemin);
        if(id_courant==ident){
            snprintf(chaine,220,"xdg-open %s",chemin);
            system(chaine);
            break;
        }
    }
    fclose(fich);
}
/*
int main(){
    system("echo '' > /home/pfr/pfr_code/data/table_descripteur_texte.txt");
    char fichier[150];
    Mot p = initM();
    int ident = 1;
    system("ls /home/pfr/pfr/texte/tok | grep '.tok' | sed -e 's/.tok//' > /home/pfr/pfr_code/data/nom_tok.txt");
    FILE *n_tok = fopen("/home/pfr/pfr_code/data/nom_tok.txt", "r");
    while (fscanf(n_tok,"%s", fichier) == 1)
    {
        p = table(p, ident, fichier);
        ident++;
    }
    fclose(n_tok);
    rech_MC(p,"le");
    open_fich1();
}*/