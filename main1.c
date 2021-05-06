#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "distance.h"

int main(){


	DISTANCE dist = Recherche_fichiers("sequences_ADN");
	comparaison(&dist);
	for(int i=0;i<20;i++){
		printf("La chaine d'indice %d est: %s. Sa taille est de %d caractères.\n", i, dist.mesSequences[i].sequence, dist.mesSequences[i].taille);
	}
	freeDistance(dist);
	return 0;
}