int algo4 (int * t, int n, int *start_max, int *end_max) {
    int start = 0, somme = 0, sommeMax = t[0];
    *start_max = 0;
    *end_max = 0;
    for(int i = 0; i < n; ++i) {
        if(somme + t[i] >= 0)
            somme += t[i];
        else {
            somme = t[++i];
            start = i;
        }
        if(sommeMax < somme) {
            sommeMax = somme;
            *start_max = start;
            *end_max = i;
        }
    }
    return sommeMax;
}
