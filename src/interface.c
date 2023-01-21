#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interface.h"



#define mdp "feur"

//ouvrir fichier image : display <image>
//ouvrir fichier txt : xdg-open <filename>

void affMP()
{
    printf("\n\n\n    ** Menu Principal **\nTaper 1: mode Utilisateur\nTaper 2: mode Administrateur\n");
}

void affUtil()
{
    printf("\n  ** Mode Utilisateur **\nQue voulez-vous chercher?\n1: Un texte\n2: Une image\n3: Un son\n0: revenir au menu principal\n");
}

void affrechText()
{
    printf("\n  ** Recherche Texte **\n1: par mot clef\n2: par ressemblance avec un autre fichier\n0: revenir au menu principal\n");
}

void affrechImag()
{
    printf("\n  ** Recherche Image **\n1: donner les composantes RGB\n2: ressemblance avec une autre image\n0: revenir au menu principal\n");
}

void affrechSon()
{
    printf("\n  ** Recherche Son **\nTaper le chemin du son que vous voulez comparer:\n");
}

void affrechTextMotClef()
{
    printf("\n  ** Recherche Texte par Mot Clef **\nTaper le mot clef:\n");
}

void affrechTextText()
{
    printf("\n  ** Recherche Texte par ressemblance **\nTaper le chemin du texte que vous voulez comprarer:\n");
}

void affrechImagRGB()
{
    printf("\n  ** Recherche Image par composantes RGB **\n");
}

void affrechImagImag()
{
    printf("\n  ** Recherche Image par ressemblance avec une image **\n1: une image en noir et blanc\n2: une image couleur\n");
}

void affrechImagImagNB()
{
    printf("\n  ** Recherche Image par ressemblance avec une image NetB **\nTaper le chemin de l'image que vous voulez comparer:\n");
}

void affrechImagImagCoul()
{
    printf("\n  ** Recherche Image par ressemblance avec une image Couleur **\nTaper le chemin de l'image que vous voulez comparer:\n");
}

