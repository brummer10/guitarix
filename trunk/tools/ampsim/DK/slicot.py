import numpy as np
import ctypes as ct

__all__ = ["ab09ad","ab09ax","tb01id","tb01wd"]

def c_arr(w=False):
    flags = ['F']
    if w:
        flags.append('W')
    return np.ctypeslib.ndpointer(dtype=ct.c_double, ndim=1, flags=flags)
def c_mat(w=False):
    flags = ['F']
    if w:
        flags.append('W')
    return np.ctypeslib.ndpointer(dtype=ct.c_double, ndim=2, flags=flags)

slicot = ct.cdll.LoadLibrary("libslicot.so.0")

################################################################
## AB09AD
#
slicot.ab09ad_.restype = None
slicot.ab09ad_.argtypes = [
    ct.c_char_p, #DICO,
    ct.c_char_p, #JOB,
    ct.c_char_p, #EQUIL,
    ct.c_char_p, #ORDSEL,
    ct.POINTER(ct.c_int), #N,
    ct.POINTER(ct.c_int), #M,
    ct.POINTER(ct.c_int), #P,
    ct.POINTER(ct.c_int), #NR,
    c_mat(True), #A,
    ct.POINTER(ct.c_int), #LDA,
    c_mat(True), #B,
    ct.POINTER(ct.c_int), #LDB,
    c_mat(True), #C,
    ct.POINTER(ct.c_int), #LDC,
    c_arr(True), #HSV,
    ct.POINTER(ct.c_double), #TOL,
    np.ctypeslib.ndpointer(dtype=ct.c_int, ndim=1, flags=["F","W"]), #IWORK,
    c_arr(True), #DWORK,
    ct.POINTER(ct.c_int), #LDWORK,
    ct.POINTER(ct.c_int), #IWARN,
    ct.POINTER(ct.c_int), #INFO
    ]

def ab09ad(dico, job, equil, A, B, C, nr=None, tol=0):
    ordsel = 'A' if nr is None else 'F'
    Ar = np.array(A, dtype=np.float64, order='F', copy=True)
    Br = np.array(B, dtype=np.float64, order='F', copy=True)
    Cr = np.array(C, dtype=np.float64, order='F', copy=True)
    _nr = ct.c_int(nr or 0)
    hsv = np.zeros(Ar.shape[1], dtype=np.float64, order='F')
    iwork = np.zeros(Ar.shape[1], dtype=np.int32, order='F')
    dwork = np.zeros(Ar.size * 5, dtype=np.float64, order='F')
    iwarn = ct.c_int()
    info = ct.c_int()
    n = ct.c_int(Ar.shape[0])
    m = ct.c_int(Br.shape[1])
    p = ct.c_int(Cr.shape[0])
    lda = ct.c_int(Ar.shape[0])
    ldb = ct.c_int(Br.shape[0])
    ldc = ct.c_int(Cr.shape[0])
    _tol = ct.c_double(tol)
    ldwork = ct.c_int(dwork.shape[0])
    slicot.ab09ad_(
        dico, job, equil, ordsel, ct.byref(n), ct.byref(m), ct.byref(p),
        ct.byref(_nr), Ar, ct.byref(lda), Br, ct.byref(ldb), Cr, ct.byref(ldc),
        hsv, ct.byref(_tol), iwork, dwork, ct.byref(ldwork), ct.byref(iwarn), ct.byref(info))
    if iwarn.value != 0:
        print "ab09ad:", (
            "The selected order NR is greater than the order of a minimal\n"
            "realization of the given system. The order has been set according\n"
            "to the minimal realization of the system.")
    if info.value != 0:
        if info.value < 0:
            raise ValueError("%dth input argument is illegal" % -info.value())
        if info.value == 1:
            raise ValueError("the reduction of A to the real Schur form failed")
        if info.value == 2:
            raise ValueError("the state matrix A is not stable (if DICO = 'C') or not convergent (if DICO = 'D')")
        if info.value == 3:
            raise ValueError("the computation of Hankel singular values failed.")
        raise ValueError("unknown error value %d" % info.value)
    nr = _nr.value
    if nr != Ar.shape[1]:
        Ar = Ar[:nr,:nr]
        Br = Br[:nr]
        Cr = Cr[:,:nr]
    return Ar, Br, Cr, hsv

