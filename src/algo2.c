#include "utils.c"

int main(int argc, char const *argv[])
{
    int tailleT = argc-1;
    int * t = loadTab( tailleT, argv);

    int somme;
    int sommeMax = t[0];
    int start_max = 0;
    int end_max = 0;

    for( int i=0; i< tailleT; ++i) {
        somme = 0;
        for(int j=i; j<tailleT; ++j) {
            somme += t[j];
            if(somme > sommeMax) {
                start_max = i;
                end_max = j;
                sommeMax = somme;
            }
        }
    }

    printf("%d[%d:%d]\n", sommeMax, start_max, end_max);

    free(t);

    return 0;
}
