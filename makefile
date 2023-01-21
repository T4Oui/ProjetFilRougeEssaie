testgen : ./src/interface.c ./texte/src/recherche_mot_clef.c ./include/interface.h ./texte/include/recherche_mot_clef.h ./texte/src/tok.c ./texte/include/tok.h ./texte/src/clean.c ./texte/include/tok.h ./texte/src/tok.c ./texte/src/indexation_texte.c ./texte/src/indexation_texte.c ./texte/src/descripteur_Txt.c ./texte/include/descripteur_Txt.h ./texte/src/pile_dynamique.c ./texte/include/pile_dynamique.h ./src/tri_fich.c ./include/tri_fich.h ./src/main.c ./texte/src/recherche_texte.c ./texte/include/recherche_texte.h ./texte/include/table_index.h ./texte/src/table_index.c ./texte/include/piles2.h ./texte/src/piles2.c
	gcc -c ./src/tri_fich.c
	gcc -c ./texte/src/indexation_texte.c 
	gcc -c ./texte/src/tok.c
	gcc -c ./texte/src/clean.c
	gcc -c ./texte/src/descripteur_Txt.c
	gcc -c ./texte/src/pile_dynamique.c
	gcc -c ./src/main.c
	gcc -c ./texte/src/recherche_texte.c
	gcc -c ./texte/src/piles2.c
	gcc -c ./texte/src/table_index.c
	gcc -c ./src/interface.c
	gcc -c ./texte/src/recherche_mot_clef.c
	gcc -o testgen.out interface.o recherche_mot_clef.o indexation_texte.o clean.o tok.o descripteur_Txt.o pile_dynamique.o tri_fich.o main.o recherche_texte.o table_index.o piles2.o
	./testgen.out
