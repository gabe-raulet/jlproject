#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vecs_io.h"

#define NUM_FILES 4

char const *files[NUM_FILES] = {"siftsmall/siftsmall_base.fvecs",
                                "siftsmall/siftsmall_groundtruth.ivecs",
                                "siftsmall/siftsmall_learn.fvecs",
                                "siftsmall/siftsmall_query.fvecs"};

int endswith(const char *str1, const char *str2);

int main(int argc, char *argv[])
{
    FILE *fp;
    int n, d;
    float *fvecs;
    int *ivecs;

    for (int i = 0; i < NUM_FILES; ++i)
    {
        char const *fname = files[i];
        fp = fopen(fname, "rb");

        if (endswith(fname, "fvecs"))
        {
            n = vecs_read(fp, (void**)&fvecs, &d);
            printf("Read %d floating point vectors (d=%d) from '%s'\n", n, d, fname);
            free(fvecs);
        }
        else if (endswith(fname, "ivecs"))
        {
            n = vecs_read(fp, (void**)&ivecs, &d);
            printf("Read %d integer vectors (d=%d) from '%s'\n", n, d, fname);
            free(ivecs);
        }
        else
        {
            printf("error: could not read '%s'\n", fname);
        }

        fclose(fp);
    }

    return 0;
}

int endswith(const char *str1, const char *str2)
{
    int l1 = strlen(str1);
    int l2 = strlen(str2);

    while (l2 > 0)
    {
        if (str1[--l1] != str2[--l2]) return 0;
    }

    return 1;
}
