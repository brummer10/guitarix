#! /usr/bin/env python
# encoding: utf-8

import os,sys
import Configure,Options,Utils
import ccroot,ar
from Configure import conftest
def find_xlc(conf):
	cc=conf.find_program(['xlc_r','xlc'],var='CC',mandatory=True)
	cc=conf.cmd_to_list(cc)
	conf.env.CC_NAME='xlc'
	conf.env.CC=cc
def find_cpp(conf):
	v=conf.env
	cpp=None
	if v['CPP']:cpp=v['CPP']
	elif'CPP'in conf.environ:cpp=conf.environ['CPP']
	if not cpp:cpp=v['CC']
	v['CPP']=cpp
def xlc_common_flags(conf):
	v=conf.env
	v['CCFLAGS_DEBUG']=['-g']
	v['CCFLAGS_RELEASE']=['-O2']
	v['CC_SRC_F']=''
	v['CC_TGT_F']=['-c','-o','']
	v['CPPPATH_ST']='-I%s'
	if not v['LINK_CC']:v['LINK_CC']=v['CC']
	v['CCLNK_SRC_F']=''
	v['CCLNK_TGT_F']=['-o','']
	v['LIB_ST']='-l%s'
	v['LIBPATH_ST']='-L%s'
	v['STATICLIB_ST']='-l%s'
	v['STATICLIBPATH_ST']='-L%s'
	v['RPATH_ST']='-Wl,-rpath,%s'
	v['CCDEFINES_ST']='-D%s'
	v['SONAME_ST']=''
	v['SHLIB_MARKER']=''
	v['STATICLIB_MARKER']=''
	v['FULLSTATIC_MARKER']='-static'
	v['program_LINKFLAGS']=['-Wl,-brtl']
	v['program_PATTERN']='%s'
	v['shlib_CCFLAGS']=['-fPIC','-DPIC']
	v['shlib_LINKFLAGS']=['-G','-Wl,-brtl,-bexpfull']
	v['shlib_PATTERN']='lib%s.so'
	v['staticlib_LINKFLAGS']=''
	v['staticlib_PATTERN']='lib%s.a'
def detect(conf):
	conf.find_xlc()
	conf.find_cpp()
	conf.find_ar()
	conf.xlc_common_flags()
	conf.cc_load_tools()
	conf.cc_add_flags()

conftest(find_xlc)
conftest(find_cpp)
conftest(xlc_common_flags)
