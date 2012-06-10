#! /usr/bin/env python
# encoding: utf-8

import os,sys
import Configure,Options,Utils
import ccroot,ar
from Configure import conftest
def find_xlcxx(conf):
	cxx=conf.find_program(['xlc++_r','xlc++'],var='CXX',mandatory=True)
	cxx=conf.cmd_to_list(cxx)
	conf.env.CXX_NAME='xlc++'
	conf.env.CXX=cxx
def find_cpp(conf):
	v=conf.env
	cpp=None
	if v['CPP']:cpp=v['CPP']
	elif'CPP'in conf.environ:cpp=conf.environ['CPP']
	if not cpp:cpp=v['CXX']
	v['CPP']=cpp
def xlcxx_common_flags(conf):
	v=conf.env
	v['CXXFLAGS_DEBUG']=['-g']
	v['CXXFLAGS_RELEASE']=['-O2']
	v['CXX_SRC_F']=''
	v['CXX_TGT_F']=['-c','-o','']
	v['CPPPATH_ST']='-I%s'
	if not v['LINK_CXX']:v['LINK_CXX']=v['CXX']
	v['CXXLNK_SRC_F']=''
	v['CXXLNK_TGT_F']=['-o','']
	v['LIB_ST']='-l%s'
	v['LIBPATH_ST']='-L%s'
	v['STATICLIB_ST']='-l%s'
	v['STATICLIBPATH_ST']='-L%s'
	v['RPATH_ST']='-Wl,-rpath,%s'
	v['CXXDEFINES_ST']='-D%s'
	v['SONAME_ST']=''
	v['SHLIB_MARKER']=''
	v['STATICLIB_MARKER']=''
	v['FULLSTATIC_MARKER']='-static'
	v['program_LINKFLAGS']=['-Wl,-brtl']
	v['program_PATTERN']='%s'
	v['shlib_CXXFLAGS']=['-fPIC','-DPIC']
	v['shlib_LINKFLAGS']=['-G','-Wl,-brtl,-bexpfull']
	v['shlib_PATTERN']='lib%s.so'
	v['staticlib_LINKFLAGS']=''
	v['staticlib_PATTERN']='lib%s.a'
def detect(conf):
	conf.find_xlcxx()
	conf.find_cpp()
	conf.find_ar()
	conf.xlcxx_common_flags()
	conf.cxx_load_tools()
	conf.cxx_add_flags()

conftest(find_xlcxx)
conftest(find_cpp)
conftest(xlcxx_common_flags)
