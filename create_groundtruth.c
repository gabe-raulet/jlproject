#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vecs_io.h"

int usage(char const *prg);

int main(int argc, char *argv[])
{
    int i;
    char *base_fname, *query_fname, *truth_fname;

    if (argc != 7) return usage(argv[0]);

    for (i = 1; i < argc; ++i)
    {
        char *a = argv[i];
        if (!strcmp(a, "-base") && i+1 < argc) base_fname = argv[++i];
        else if (!strcmp(a, "-query") && i+1 < argc) query_fname = argv[++i];
        else if (!strcmp(a, "-truth") && i+1 < argc) truth_fname = argv[++i];
        else
        {
            fprintf(stderr, "error: unknown parameter '%s'\n", a);
            return usage(argv[0]);
        }
    }

    return 0;
}

int usage(char const *prg)
{
    fprintf(stderr, "usage: %s [parameters]\n", prg);
    fprintf(stderr, "parameters: -base  IN  [base vectors filename (.fvecs)] REQUIRED\n");
    fprintf(stderr, "            -query IN  [query vectors filename (.fvecs)] REQUIRED\n");
    fprintf(stderr, "            -truth OUT [ground truth filename (.ivecs)] REQUIRED\n");
    return -1;
}

