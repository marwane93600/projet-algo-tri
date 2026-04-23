#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>




/*TRI À BULLE — Version 1*/
void tri_bulle_basique(int T[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - 1; j++) { // j <= s-2
            if (T[j] > T[j + 1]) {
                int tmp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = tmp;
            }
        }
    }
}


void tri_bulle_basique_v2(int T[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - 1-i; j++) { // j <= s-2
            if (T[j] > T[j + 1]) {
                int tmp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = tmp;
            }
        }
    }
}



void tri_bulle_optimise2(int T[], int s) {
    bool continuer = true;
    int i = 0;
    while (i < s - 1 && continuer) {
        continuer = false;
        for (int j = 0; j < s - 1 - i; j++) {
            if (T[j] > T[j + 1]) {
                int tmp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = tmp;
                continuer = true;
            }
        }
        i++;
    }
}






void tri_cocktail(int T[], int s) {
    bool echange = true;
    int debut = 0;
    int fin = s - 2;
    while (echange) {
        echange = false;
        for (int i = debut; i <= fin; i++) {
            if (T[i] > T[i + 1]) {
                int tmp = T[i];
                T[i] = T[i + 1];
                T[i + 1] = tmp;
                echange = true;
            }
        }
        fin--;
        for (int i = fin; i >= debut; i--) {
            if (T[i] > T[i + 1]) {
                int tmp = T[i];
                T[i] = T[i + 1];
                T[i + 1] = tmp;
                echange = true;
            }
        }
        debut++;
    }
}

void tri_selection(int T[], int s) {
    for (int i = 0; i < s - 1; i++) {
        int min = i;
        for (int j = i + 1; j < s; j++) {
            if (T[j] < T[min])
                min = j;
        }
        if (min != i) {
            int tmp = T[i];
            T[i] = T[min];
            T[min] = tmp;
        }
    }
}


void tri_insertion(int T[], int s) {
    for (int i = 1; i < s; i++) {
        int x = T[i];
        int j = i;
        while (j > 0 && T[j - 1] > x) {
            T[j] = T[j - 1];
            j--;
        }
        T[j] = x;
    }
}


void triComptage(int T[], int s) {
    int max = T[0];
    int i, j, x;

    for (i = 1; i < s; i++) {
        if (T[i] > max)
            max = T[i];
    }

    x = 0;

    int *comptage = (int *)calloc(max + 1, sizeof(int));
    
    for (i = 0; i < s; i++) {
        comptage[T[i]] = comptage[T[i]] + 1;
    }

    for (i = 0; i <= max; i++) {
        for (j = 0; j < comptage[i]; j++) {
            T[x] = i;
            x = x + 1;
        }
    }
}


void fusion(int T1[], int s1, int T2[], int s2, int T[]) {
    int i = 0, j = 0, k = 0;

    while (i < s1 && j < s2) {
        if (T1[i] < T2[j]) {
            T[k] = T1[i];
            k++;
            i++;
        } else {
            T[k] = T2[j];
            k++;
            j++;
        }
    }

    while (i < s1) {
        T[k] = T1[i];
        k++;
        i++;
    }

    while (j < s2) {
        T[k] = T2[j];
        k++;
        j++;
    }
}


void triFusion(int T[], int s) {
    if (s <= 1)
        return;

    int milieu = s / 2;
    int *T1 = (int *)malloc( sizeof(int) * milieu );
    int *T2 = (int *)malloc( sizeof(int)*(s - milieu));

    

    for (int i = 0; i < milieu; i++)
        T1[i] = T[i];
    for (int i = milieu; i < s; i++)
        T2[i - milieu] = T[i];

    triFusion(T1, milieu);
    triFusion(T2, s - milieu);

    fusion(T1, milieu, T2, s - milieu, T);

}

