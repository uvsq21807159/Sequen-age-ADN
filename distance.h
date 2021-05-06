#ifndef __DISTANCE_H
#define __DISTANCE_H

#include "sequence.h"

struct Distance{
	SEQUENCE *mesSequences;
	char **nom;
	float **Distance_Finale;
};
typedef struct Distance DISTANCE;

DISTANCE Recherche_fichiers(char *name);
void comparaison(DISTANCE *dist);
void freeDistance(DISTANCE d);

#endif