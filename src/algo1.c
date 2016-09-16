#include "utils.c"

int main(int argc, char const *argv[])
{
    int tailleT = argc-1;
    int * t = generateTab( tailleT, 0);

    for(int i=0; i<tailleT; ++i)
        t[i] = atoi(argv[i+1]);


    int somme;
    int sommeMax = t[0];
    int start_max = 0;
    int end_max = 0;
    

    for( int i=0; i< tailleT; ++i) {
        for(int j=i; j<tailleT; ++j) {
            somme = 0;
            for(int k=i; k<=j; ++k)
                somme += t[k];
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
