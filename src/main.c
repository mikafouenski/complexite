#include "algo1.h"
#include "algo2.h"
#include "algo3.h"
#include "algo4.h"
#include "utils.h"

#define nb_sizes 8

int sizes[nb_sizes] = {100, 500, 1000, 10000, 100000, 1000000, 10000000, 100000000};
typedef int(*Functions[4])(int*,int, int*, int*);
Functions algos = {algo1, algo2, algo3, algo4};

int sonNumber;
int sonSizeTest;
int debug = 0;

void random_perso(int* t, int n) {
    for(int i = 0 ; i < n ; ++i)
        t[i] = (rand() % (100 * 2) - 100);
}

void capt_alarm(int sig) {
    printf("Algo%d, taille:%d temps:>60.000000\n", sonNumber + 1, sizes[sonSizeTest]);
    exit(0);
}

void son (int * t, int n, int algo) {
    clock_t debut, fin;
    sonNumber = algo;
    sonSizeTest = n;
    signal(SIGALRM, capt_alarm);
    alarm(60);
    int start_max, end_max, sommeMax;
    debut = clock();
    sommeMax = (algos[algo])(t, sizes[n], &start_max, &end_max);
    fin = clock();
    double exec = (double) (fin - debut) / CLOCKS_PER_SEC;
    printf("Algo%d, taille:%d temps:%0.6lf\n", algo + 1, sizes[n], exec);
    if(debug)
        printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
}

int main(int argc, char **argv) {
    int flag_a = 0, flag_b = 0, flag_c = 0, flag_d = 0, flag_t = 0;
    int debut = 1;
    if (argc < 2) {
        printf("Please give an array to test...\n");
        return 1;
    }

    if (argv[1][0] == '-') {
        if (argv[1][1] == 'a') {
            flag_a = 1;
            debut++;
        } else if (argv[1][1] == 'b') {
            flag_b = 1;
            debut++;
        } else if (argv[1][1] == 'c') {
            flag_c = 1;
            debut++;
        } else if (argv[1][1] == 'd') {
            flag_d = 1;
            debut++;
        } else if (argv[1][1] == 't') {
            flag_t = 1;
            debut++;
        }
    }

    if (flag_t) {
        srand(time(0));
        int *t;
        for (int i = 0; i < nb_sizes; ++i) {
            t = (int*)malloc(sizes[i] * sizeof(int));
            random_perso(t, sizes[i]);
            int status = 0, wpid, fils;
            for (int j = 0; j < 4; ++j) {
                fils = fork();
                if (fils == 0) {
                    son(t, i, j);
                    exit(0);
                }
            }
            while ((wpid = wait(&status)) > 0); // attend tout les fils
            free(t);
        }
        return 0;
    }

    int n = argc - debut;
    int start_max, end_max, sommeMax;
    int * t = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        t[i] = atoi(argv[debut]);
        ++debut;
    }

    if (flag_a) {
        sommeMax = algo1(t, n, &start_max, &end_max);
    } else if (flag_b) {
        sommeMax = algo2(t, n, &start_max, &end_max);
    } else if (flag_c) {
        sommeMax = algo3(t, n, &start_max, &end_max);
    } else if (flag_d) {
        sommeMax = algo4(t, n, &start_max, &end_max);
    } else {
        sommeMax = algo4(t, n, &start_max, &end_max);
    }

    printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
    free(t);
}
