#! /usr/bin/python
# -*- coding: utf-8 -*-
#
# dependencies:
# - python-matplotlib
# - python-scipy
# - python-gtk2
# - optional:
#   - python-audiolab
#   - jack-stdio

import numpy as np
import numpy.fft as fft
import scipy.signal as sig
from scipy.interpolate import LSQUnivariateSpline
import sys, gtk, glib, os, socket, json, jackx, time
import subprocess, signal


