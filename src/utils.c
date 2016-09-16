#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>

int * generateTab( int size, int init) {
    if( init )
        return (int*)calloc(size, sizeof( int ) );
    else
        return (int*)malloc(size * sizeof( int ) );
}