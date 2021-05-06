#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "famille.h"

float dist_min(DISTANCE dist, float mininf, int * aUnGroupe){
	float min = 10000;
	//printf("valeur de min : %d\n", min);
	for(int a = 0; a < 20; a++){
		for(int b = a; b < 20; b++){
			if(a != b){
				if(min > dist.Distance_Finale[a][b] && dist.Distance_Finale[a][b] > mininf && aUnGroupe[a] == 0 && aUnGroupe[b]==0){
					min = dist.Distance_Finale[a][b];
				}
			}
		}
	}

	printf("Le minimum vaut: %.2f\n", min);

	return min;
}

int indice(DISTANCE dist, FAMILLE * fam, float min, int * aUnGroupe){
	int cpt = 0; int nb_fam = 0; int indice;

	fam->Dmin = min;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(dist.Distance_Finale[i][j] == fam->Dmin && aUnGroupe[j] == 0 && aUnGroupe[i] == 0){
				cpt++;
				printf("La famille contient: %s\n", dist.nom[j]);
			}
			if(nb_fam < cpt){
				nb_fam = cpt;
				indice = i;
			}
		}
		cpt = 0;
	}

	fam->taille = nb_fam + 1;

	return indice;
}

void construction(DISTANCE dist, FAMILLE * fam, int indice, int * aUnGroupe){
	fam->sequence = (SEQUENCE *) malloc(fam->taille * sizeof(SEQUENCE));
	fam->sequence[0] = dist.mesSequences[indice];
	aUnGroupe[indice] = 1;
	int add = 1;
	for(int j = 0; j < 20; j++){
		if(dist.Distance_Finale[indice][j] == fam->Dmin && aUnGroupe[j] == 0){
			fam->sequence[add] = dist.mesSequences[j];
			aUnGroupe[j] = 1;
			printf("Sa sequence respective est: %s\n", dist.mesSequences[j].sequence);
			add++;
		}
		
	}
}
//Si toute les sequence appartienne déja à une famille
int estCompler(int * aUnGroupe){
	int estcompler = 1;
	for(int i=0;i<20;i++){
		if(aUnGroupe[i] == 0){
			estcompler = 0;
		}
	}
	return estcompler;
}

LISTFAMILLE touteLesSequences(DISTANCE dist){
	LISTFAMILLE lfamille;
	lfamille.famille = (FAMILLE *) malloc(10 * sizeof(FAMILLE));
	int aUnGroupe[20] = {0};
	float minInf = 0;
	int compteurFamille = 0;
	int indicee = 0;
		while(!estCompler(aUnGroupe)){
		minInf = dist_min(dist, minInf, aUnGroupe);
		if(minInf == 10000){
			lfamille.famille[compteurFamille].sequence = (SEQUENCE *) malloc(1 * sizeof(SEQUENCE));
			for(int i =0;i<20;i++){
				if(aUnGroupe[i] == 0){
					lfamille.famille[compteurFamille].sequence[0] = dist.mesSequences[i];
					lfamille.famille[compteurFamille].taille = 1;
				}
			}
			
			compteurFamille++;
			break;
		}

		indicee = indice(dist, &lfamille.famille[compteurFamille], minInf, aUnGroupe);
		construction(dist, &lfamille.famille[compteurFamille], indicee, aUnGroupe);
		printf("Sequence S : %s\n", lfamille.famille[compteurFamille].sequence[0].sequence);
		for (int i = 0; i < 20; ++i)
		{
			printf("|%d|", aUnGroupe[i]);
		}
		compteurFamille++;
		printf("\nNombre de familles : %d\n", compteurFamille);
		printf("\n");
	}
	lfamille.taille = compteurFamille;
	return lfamille;
}

void freeListFamille(LISTFAMILLE lf){
	free(lf.famille);
}