#ifndef VECS_IO_H_
#define VECS_IO_H_

#include <stdio.h>
#include <stdint.h>

int vecs_read(FILE *fp, void **data, int *d);
int vecs_write(FILE *fp, const void *data, int d, int n);

#endif
