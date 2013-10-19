from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("pyamp",
                         ["pyamp.pyx"],
                         language="c++",
                         extra_objects=["intpp.o","data.o"],
                         extra_compile_args=['-UNDEBUG'],
                         extra_link_args=['-fPIC','-UNDEBUG'],
                         )]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
    )
