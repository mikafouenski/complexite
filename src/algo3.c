#include "utils.c"

int seqSommeMax(int *t, int start, int end, int *start_max, int *end_max)
{
    int somme;
    int sommeMax = t[0];

    for( int i=start; i< end; ++i) {
        somme = 0;
        for(int j=i; j<end; ++j) {
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

int main(int argc, char const *argv[])
{
    int tailleT = argc-1;
    int * t = loadTab( tailleT, argv);

    int t1_start, t1_end, t2_start, t2_end, t3_start, t3_end;

    int r1 = seqSommeMax(t, 0, tailleT/2, &t1_start, &t1_end);
    int r2 = seqSommeMax(t, tailleT/2, tailleT, &t2_start, &t2_end);
    int r3 = seqSommeMax(t, 0+tailleT/2, tailleT-tailleT/2, &t3_start, &t3_end);

    if(r1 > r2 && r1 > r3) {
        printf("%d[%d:%d]\n", r1, t1_start, t1_end);
    } else if (r2 > r3) {
        printf("%d[%d:%d]\n", r2, t2_start, t2_end);
    } else
        printf("%d[%d:%d]\n", r3, t3_start, t3_end);

    free(t);

    return 0;
}