#ifndef __SEQUENCE_H
#define __SEQUENCE_H

struct Sequence{
	char *sequence;
	int *numerique;
	int taille;
};
typedef struct Sequence SEQUENCE;

SEQUENCE lire_fichier(char *fichier);
int valeur(SEQUENCE lire, int truc);
int transforme(char t);
void calcul_distances(SEQUENCE lire, SEQUENCE lire2);

float min(float a, float b, float c);
float calcul_recursive_dist(int * v, int * w, int i, int j, float tableau[5][5], float ** stick);

#endif