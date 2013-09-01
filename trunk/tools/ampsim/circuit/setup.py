from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("pycircuit",
                         ["pycircuit.pyx"],
                         language="c++",
                         libraries=["sundials_kinsol","sundials_nvecserial","lapack"],
                         extra_objects=["circuit.cc"],
                         )]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
    )
