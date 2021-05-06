#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "distance.h"
#include "famille.h"

int main(){


	DISTANCE dist = Recherche_fichiers("sequences_ADN");
	comparaison(&dist);
	
	LISTFAMILLE lfamille = touteLesSequences(dist);
	printf("Il y a donc %d familles au total.\n", lfamille.taille);
	for(int i = 0; i < lfamille.taille;i++){
		printf("Famille %d :\n", i);
		for(int j=0; j < lfamille.famille[i].taille; j++){
			printf("sequence %d : %s\n", j, lfamille.famille[i].sequence[j].sequence);
		}
		
	}
	freeDistance(dist);
	freeListFamille(lfamille);
	return 0;
}