int partitionner(int T[], int pivot, int debut, int fin) {
    int i = debut;
    int j = fin;
    int pivotValue = T[pivot];

    // Échanger pivot avec fin
    int temp = T[pivot];
    T[pivot] = T[fin];
    T[fin] = temp;

    int indiceInsertion = debut;

    // Placer les valeurs <= pivot sur la partie gauche
    for (i = debut; i < fin; i++) {
        if (T[i] <= pivotValue) {
            temp = T[i];
            T[i] = T[indiceInsertion];
            T[indiceInsertion] = temp;
            indiceInsertion++;
        }
    }

    // Placer le pivot à sa position finale
    temp = T[indiceInsertion];
    T[indiceInsertion] = T[fin];
    T[fin] = temp;

    // Retourner l'indice du pivot
    return indiceInsertion;
}


int choix_pivot(int debut, int fin) {
    return (debut + fin) / 2;
}

void triRapide(int T[], int debut, int fin) {
    if ((fin - debut) <= 0)
        return;

    int pivot = choix_pivot(debut, fin);
    int indice_pivot = partitionner(T, pivot, debut, fin);

    triRapide(T, debut, indice_pivot - 1);
    triRapide(T, indice_pivot + 1, fin);
}


int main() {
    srand(time(NULL));

    FILE *fp_csv = fopen("resultats.csv", "w");
    fprintf(fp_csv, "tri,taille,cas,plage,temps\n");

    const char *cas_types[] = {"aleatoire", "croissant", "decroissant", "constant"};
    int nb_cas = 4;

    const char *plages[] = {"petite", "grande"};
    int nb_plages = 2;

    for (int n = 1000; n <= 50000; n += 2000) {
        for (int p = 0; p < nb_plages; p++) {
            int min = (strcmp(plages[p], "petite") == 0) ? 0 : 0;
            int max = (strcmp(plages[p], "petite") == 0) ? 20 : 1000000;

            for (int c = 0; c < nb_cas; c++) {
                int *tab = malloc(n * sizeof(int));
                int *copie = malloc(n * sizeof(int));

                // --- Génération du tableau selon le cas
                if (strcmp(cas_types[c], "aleatoire") == 0) {
                    for (int i = 0; i < n; i++) tab[i] = rand() % (max - min + 1) + min;
                } else if (strcmp(cas_types[c], "croissant") == 0) {
                    for (int i = 0; i < n; i++) tab[i] = i;
                } else if (strcmp(cas_types[c], "decroissant") == 0) {
                    for (int i = 0; i < n; i++) tab[i] = n - i;
                } else { // constant
                    int val = rand() % (max - min + 1) + min;
                    for (int i = 0; i < n; i++) tab[i] = val;
                }

                clock_t debut, fin;
                float duree;

                // macro d’exécution
                #define RUN_AND_LOG(func, nom) do { \
                    memcpy(copie, tab, n * sizeof(int)); \
                    debut = clock(); \
                    func(copie, n); \
                    fin = clock(); \
                    duree = (fin - debut) / (float)CLOCKS_PER_SEC; \
                    fprintf(fp_csv, "%s,%d,%s,%s,%.6f\n", nom, n, cas_types[c], plages[p], duree); \
                } while(0)

                RUN_AND_LOG(tri_bulle_basique, "bulle_basique");
                RUN_AND_LOG(tri_bulle_basique_v2, "bulle_basique_v2");
                RUN_AND_LOG(tri_bulle_optimise2, "bulle_optimise");
                RUN_AND_LOG(tri_cocktail, "cocktail");
                RUN_AND_LOG(tri_selection, "selection");
                RUN_AND_LOG(tri_insertion, "insertion");
                RUN_AND_LOG(triComptage, "comptage");
                RUN_AND_LOG(triFusion, "fusion");

                // Tri rapide (appel spécial)
                memcpy(copie, tab, n * sizeof(int));
                debut = clock();
                triRapide(copie, 0, n - 1);
                fin = clock();
                duree = (fin - debut) / (float)CLOCKS_PER_SEC;
                fprintf(fp_csv, "rapide,%d,%s,%s,%.6f\n", n, cas_types[c], plages[p], duree);

                free(tab);
                free(copie);
            }
        }
    }

    fclose(fp_csv);
    printf("\n✅ Données enregistrées dans resultats.csv (avec cas + plage + 9 tris)\n");
    return 0;
}
