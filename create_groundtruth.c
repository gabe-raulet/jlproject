#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "vecs_io.h"

int usage(char const *prg);
int read_fvecs(char const *fname, float **vecs, int *d);

typedef struct
{
    int id;
    float dist;
} item_t;

int item_cmp(const void *v1, const void *v2);

int main(int argc, char *argv[])
{
    int i, j;
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

    float *base_vecs, *query_vecs;
    int base_num, query_num, base_dim, query_dim, d;

    base_num = read_fvecs(base_fname, &base_vecs, &base_dim);
    query_num = read_fvecs(query_fname, &query_vecs, &query_dim);

    assert(query_dim == base_dim);
    d = query_dim;

    item_t *items = calloc(base_num, sizeof(item_t));

    for (i = 0; i < query_num; ++i)
    {
        float *q = &query_vecs[i*d];
        double dist = 0.0;

        for (j = 0; j < base_num; ++j)
        {
            float *p = &base_vecs[i*d];

            for (int k = 0; k < d; ++k)
            {
                dist += (p[k] - q[k]) * (p[k] - q[k]);
            }

            items[j].id = j;
            items[j].dist = (float)dist;
        }

        qsort(items, (size_t)base_num, sizeof(item_t), item_cmp);

        for (j = 0; j < 100; ++j)
        {
            printf("%d\t%f\n", items[j].id, sqrt(items[j].dist));
        }
    }

    free(base_vecs);
    free(query_vecs);
    free(items);

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

int item_cmp(const void *v1, const void *v2)
{
    const item_t *item1 = (item_t*)v1;
    const item_t *item2 = (item_t*)v2;

    if (item1->dist != item2->dist)
    {
        return item1->dist < item2->dist? -1 : 1;
    }

    return 0;
}


