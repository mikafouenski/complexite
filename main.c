#if defined __STRICT_ANSI__ && !defined _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "algo1.h"
#include "algo2.h"
#include "algo3.h"
#include "algo4.h"

typedef struct tms sTms;

typedef struct{
    sTms sdebut, sfin;
}temps_exec;

typedef int(*Pfonction[4])(int*,int, int*, int*);

int sizes[9] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
char* algos[4] = {"algo1", "algo2", "algo3", "algo4"};
Pfonction functions = {algo1, algo2, algo3, algo4};
char* results[4] = {"result/algo1.csv", "result/algo2.csv", "result/algo3.csv", "result/algo4.csv"};

void captSigAlarm() {
    printf("Timeout !\n");
    exit(0);
}

int signal_perso (int sig, int options) {
    int r;
    struct sigaction s;
    s.sa_handler = captSigAlarm;
    sigemptyset (&s.sa_mask);
    s.sa_flags = options;
    r = sigaction (sig, &s, NULL);
    return r;
}

void resultat(long int tab[9][5], int t) {
    int i, j;
    FILE *fichier = NULL;

    fichier = fopen(results[t], "w+");
    fprintf(fichier, ", ");
    for(i = 0; i < 9; ++i)
        fprintf(fichier, "%d, ", sizes[i]);
    fprintf(fichier, "\n");

    for (i = 0; i < 5; ++i) {
        fprintf(fichier, "%s, ", algos[t]);
        for (j = 0; j < 9; ++j)
            fprintf(fichier, "%ld, ", tab[j][i]);
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "\n");
}

void display(int* array, int arraysize) {
    int i;
    for (i = 0; i < arraysize; ++i)
        printf("%d", array[i]);
    printf("\n");
}

void random_perso(int* array, int arraysize) {
    int i;
    srand(time(NULL));
    for(i = 0 ; i < arraysize ; ++i)
        array[i] = (rand() % arraysize - arraysize/2);
}

void traitement_fils(int* sizes, int algo) {
    int i, j, size;
    int* array;
    temps_exec temps;
    int start_max, end_max, sommeMax;

    long int tableauResultat[9][5];
    alarm(60);
    signal_perso(SIGALRM, SA_RESTART);

    for (j = 0; j < 5; ++j) {
        /* le faire 5 fois */
        for (i = 0; i < 9; ++i) {
            /* 9 tailles */
            size = sizes[i];
            array = (int*)malloc(size * sizeof(int));
            random_perso(array, size);
            times(&temps.sdebut);
            sommeMax = (functions[algo])(array, size, &start_max, &end_max);
            times(&temps.sfin);
            // display(array, size);
            tableauResultat[i][j] = (temps.sfin.tms_utime - temps.sdebut.tms_utime) * 10;
            printf("%s, taille %d, %d[%d:%d], %ld millisecondes\n", algos[algo], sizes[i], sommeMax, start_max, end_max, (temps.sfin.tms_utime - temps.sdebut.tms_utime) * 10);
        }
    }
    resultat(tableauResultat, algo);
    free(array);
}

int main(/*int argc, char const *argv[]*/) {

    // int start_max, end_max, sommeMax;
    // int n = argc-1;
    // int * t = (int*)malloc(n * sizeof( int ) );
    // for(int i=0; i<n; ++i)
    //     t[i] = atoi(argv[i+1]);

    // sommeMax = algo1(t, n, &start_max, &end_max);
    // printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
    // sommeMax = algo2(t, n, &start_max, &end_max);
    // printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
    // sommeMax = algo3(t, n, &start_max, &end_max);
    // printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
    // sommeMax = algo4(t, n, &start_max, &end_max);
    // printf("%d[%d:%d]\n", sommeMax, start_max, end_max);

    // free(t);

    int i, status = 0, wpid, fils;

    for (i = 0; i < 4; ++i) {
        /* 4 algos */
        fils = fork();
        if (fils == 0) {
            traitement_fils(sizes, i);
            exit(0);
        }
    }

    while ((wpid = wait(&status)) > 0);

    return 0;
}
