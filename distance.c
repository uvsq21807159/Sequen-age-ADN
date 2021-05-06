#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "distance.h"

DISTANCE Recherche_fichiers(char *name){
	DISTANCE dist;
	DIR* D;
	D = opendir(name);

	dist.nom = (char **)malloc(20 * sizeof(char *)+1);
	for(int j = 0; j < 20; j++){
		dist.nom[j] = (char *)malloc(24 * sizeof(char)+1);
	}

	if(D == NULL)
		exit(1);
	else
		printf("Ouverture du dossier. Le dossier à bien été ouvert.\n");

	struct dirent *sd;
	sd = readdir(D);
	int i = 0;

	while(sd != NULL && i < 20){
		if(strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0){
			sprintf(dist.nom[i], "%s/%s", name, sd->d_name);
			i++;
		}
		sd = readdir(D);
	}

	closedir(D);

	return dist;
}



void comparaison(DISTANCE *dist){

	float tableau[5][5] = {{0, 2, 1, 2, 1.5}, {2, 0, 2, 1, 1.5}, {1, 2, 0, 2, 1.5}, {2, 1, 2, 0, 1.5}, {1.5, 1.5, 1.5, 1.5, 0}};
	SEQUENCE lire, lire2;
	float **stick;
	dist->mesSequences = (SEQUENCE *) malloc(20 * sizeof(SEQUENCE));
	dist->Distance_Finale = (float **) malloc(20 * sizeof(float *));
	for(int i = 0; i < 20; i++){
		dist->Distance_Finale[i] = (float *) malloc(20 * sizeof(float));
	}
	int a, b, compteur = 0;
	for(a = 0; a < 20; a++){

		lire = lire_fichier(dist->nom[a]);
		dist->mesSequences[a] = lire;
		for(b = a; b < 20; b++){
			lire2 = lire_fichier(dist->nom[b]);
			stick = (float**) malloc(lire.taille * sizeof (float*) + 1);

			for(int i=0; i<lire.taille; i++)
			{
				stick[i] = (float *) malloc(lire2.taille * sizeof (float) + 1); //Allocation du stick
				for(int j=0; j<lire2.taille; j++){
    				stick[i][j] = 0; //Initialisation de toutes les valeures à 0
    			}
			}
			if(a == b){
				dist->Distance_Finale[a][b] = 0;
			}
			else {
				dist->Distance_Finale[a][b] = calcul_recursive_dist(lire.numerique, lire2.numerique, lire.taille-1, lire2.taille-1, tableau, stick);
				//printf("La distance finale est: %.2f\n", dist->Distance_Finale[a][b]);
				compteur++;
			}
			for(int i=0;i<lire.taille;i++){
				free(stick[i]);
			}
			free(stick);
		}
	}

	printf("Après calcul, nous avons fait: %d comparaisons.\n", compteur);
	printf("Les caractéristiques de nos familles sont ci-dessous.\n");
	printf("\n");

}

void freeDistance(DISTANCE d){
	for (int i = 0; i < 20; i++)
	{
		free(d.mesSequences[i].sequence);
		free(d.mesSequences[i].numerique);
	}
	for(int i=0;i<20;i++){
		free(d.nom[i]);
	}
	for(int i=0;i<20;i++){
		free(d.Distance_Finale[i]);
	}
	free(d.Distance_Finale);
	free(d.nom);
}

