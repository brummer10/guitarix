#! /usr/bin/env python
# encoding: utf-8

import os,optparse
import Utils,Options,Configure
import ccroot,ar
from Configure import conftest
def find_sxx(conf):
	v=conf.env
	cc=None
	if v['CXX']:cc=v['CXX']
	elif'CXX'in conf.environ:cc=conf.environ['CXX']
	if not cc:cc=conf.find_program('c++',var='CXX')
	if not cc:conf.fatal('sunc++ was not found')
	cc=conf.cmd_to_list(cc)
	try:
		if not Utils.cmd_output(cc+['-flags']):
			conf.fatal('sunc++ %r was not found'%cc)
	except ValueError:
		conf.fatal('sunc++ -flags could not be executed')
	v['CXX']=cc
	v['CXX_NAME']='sun'
def sxx_common_flags(conf):
	v=conf.env
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
	v['CXXDEFINES_ST']='-D%s'
	v['SONAME_ST']='-Wl,-h -Wl,%s'
	v['SHLIB_MARKER']='-Bdynamic'
	v['STATICLIB_MARKER']='-Bstatic'
	v['program_PATTERN']='%s'
	v['shlib_CXXFLAGS']=['-Kpic','-DPIC']
	v['shlib_LINKFLAGS']=['-G']
	v['shlib_PATTERN']='lib%s.so'
	v['staticlib_LINKFLAGS']=['-Bstatic']
	v['staticlib_PATTERN']='lib%s.a'
detect='''
find_sxx
find_cpp
find_ar
sxx_common_flags
cxx_load_tools
cxx_add_flags
'''

conftest(find_sxx)
conftest(sxx_common_flags)
