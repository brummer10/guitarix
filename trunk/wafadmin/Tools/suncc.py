#! /usr/bin/env python
# encoding: utf-8

import os,optparse
import Utils,Options,Configure
import ccroot,ar
from Configure import conftest
def find_scc(conf):
	v=conf.env
	cc=None
	if v['CC']:cc=v['CC']
	elif'CC'in conf.environ:cc=conf.environ['CC']
	if not cc:cc=conf.find_program('cc',var='CC')
	if not cc:conf.fatal('suncc was not found')
	cc=conf.cmd_to_list(cc)
	try:
		if not Utils.cmd_output(cc+['-flags']):
			conf.fatal('suncc %r was not found'%cc)
	except ValueError:
		conf.fatal('suncc -flags could not be executed')
	v['CC']=cc
	v['CC_NAME']='sun'
def scc_common_flags(conf):
	v=conf.env
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
	v['CCDEFINES_ST']='-D%s'
	v['SONAME_ST']='-Wl,-h -Wl,%s'
	v['SHLIB_MARKER']='-Bdynamic'
	v['STATICLIB_MARKER']='-Bstatic'
	v['program_PATTERN']='%s'
	v['shlib_CCFLAGS']=['-Kpic','-DPIC']
	v['shlib_LINKFLAGS']=['-G']
	v['shlib_PATTERN']='lib%s.so'
	v['staticlib_LINKFLAGS']=['-Bstatic']
	v['staticlib_PATTERN']='lib%s.a'
detect='''
find_scc
find_cpp
find_ar
scc_common_flags
cc_load_tools
cc_add_flags
link_add_flags
'''

conftest(find_scc)
conftest(scc_common_flags)
