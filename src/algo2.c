#include "algo2.h"

int algo2 (int * t, int n, int *start_max, int *end_max) {
    int somme, sommeMax = t[0];
    *start_max = 0;
    *end_max = 0;
    for(int i = 0; i < n; ++i) {
        somme = 0;
        for(int j = i; j < n; ++j) {
            somme += t[j];
            if(somme > sommeMax) {
                *start_max = i;
                *end_max = j;
                sommeMax = somme;
            }
        }
    }
    return sommeMax;
}
