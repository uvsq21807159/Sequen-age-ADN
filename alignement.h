#ifndef __ALIGNEMENT_H
#define __ALIGNEMENT_H
#include "famille.h"


struct AllSequenceConsensus{
	SEQUENCE * seq;
	int taille;
};
typedef struct AllSequenceConsensus ALLSEQUENCECONSENSUS;

char transformeInverse(int t);
SEQUENCE seqConsensus(FAMILLE fam);
ALLSEQUENCECONSENSUS allseqConsensus(LISTFAMILLE lfamille);

#endif