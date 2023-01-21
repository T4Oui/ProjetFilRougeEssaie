#ifndef TOK_H_INCLUS
#define TOK_H_INCLUS

void filtrage (char * fileName, char * pathTraitement);

void enleverStopWord(char * mot, char * pathFile);
void creerFichTok(char * pathFile);
#endif