void affresultMotClef(MotTable p,char *mot)
{
    printf("\n  ** Resultats trouvés pour la recherche '%s' **\n", mot);
    rech_MC(p,mot);
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultTexte(char * chemin)
{
    printf("\n  ** Resultats trouvés pour la comparaison avec un fichier **\n");
    recherche_comparaison_texte(chemin,35); //35?
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultRGB(int R, int G, int B)
{
    printf("\n  ** Resultats trouvés pour la recherche grâce aux composantes R:'%d', G:'%d', B:'%d' **", R, G, B);
    // recherche RGB
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultImageNB(){
    printf("\n  ** Resultats trouvés pour la comparaison avec une image NetB **\n");
    // recherche image NB
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultImageCoul(){
    printf("\n  ** Resultats trouvés pour la comparaison avec une image Couleur **\n");
    // recherche image Coul
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultSon()
{
    printf("\n  ** Resultats trouvés pour la comparaison avec un fichier **\n");
    // recherche son
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affAdm()
{
    printf("\n  ** Mode Administrateur **\n       Mot de passe?\n");
}

void affmdp()
{
    printf("\n  ** Mode Administrateur **\nMot de passe erroné    Mot de passe?\n(Taper 0: revenir au menu principal)\n");
}

void affmodeAdm()
{
    printf("\n  ** Mode Administrateur **\n1: modifier les configurations\n2: visualiser le contenu des descripteurs\n3: effectuer une recherche\n4: faire l'indexation\n0: revenir au menu principal\n");
}

void affconfig()
{
    int nb_lig;
    int nb_modif;
    printf("\n  ** Modifier les configurations **\n\n");
    system("cat /home/pfr/pfr_code/config.txt");
    printf("\n\n Que voulez vous modifier ?\nrentrer le numéro de ligne (début à 1) puis la valeur à mettre à la place\n");
    scanf("%d",&nb_lig);
    scanf("%d",&nb_modif);

    printf("\n  ** fichier mofifié **\n");
    system("cat /home/pfr/pfr_code/config.txt");
}

void affvisudescripteurs()
{
    printf("\n  ** Visualiser le contenu des descripteurs **\n1: texte\n2: image\n3: son\n0: revenir au mode administrateur\n");
}

void affvisudescText()
{
    printf("\n  ** Descripteurs texte **\n");
    printf("\n**** Descripteurs utiles pour la comparaison ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt");
    printf("\n**** Descripteurs utiles pour la recherche mot clef ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt");
    printf("\n**** Identificateur des fichiers ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt");
}

void affvisudescImag()
{
    printf("\n  ** Descripteurs image **\n");
    // afficher descripteurs
}

void affvisudescSon()
{
    printf("\n  ** Descripteurs son **\n");
    // afficher descripteurs
}

void indexation(){
    char chemin [250];
    //supprimer les fichiers avant de faire l'indexation //A FAIRE
    printf("\n  ** Indexation **\n Saisir le chemin des fichiers que vous voulez indexer:\n");
    scanf("%s",chemin);
    tri_fich(chemin);
    //indexation texte
    printf("\n***** indexation texte *****\n");
    indexation_texte(); //ou est la pile? 
    //indexation image
    printf("\n***** indexation image *****\n");
    indexation_image();
    //indexation son
    printf("\n***** indexation son *****\n");
}

void modeUtil()
{
    int choix;
    affUtil(); // menu utilisateur
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        affrechText(); // menu recherche texte
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            char mot[256];
            affrechTextMotClef(); // menu recherche texte - mot clef
            scanf("%s", mot);
            MotTable p=NULL;
            affresultMotClef(p,mot);
            scanf("%d", &choix);
            open_fich();
            break;
        case 2:
            char chemin[150];
            char chaine[256];
            affrechTextText(); // menu recherche texte - texte
            scanf("%s", chemin);
            snprintf(chaine,256,"cp %s.xml /home/pfr/pfr/texte/recherche_texte",chemin);
            system(chaine);
            affresultTexte(chemin);
            scanf("%d", &choix);
            // open fichier
            break;
        case 0:
            interface();
            break;
        default:
            break;
        }
        break;
    case 2:
        affrechImag();
        scanf("%d",&choix);
        switch (choix)
        {
        case 1:
            int R, G, B;
            affrechImagRGB(); // menu recherche image - RGB
            printf("Composante R?   ");
            scanf("%d", &R);
            printf("Composante G?   ");
            scanf("%d", &G);
            printf("Composante B?   ");
            scanf("%d", &B);
            affresultRGB(R,G,B);
            scanf("%d", &choix);
            // open fichier
            break;
        case 2:
            char chemin[150];
            char chaine[256];
            affrechImagImag(); // menu recherche image - image
            scanf("%d",&choix);
            switch (choix)
            {
            case 1:
                affrechImagImagNB(); // menu recherche image - image - NB
                scanf("%s", chemin);
                snprintf(chaine,256,"cp %s /home/pfr/pfr/texte/recherche_image",chemin);
                system(chaine);
                affresultImageNB();
                scanf("%d", &choix);
                // open fichier
                break;
            case 2:
                affrechImagImagCoul(); // menu recherche image - image - couleur
                scanf("%s", chemin);
                snprintf(chaine,256,"cp %s /home/pfr/pfr/texte/recherche_image",chemin);
                system(chaine);
                affresultImageCoul();
                scanf("%d", &choix);
                // open fichier
                break;
            default:
                break;
            }
            break;
        case 0:
            interface();
            break;
        default:
            break;
        }
        break;
    case 3:
        char chemin[150];
        char chaine[256];
        affrechSon();
        scanf("%s", chemin);
        snprintf(chaine,256,"cp %s /home/pfr/pfr/texte/recherche_son",chemin);
        system(chaine);
        affresultSon();
        scanf("%d", &choix);
        // open fichier
        break;
    case 0:
        interface();
        break;
    default:
        break;
    }
}

void modeAdm()
{
    int choix;
    affmodeAdm();
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        affconfig();
        break;
    case 2:
        affvisudescripteurs();
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            affvisudescText();
            break;
        case 2:
            affvisudescImag();
            break;
        case 3:
            affvisudescSon();
            break;
        case 0:
            modeAdm();
            break;
        default:
            break;
        }
        break;
    case 3:
        modeUtil();
        break;
    case 4:
            indexation();
            modeAdm();
            break;
    case 0:
        interface();
        break;
    default:
        break;
    }
}

void interface()
{
    int choix;
    affMP(); // menu principal
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        modeUtil();
        break;
    case 2:
        char m[256];
        affAdm();//gestion du mot de passe
        scanf("%s", m);
        if (m == 0)
        {
            interface();
        }
        while (strcmp(m, mdp) != 0)
        {
            affmdp();
            scanf("%s", m);
        }
        modeAdm();
        break;
    default:
        break;
    }
}