#include "alignement.h"

char transformeInverse(int t){ //Fonction pour renvoyer un char selon la valeur trouvé
	if(t == 0)
		return 'A';
	if(t == 1)
		return 'C';
	if(t == 2)
		return 'G';
	if(t == 3)
		return 'T';
	else
		return '-';
}


SEQUENCE seqConsensus(FAMILLE fam){
	SEQUENCE consensus ;
	int tab[4] = {0};
	int maxLength = fam.sequence[0].taille;
	for(int i = 1; i<fam.taille; i++){
		if(fam.sequence[i].taille > maxLength){
			maxLength = fam.sequence[i].taille;
		}
	}
	consensus.taille = maxLength;
	consensus.sequence = (char *) malloc(maxLength * sizeof(char) + 1 );
	consensus.numerique = (int *) malloc(maxLength * sizeof(int) + 1 );
	int maxRepIndice = 0;
	int maxRep = 0;
	for(int i=0; i<maxLength; i++){
		
		for(int j=0; j<fam.taille; j++){
			if(fam.sequence[j].taille > i) tab[fam.sequence[j].numerique[i]]++;
		}

		for(int y=0; y<4; y++){
			if(maxRep < tab[y]){
				maxRep = tab[y];
				maxRepIndice = y;
			}
		}
		consensus.numerique[i] = maxRepIndice;
		consensus.sequence[i] = transformeInverse(maxRepIndice);
		maxRep = 0;
		maxRepIndice = 0;
		for(int w=0;w<4;w++){
			tab[w] = 0;
		}
	}
	return consensus;
}

ALLSEQUENCECONSENSUS allseqConsensus(LISTFAMILLE lfamille){
	ALLSEQUENCECONSENSUS asc;
	asc.seq = (SEQUENCE *) malloc(lfamille.taille * sizeof(SEQUENCE));
	for(int i=0; i<lfamille.taille; i++){
		asc.seq[i] = seqConsensus(lfamille.famille[i]);
	}
	asc.taille = lfamille.taille;
	return asc;
}