################################################################
## AB09AX
##
slicot.ab09ax_.restype = None
slicot.ab09ax_.argtypes = [
    ct.c_char_p, #DICO,
    ct.c_char_p, #JOB,
    ct.c_char_p, #ORDSEL,
    ct.POINTER(ct.c_int), #N,
    ct.POINTER(ct.c_int), #M,
    ct.POINTER(ct.c_int), #P,
    ct.POINTER(ct.c_int), #NR,
    c_mat(True), #A,
    ct.POINTER(ct.c_int), #LDA,
    c_mat(True), #B,
    ct.POINTER(ct.c_int), #LDB,
    c_mat(True), #C,
    ct.POINTER(ct.c_int), #LDC,
    c_arr(True), #HSV,
    c_mat(True), #T,
    ct.POINTER(ct.c_int), #LDT,
    c_mat(True), #TI,
    ct.POINTER(ct.c_int), #LDTI,
    ct.POINTER(ct.c_double), #TOL,
    np.ctypeslib.ndpointer(dtype=ct.c_int, ndim=1, flags=["F","W"]), #IWORK,
    c_arr(True), #DWORK,
    ct.POINTER(ct.c_int), #LDWORK,
    ct.POINTER(ct.c_int), #IWARN,
    ct.POINTER(ct.c_int), #INFO
    ]

def ab09ax(dico, job, A, B, C, nr=None, tol=0):
    ordsel = 'A' if nr is None else 'F'
    Ar = np.array(A, dtype=np.float64, order='F', copy=True)
    Br = np.array(B, dtype=np.float64, order='F', copy=True)
    Cr = np.array(C, dtype=np.float64, order='F', copy=True)
    _nr = ct.c_int(nr or 0)
    hsv = np.zeros(Ar.shape[1], dtype=np.float64, order='F')
    T = np.zeros_like(Ar)
    ldt = ct.c_int(Ar.shape[0])
    Ti = np.zeros_like(Ar)
    ldti = ct.c_int(Ar.shape[0])
    iwork = np.zeros(Ar.shape[1], dtype=np.int32, order='F')
    dwork = np.zeros(Ar.size * 5, dtype=np.float64, order='F')
    iwarn = ct.c_int()
    info = ct.c_int()
    n = ct.c_int(Ar.shape[0])
    m = ct.c_int(Br.shape[1])
    p = ct.c_int(Cr.shape[0])
    lda = ct.c_int(Ar.shape[0])
    ldb = ct.c_int(Br.shape[0])
    ldc = ct.c_int(Cr.shape[0])
    _tol = ct.c_double(tol)
    ldwork = ct.c_int(dwork.shape[0])
    slicot.ab09ax_(
        dico, job, ordsel, ct.byref(n), ct.byref(m), ct.byref(p),
        ct.byref(_nr), Ar, ct.byref(lda), Br, ct.byref(ldb), Cr, ct.byref(ldc),
        hsv, T, ct.byref(ldt), Ti, ct.byref(ldti), ct.byref(_tol),
        iwork, dwork, ct.byref(ldwork), ct.byref(iwarn), ct.byref(info))
    if iwarn.value != 0:
        print "ab09ad:", (
            "The selected order NR is greater than the order of a minimal\n"
            "realization of the given system. The order has been set according\n"
            "to the minimal realization of the system.")
    if info.value != 0:
        if info.value < 0:
            raise ValueError("%dth input argument is illegal" % -info.value())
        if info.value == 1:
            raise ValueError("the state matrix A is not stable (if DICO = 'C') or not convergent (if DICO = 'D')")
        if info.value == 2:
            raise ValueError("the computation of Hankel singular values failed.")
        raise ValueError("unknown error value %d" % info.value)
    nr = _nr.value
    if nr != Ar.shape[1]:
        Ar = Ar[:nr,:nr]
        Br = Br[:nr]
        Cr = Cr[:,:nr]
        T = T[:,:nr]
        Ti = Ti[:nr,:]
    return T, Ti, Ar, Br, Cr, hsv

