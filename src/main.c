#include "algo1.h"
#include "algo2.h"
#include "algo3.h"
#include "algo4.h"
#include "utils.h"

int sizes[7] = {100, 500, 5000, 10000, 100000, 500000, 1000000};
typedef int(*Functions[4])(int*,int, int*, int*);
Functions algos = {algo1, algo2, algo3, algo4};
typedef struct tms sTms;
typedef struct{
    sTms sdebut, sfin;
}temps_exec;
int result[4][7];

void random_perso(int* t, int n) {
    for(int i = 0 ; i < n ; ++i)
        t[i] = (rand() % (100 * 2) - 100);
}

void capt_alarm(int sig) {
    printf("Timeout\n");
    exit(0);
}

void son (int * t, int n, int algo, int size) {
    signal(SIGALRM, capt_alarm);
    alarm(2);
    temps_exec temps;
    int start_max, end_max, sommeMax;
    times(&temps.sdebut); //debut
    sommeMax = (algos[algo])(t, n, &start_max, &end_max);
    times(&temps.sfin);
    int exec = (temps.sfin.tms_utime - temps.sdebut.tms_utime) * 10;
    printf("Algo%d, taille:%d temps:%d\n", algo + 1, n, exec);
    printf("%d[%d:%d]\n", sommeMax, start_max, end_max);
    result[algo][size] = exec; //POURQUOI ????????
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
        printf("Not yet implemented\n");
        srand(time(0));
        int *t;
        for (int j = 0; j < 7; ++j)
            for (int k = 0; k < 7; ++k)
                result[j][k] = -1;
        for (int i = 0; i < 7; ++i) { //tailles
            int size = sizes[i];
            t = (int*)malloc(size * sizeof(int));
            random_perso(t, size);
            int status = 0, wpid, fils;
            for (int j = 0; j < 4; ++j) {
                fils = fork();
                if (fils == 0) {
                    son(t, size, j, i);
                    exit(0);
                }
            }
            while ((wpid = wait(&status)) > 0); // attend tout les fils
            free(t);
        }
        printf("Result:\n");
        for (int r = 0; r < 4; ++r) {
            for(int c = 0; c < 7; ++c)
                printf("%d   ", result[r][c]);
            printf("\n");
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
