#!/usr/bin/python
# -*- coding: utf-8 -*-
# Distutils installer for specmatch

# Test for Jack2
#---------------------------------------------------#
import os
if os.path.exists("/usr/local/include/jack/jack.h"):
  path = "/usr/local/include/jack/jack.h"
elif os.path.exists("/usr/include/jack/jack.h"):
  path = "/usr/include/jack/jack.h"
else:
  print("You don't seem to have the jack headers installed.\nPlease install them first")
  exit(-1)

test = open(path).read()

pyjack_macros=[]
if ("jack_get_version_string" in test):
  pyjack_macros+=[('JACK2', '1')]
else:
  pyjack_macros+=[('JACK1', '1')]
#----------------------------------------------------#


from setuptools import setup, Extension
import numpy.distutils

numpy_include_dirs = numpy.distutils.misc_util.get_numpy_include_dirs()

setup(
    name = "specmatch",
    version = "0.9",
    description = "Calculate an IR to match a spectrum",
    zip_safe = False,
    packages = ['specmatch'],
    scripts = ['scripts/specmatch'],
    data_files = [('specmatch', ['specmatch/specmatch.glade'])],
    ext_modules = [Extension("specmatch.jackx",
                             ["pyjackx.c"],
                             libraries=["jack", "dl"],
                             include_dirs=numpy_include_dirs,
                             define_macros=pyjack_macros,
                             )],
    )
