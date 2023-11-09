#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "vecs_io.h"

int usage(char const *prg);
int read_fvecs(char const *fname, float **vecs, int *d);

int main(int argc, char *argv[])
{
    int i, j, k;
    char *base_fname, *query_fname, *truth_fname;

    if (argc != 8) return usage(argv[0]);

    for (i = 1; i < argc; ++i)
    {
        char *a = argv[i];
        if (!strcmp(a, "-base") && i+1 < argc) base_fname = argv[++i];
        else if (!strcmp(a, "-query") && i+1 < argc) query_fname = argv[++i];
        else if (!strcmp(a, "-truth") && i+1 < argc) truth_fname = argv[++i];
        else if (!strcmp(a, "-k") && i+1 < argc) k = atoi(argv[++i]);
        else
        {
            fprintf(stderr, "error: unknown parameter '%s'\n", a);
            return usage(argv[0]);
        }
    }

    float *base_vecs, *query_vecs;
    int base_num, query_num, base_dim, query_dim, d;

    base_num = read_fvecs(base_fname, &base_vecs, &base_dim);
    query_num = read_fvecs(query_fname, &query_vecs, &query_dim);

    assert(query_dim == base_dim);
    d = query_dim;

    free(base_vecs);
    free(query_vecs);

    return 0;
}

int usage(char const *prg)
{
    fprintf(stderr, "usage: %s [parameters]\n", prg);
    fprintf(stderr, "parameters: -base  IN  [base vectors filename (.fvecs)] REQUIRED\n");
    fprintf(stderr, "            -query IN  [query vectors filename (.fvecs)] REQUIRED\n");
    fprintf(stderr, "            -truth OUT [ground truth filename (.ivecs)] REQUIRED\n");
    fprintf(stderr, "            -k     IN  [report k nearest neighbors INT] REQUIRED\n");
    return -1;
}

int read_fvecs(char const *fname, float **vecs, int *d)
{
    float *v;
    int n, dim;
    FILE *fp;

    assert(fname != NULL && vecs != NULL && d != NULL);

    fp = fopen(fname, "rb");

    if (fp == NULL)
    {
        fprintf(stderr, "error: couldn't open file '%s'\n", fname);
        exit(-1);
    }

    n = vecs_read(fp, (void**)&v, &dim);
    fclose(fp);

    assert(n > 0 && dim > 0 && v != NULL);

    *d = dim;
    *vecs = v;

    return n;
}
