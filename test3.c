#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int main(int argc, char *argv[])
{
    char const *fname = argv[1];
    FILE *fp = fopen(fname, "rb");

    int k, k2, n;

    fread(&k, sizeof(int), 1, fp);
    fseek(fp, 0, SEEK_END);
    n = ftell(fp) / (sizeof(int) * (k+1));
    fseek(fp, 0, SEEK_SET);

    int *ids = malloc(k * sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        fread(&k2, sizeof(int), 1, fp);
        assert(k == k2);

        fread(ids, sizeof(int), k, fp);

        for (int j = 0; j < k-1; ++j)
            printf("%d,", ids[j]);
        printf("%d\n", ids[k-1]);
    }

    free(ids);
    fclose(fp);

    return 0;
}
