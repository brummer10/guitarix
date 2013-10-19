from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("pycircuit",
                         ["pycircuit.pyx"],
                         language="c++",
                         libraries=["sundials_kinsol","sundials_nvecserial","lapack","rt"],
                         extra_objects=["circuit.cc"],
                         extra_compile_args=['-UNDEBUG'],
                         extra_link_args=['-fPIC','-UNDEBUG'],
                         )]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
    )
