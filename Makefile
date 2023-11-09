
all: create_groundtruth

create_groundtruth: create_groundtruth.c
	clang -o create_groundtruth create_groundtruth.c vecs_io.c

clean:
	rm -rf *.dSYM a.out create_groundtruth
