#include "algo4.h"

int algo4 (int * t, int n, int *start_max, int *end_max) {
    int sum_max = 0, sum = 0, i = 0;
    *start_max = 0;
    *end_max = -1;
    for (int j = 0; j < n; j++) {
        sum += t[j];
        if (sum < 0) {
            i = j + 1;
            sum = 0;
        } else if (sum > sum_max) {
            sum_max = sum;
            *start_max = i;
            *end_max   = j;
        }
    }
    if (*start_max <= *end_max && *start_max >= 0 && *end_max >= 0) {
        return sum_max;
    } else {
        *start_max = 0;
        *end_max = 0;
        return 0;
    }
}
