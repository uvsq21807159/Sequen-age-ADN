#ifndef __FAMILLE_H
#define __FAMILLE_H
#include "distance.h"
#include "sequence.h"

struct Famille{
	SEQUENCE * sequence;
	int taille;
	float Dmin;
};
typedef struct Famille FAMILLE;

struct ListFamille{
	FAMILLE * famille;
	int taille;
};
typedef struct ListFamille LISTFAMILLE;

float dist_min(DISTANCE dist, float mininf, int * aUnGroupe);
int indice(DISTANCE dist, FAMILLE * fam, float min, int * aUnGroupe);
void construction(DISTANCE dist, FAMILLE * fam, int indice, int * aUnGroupe);
LISTFAMILLE touteLesSequences(DISTANCE dist);
void freeListFamille(LISTFAMILLE lf);

#endif