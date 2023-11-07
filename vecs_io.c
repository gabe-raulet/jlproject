#include "vecs_io.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int vecs_read(FILE *fp, void **data, int *d)
{
    int dim, n, i, d2;
    unsigned char *v, *p;

    assert(fp != NULL && data != NULL && d != NULL);
    assert(sizeof(int) == sizeof(float));

    fseek(fp, 0, SEEK_SET);
    fread(&dim, sizeof(dim), 1, fp);

    fseek(fp, 0, SEEK_END);
    n = ftell(fp) / (sizeof(int) + (dim * 4));
    fseek(fp, 0, SEEK_SET);

    p = v = malloc(n*dim*4);
    assert(p != NULL);

    for (i = 0; i < n; ++i)
    {
        fread(&d2, sizeof(dim), 1, fp);
        assert(dim == d2);

        fread(p, 4, dim, fp);
        p += (4*dim);
    }

    *d = dim;
    *data = v;

    return n;
}

int vecs_write(FILE *fp, const void *data, int d, int n)
{
    int i;
    const float *p = data;

    assert(fp != NULL && data != NULL);

    for (i = 0; i < n; ++i)
    {
        fwrite(&d, sizeof(int), 1, fp);
        fwrite(p, 4, d, fp);
        p += (4*d);
    }

    return n;
}