################################################################
## TB01ID
##
slicot.tb01id_.restype = None
slicot.tb01id_.argtypes = [
    ct.c_char_p, #JOB,
    ct.POINTER(ct.c_int), #N,
    ct.POINTER(ct.c_int), #M,
    ct.POINTER(ct.c_int), #P,
    ct.POINTER(ct.c_double), #MAXRED,
    c_mat(True), #A,
    ct.POINTER(ct.c_int), #LDA,
    c_mat(True), #B,
    ct.POINTER(ct.c_int), #LDB,
    c_mat(True), #C,
    ct.POINTER(ct.c_int), #LDC,
    c_arr(True), #SCALE,
    ct.POINTER(ct.c_int), #INFO
    ]

def tb01id(job, A, B, C, maxred=0):
    Ar = np.array(A, dtype=np.float64, order='F', copy=True)
    Br = np.array(B, dtype=np.float64, order='F', copy=True)
    Cr = np.array(C, dtype=np.float64, order='F', copy=True)
    n = ct.c_int(Ar.shape[0])
    m = ct.c_int(Br.shape[1])
    p = ct.c_int(Cr.shape[0])
    lda = ct.c_int(Ar.shape[0])
    ldb = ct.c_int(Br.shape[0])
    ldc = ct.c_int(Cr.shape[0])
    scale = np.zeros(Ar.shape[1], dtype=np.float64, order='F')
    info = ct.c_int()
    maxred_ = ct.c_double(maxred)
    slicot.tb01id_(job, ct.byref(n), ct.byref(m), ct.byref(p), ct.byref(maxred_),
                   Ar, ct.byref(lda), Br, ct.byref(ldb), Cr, ct.byref(ldc),
                   scale, ct.byref(info))
    if info.value != 0:
        if info.value < 0:
            raise ValueError("%dth input argument is illegal" % -info.value())
        raise ValueError("unknown error value %d" % info.value)
    return Ar, Br, Cr, maxred_.value, scale

################################################################
## TB01WD
##
slicot.tb01wd_.restype = None
slicot.tb01wd_.argtypes = [
    ct.POINTER(ct.c_int), #N,
    ct.POINTER(ct.c_int), #M,
    ct.POINTER(ct.c_int), #P,
    c_mat(True), #A,
    ct.POINTER(ct.c_int), #LDA,
    c_mat(True), #B,
    ct.POINTER(ct.c_int), #LDB,
    c_mat(True), #C,
    ct.POINTER(ct.c_int), #LDC,
    c_mat(True), #U,
    ct.POINTER(ct.c_int), #LDU,
    c_arr(True), #WR,
    c_arr(True), #WI,
    c_arr(True), #DWORK,
    ct.POINTER(ct.c_int), #LDWORK,
    ct.POINTER(ct.c_int), #INFO
    ]

def tb01wd(A, B, C):
    Ar = np.array(A, dtype=np.float64, order='F', copy=True)
    Br = np.array(B, dtype=np.float64, order='F', copy=True)
    Cr = np.array(C, dtype=np.float64, order='F', copy=True)
    n = ct.c_int(Ar.shape[0])
    m = ct.c_int(Br.shape[1])
    p = ct.c_int(Cr.shape[0])
    lda = ct.c_int(Ar.shape[0])
    ldb = ct.c_int(Br.shape[0])
    ldc = ct.c_int(Cr.shape[0])
    U = np.zeros_like(Ar)
    ldu = ct.c_int(Ar.shape[0])
    WR = np.zeros(Ar.shape[0], dtype=np.float64, order='F')
    WI = np.zeros(Ar.shape[0], dtype=np.float64, order='F')
    dwork = np.zeros(Ar.shape[0] * 5, dtype=np.float64, order='F')
    ldwork = ct.c_int(dwork.shape[0])
    info = ct.c_int()
    slicot.tb01wd_(
        ct.byref(n), ct.byref(m), ct.byref(p),
        Ar, ct.byref(lda), Br, ct.byref(ldb), Cr, ct.byref(ldc), U, ct.byref(ldu),
        WR, WI, dwork, ct.byref(ldwork), ct.byref(info))
    if info.value != 0:
        if info.value < 0:
            raise ValueError("%dth input argument is illegal" % -info.value())
        raise ValueError("not all eigenvalues computed (%d not computed)" % info.value)
    return Ar, Br, Cr, U, WR, WI
