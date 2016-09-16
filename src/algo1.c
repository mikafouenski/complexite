#include <stdio.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    int t[100];
    int somme = 0;
    int start = 0, end = 100, sommeMax = INT_MIN;
    int start_max = 0, end_max = 100;

    for (int i = 0; i < 100; ++i) {
        for (int j = end; j >= start; --j) {
            for (int k = i; k <= j; ++k) {
                somme = somme + t[k];
            }
            if (sommeMax < somme) {
                sommeMax = somme;
                start_max = i;
                end_max = j;
            }
        }
    }
    printf("[%d:%d]\n", start_max, end_max);
    return 0;
}
