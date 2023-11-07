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

int main(int argc, char *argv[])
{
    FILE *fp, *fp_tmp;
    int n, d;
    void *vecs;

    for (int i = 0; i < NUM_FILES; ++i)
    {
        char const *fname = files[i];
        fp = fopen(fname, "rb");

        n = vecs_read(fp, &vecs, &d);
        fclose(fp);

        char *fname_tmp = malloc(strlen(fname) + 5);
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ".tmp");
        fp_tmp = fopen(fname_tmp, "wb");

        vecs_write(fp_tmp, vecs, d, n);
        fclose(fp_tmp);

        free(vecs);
        free(fname_tmp);
    }

    return 0;
}
