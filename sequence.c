#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sequence.h"
#include <dirent.h>

int transforme(char t){ //Fonction pour renvoyer une valeur selon le char trouvé pour la distance 2
	if(t == 'A')
		return 0;
	if(t == 'C')
		return 1;
	if(t == 'G')
		return 2;
	if(t == 'T')
		return 3;
	else
		return 4;
}


SEQUENCE lire_fichier(char *fichier)
{
	SEQUENCE seq;
	seq.taille = 0;
	int c;
	FILE *F = fopen(fichier, "r");
	if (F == NULL)
	{
		fprintf(stderr, "Erreur. Impossible d'ouvrir le fichier\n"); //Message d'erreur
		exit(1);
	}

	while((c = fgetc(F)) != EOF)
	{
		if(c != '\n'){
			seq.taille += 1; //Compteur de la taille de la chaine de caractère
		}
	}
	seq.sequence = malloc(seq.taille * sizeof(char) + 1);
	seq.numerique = malloc(seq.taille * sizeof(int) + 1);
	
	fseek(F,0,SEEK_SET);

	for(int i = 0; i<seq.taille; i++){
		seq.sequence[i] = 0;
	}

	int cpt = 0;
	while((c = fgetc(F)) != EOF)
	{
		if(c != '\n'){
			seq.sequence[cpt] = c;
			seq.numerique[cpt] = transforme(seq.sequence[cpt]);
			cpt++; //Lecture des caractères
		}
	}
	seq.sequence[cpt] = '\0';

	fclose(F);
	return seq;
}

int valeur(SEQUENCE truc, int cpt){ //Fonction pour renvoyer une valeur selon le char trouvé pour la distance 1
	if(truc.sequence[cpt] == 'A')
		return 0;
	if(truc.sequence[cpt] == 'C')
		return 1;
	if(truc.sequence[cpt] == 'G')
		return 2;
	if(truc.sequence[cpt] == 'T')
		return 3;
	else
		return 4;
}

void calcul_distances(SEQUENCE lire, SEQUENCE lire2) //Distance 1 (Calcul des distances de manière standart)
{
	int tableau[4][4] = {{0, 2, 1, 2}, {2, 0, 2, 1}, {1, 2, 0, 2}, {2, 1, 2, 0}}; //Tableau stockant les valeurs possibles de distances

	int min, max;
	if(lire.taille < lire2.taille){
		min = lire.taille;
		max = lire2.taille;
	}
	else{
		min = lire2.taille;
		max = lire.taille; //Chaines min et max
	}
	
	float dist_blanc = (max - min)*1.5; //Calcul distance avec blanc

	float DF = 0;
	for(int cpt = 0; cpt<min; cpt++){ //Distance entre chaque caractères
		DF += tableau[valeur(lire, cpt)][valeur(lire2, cpt)];
	}
	DF += dist_blanc;
	printf("Distance: %.2f\n", DF); //Distance finale première méthode

}

float min(float a, float b, float c){ //Calcul du min
	if(a==b && a==c)
		return a;
	if(a<b && a<c)
		return a;
	if(b<a && b<c)
		return b;
	else
		return c;
}

//d'apres les mesure de performance, utiliser directement des nombres 
//sans passer par le transforme, accelere de 43% l'execution
float calcul_recursive_dist(int * v, int * w, int i, int j, float tableau[5][5], float ** stick) {
	if(i<0 || j<0)
		return 0;

	if(stick[i][j] != 0){
		return stick[i][j];
	}


	if((i == 0 && j == 0))
		stick[i][j] = tableau[v[i]][w[j]];
	else if(i == 1 && j == 0)
		stick[i][j] = calcul_recursive_dist(v,w,i-1,j,tableau,stick) + tableau[4][w[j]];
	else if(i == 0 && j == 1)
		stick[i][j] = calcul_recursive_dist(v,w,i,j-1,tableau,stick) + tableau[v[i]][4];
	else {
		stick[i][j] = min(
				calcul_recursive_dist(v,w,i-1,j-1,tableau,stick) + tableau[v[i]][w[j]],
				calcul_recursive_dist(v,w,i,j-1,tableau,stick) + tableau[v[i]][4],
				calcul_recursive_dist(v,w,i-1,j,tableau,stick) + tableau[4][w[j]]
				);
	}
	return stick[i][j];
}
