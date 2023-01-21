#ifndef PILES2_H
#define PILES2_H


/*Pile1*/

typedef struct s_cel1{
    int fich;
    int nb;
    struct s_cel1 * suiv;
} Cel1;

typedef Cel1 * Table;

/*Pile2*/

typedef struct s_cel2{
    char mot [50];
    Table table;
    struct s_cel2 * motTableSuiv;
} Cel2;

typedef Cel2 * MotTable;

Table initT();
Table addT(Table p, int fich, int nb);
void affT(Table p);
MotTable initM();
MotTable addM(MotTable p, char * MotTable);
MotTable add(MotTable p, int nb, char * MotTable, int fich);
void aff(MotTable p);

#endif 