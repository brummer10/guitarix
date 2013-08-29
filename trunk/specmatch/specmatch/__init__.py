#! /usr/bin/python
# -*- coding: utf-8 -*-

import argparse, matplotlib, gtk
from guitarix import Guitarix
from jackclients import JackPlayer
from ui import SpecWindow

def main():
    parser = argparse.ArgumentParser(
        description='Calculate an IR to match a spectrum')
    parser.add_argument("specfile", nargs="?", help="project file")
    parser.add_argument("orig_ir", nargs="?", help="debug: IR to reproduce")
    parser.add_argument("--no-guitarix", action="store_true",
                        help="run without connecting to Guitarix")
    parser.add_argument("--no-jack", action="store_true",
                        help="run without connecting to jackd, implies --no-guitarix")
    parser.add_argument("--samplerate", metavar="SR", type=float, default=44100.0,
                        help="set samplerate (when --no-jack), default: %(default)s")
    parser.add_argument("--soundfile", metavar="name",
                        help="debug: writeout input file convoluted with calculated IR")
    args = parser.parse_args()
    jackplayer = None if args.no_jack else JackPlayer()
    guitarix = None if args.no_guitarix or args.no_jack else Guitarix(jackplayer)
    matplotlib.interactive(True)
    SpecWindow(guitarix, jackplayer, args.specfile, args.orig_ir, args.samplerate,
               args.soundfile)
    gtk.main()
