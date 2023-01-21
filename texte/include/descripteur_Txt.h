#ifndef DESCRIPTEUR_TXT_H_INCLUS
#define DESCRIPTEUR_TXT_H_INCLUS

typedef struct MOT{
    int ident;
    char mot[50];
    int nb_occur;
    struct MOT * mot_suiv;
}MOT;

typedef struct MOT * PILE;

typedef struct DESCRIPT_TXT{
    int ident;
    PILE pile_mot;
    int nb_mot_diff;
    int taille_txt;

}DESCRIPT_TXT;

MOT initMot();
MOT addMot(char * motTxt, int ident,char * fileName);
int chercheNbOccur(char * mot, char * fileName);
void creerPileMot(PILE * pileMot , char * fileName, int * nbMotDiff, int ident, char * cheminRepertoireTok);
DESCRIPT_TXT initDescript();
DESCRIPT_TXT creerDescript(char * fileName, int ident,char * cheminRepertoireTok);
void concatBaseDescript(DESCRIPT_TXT descript);
int comptageNbMot(char * fileName);

#endif
