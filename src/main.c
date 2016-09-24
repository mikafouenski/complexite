#include "algo1.h"
#include "algo2.h"
#include "algo3.h"
#include "algo4.h"
#include "utils.h"

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
