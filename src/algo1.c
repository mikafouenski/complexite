#include "algo1.h"

int algo1 (int * t, int n, int *start_max, int *end_max) {
    int somme, sommeMax = t[0];
    *start_max = 0;
    *end_max = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            somme = 0;
            for(int k = i; k <= j; ++k)
                somme += t[k];
            if(somme > sommeMax) {
                *start_max = i;
                *end_max = j;
                sommeMax = somme;
            }
        }
    }
    return sommeMax;
}
