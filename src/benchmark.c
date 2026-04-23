#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void benchmark(char *nom, int taille, int min, int max) {
 int i,val,j;
 FILE *fp;
 fp=fopen(nom,"w"); //creation du fichier
 fprintf(fp,"%d\n",taille); //enregistrement de la taille des tableaux

 //tableau croissant
 for(i=0; i<taille; i++) fprintf(fp,"%d ",i);
 fprintf(fp,"\n");

 //tableau decroissant
 for(i=0; i<taille; i++) fprintf(fp,"%d ",taille-i-1);
fprintf(fp,"\n");

 //tableau constant
 val = rand()%(max-min)+min;
 for(i=0; i<taille; i++) fprintf(fp,"%d ",val);

 //tableaux aleatoires
 for(i=0; i<500; i++) //on genere 500 tableaux
{
 fprintf(fp,"\n");
for(j=0; j<taille; j++) fprintf(fp,"%d ",rand()%(max-min)+min);
 }
 fclose(fp);
}







// MAIN : Génération complète
// =======================
int main() {
    srand(time(NULL));
    char nom[255];
    int taille;

    printf("=== Génération des fichiers de benchmark ===\n\n");

    // --- 1️⃣ Petites valeurs (0 à 50) ---
    printf("→ Génération pour petites valeurs (0 à 20)...\n");
    for (taille = 1000; taille <= 50000; taille += 1000) {
        sprintf(nom, "benchmark_petite_%d.txt", taille);
        benchmark(nom, taille, 0, 20);
    }

    // --- 2️⃣ Grandes valeurs (0 à 1 000 000) ---
    printf("\n→ Génération pour grandes valeurs (0 à 1 000 000)...\n");
    for (taille = 1000; taille <= 20000; taille += 1000) {
        sprintf(nom, "benchmark_grande_%d.txt", taille);
        benchmark(nom, taille, 0, 1000000);
    }

    printf("\n✅ Tous les fichiers ont été générés avec succès !\n");
    return 0;
}






















