import os
import struct
import numpy as np

def vecs_read(fname):

    if fname.endswith(".fvecs"): dtype = np.float32
    elif fname.endswith(".ivecs"): dtype = np.int32
    elif fname.endswith(".bvecs"): dtype = np.uint8
    else: raise ValueError("Unknown file type: {}".format(hfname))

    fsize = os.path.getsize(fname)

    with open(fname, "rb") as f:
        d = int.from_bytes(f.read(4), byteorder="little")
        n = fsize // (4 * (d + 1))
        X = np.zeros((n, d), dtype=dtype)
        f.seek(0, 0)
        for i in range(n):
            assert d == int.from_bytes(f.read(4), byteorder="little")
            X[i] = np.frombuffer(f.read(4*d), dtype=dtype, count=d)

    return X

def vecs_write(fname, X):

    if X.dtype == np.float32 and not fname.endswith(".fvecs"): fname += ".fvecs"
    elif X.dtype == np.int32 and not fname.endswith(".ivecs"): fname += ".ivecs"
    elif X.dtype == np.uint8 and not fname.endswith(".bvecs"): fname += ".bvecs"
    else: raise ValueError("Unknown vector type: {}".format(str(X.dtype)))

    n, d = X.shape
    with open(fname, "wb") as f:
        for i in range(n):
            f.write(d.to_bytes(4, byteorder="little"))
            f.write(X[i].tobytes())


X = vecs_read("siftsmall_base.fvecs")
vecs_write("siftsmall_base2", X)

X = vecs_read("siftsmall_learn.fvecs")
vecs_write("siftsmall_learn2", X)

X = vecs_read("siftsmall_query.fvecs")
vecs_write("siftsmall_query2", X)

X = vecs_read("siftsmall_groundtruth.ivecs")
vecs_write("siftsmall_groundtruth2", X)
