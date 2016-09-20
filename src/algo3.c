#include <stdio.h>
#include <limits.h>
#include "utils.c"

int max2(int a, int b) { 
    return (a > b)? a : b;
}
int max3(int a, int b, int c) {
    return max2(max2(a, b), c);
}

int maxCrossingSum(int * t, int head, int med, int tail) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = med; i >= head; --i) {
        sum = sum + t[i];
        if (sum > left_sum)
          left_sum = sum;
    }
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = med + 1; i <= tail; ++i) {
        sum = sum + t[i];
        if (sum > right_sum)
          right_sum = sum;
    }
    return left_sum + right_sum;
}

int maxSubArraySum(int * t, int head, int tail) {
    if (head == tail)
        return t[head];
    int med = (head + tail) / 2;
    return max3(maxSubArraySum(t, head, med),
                maxSubArraySum(t, med + 1, tail),
                maxCrossingSum(t, head, med, tail));
}

int main(int argc, char const *argv[]) {
    int tailleT = argc-1;
    int * t = loadTab( tailleT, argv);

    int somme_max, start_max, end_max;

    somme_max = maxSubArraySum(t, 0, tailleT - 1);

    free(t);

    printf("%d[%d:%d]\n", somme_max, start_max, end_max);

    return 0;
}
