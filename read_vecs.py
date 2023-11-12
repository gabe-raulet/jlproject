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
