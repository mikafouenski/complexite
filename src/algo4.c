#include "utils.c"

int main(int argc, char const *argv[])
{
    int tailleT = argc-1;
    int * t = loadTab( tailleT, argv);

    int start = 0;
    int somme = 0;

    int sommeMax = t[0];
    int start_max = 0;
    int end_max = 0;

    for(int i=0; i<tailleT; ++i)
    {
        if(somme + t[i] >= 0)
            somme += t[i];
        else {
            somme = t[i];
            start = i;
        }

        if(sommeMax < somme) {
            sommeMax = somme;
            start_max = start;
            end_max = i;
        }
    }

    printf("%d[%d:%d]\n", sommeMax, start_max, end_max);

    free(t);

    return 0;
}