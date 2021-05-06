#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "distance.h"
#include "famille.h"
#include "alignement.h"

int main(){


	DISTANCE dist = Recherche_fichiers("sequences_ADN");
	comparaison(&dist);
	
	LISTFAMILLE lfamille = touteLesSequences(dist);
	
	printf("\n");
	printf("Partie 3 :\n");
	ALLSEQUENCECONSENSUS s = allseqConsensus(lfamille);
	for(int i=0;i<lfamille.taille;i++){
		printf("\n");
		printf("Famille %d:\n", i);
		for(int j=0;j<lfamille.famille[i].taille;j++){
			printf("sequence %d : %s\n",j, lfamille.famille[i].sequence[j].sequence);
		}
		printf("Sequence consensus: %s\n", s.seq[i].sequence);
	}
	freeDistance(dist);
	freeListFamille(lfamille);
	return 0;
}