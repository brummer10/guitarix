#! /usr/bin/env python
# encoding: utf-8

import sys
import Utils,ar
from Configure import conftest
def find_dmd(conf):
	conf.find_program(['dmd','ldc'],var='D_COMPILER',mandatory=True)
def common_flags_ldc(conf):
	v=conf.env
	v['DFLAGS']=['-d-version=Posix']
	v['DLINKFLAGS']=[]
	v['D_shlib_DFLAGS']=['-relocation-model=pic']
def common_flags_dmd(conf):
	v=conf.env
	v['DFLAGS']=['-version=Posix']
	v['D_SRC_F']=''
	v['D_TGT_F']=['-c','-of']
	v['DPATH_ST']='-I%s'
	v['D_LINKER']=v['D_COMPILER']
	v['DLNK_SRC_F']=''
	v['DLNK_TGT_F']='-of'
	v['DLIB_ST']='-L-l%s'
	v['DLIBPATH_ST']='-L-L%s'
	v['DFLAGS_OPTIMIZED']=['-O']
	v['DFLAGS_DEBUG']=['-g','-debug']
	v['DFLAGS_ULTRADEBUG']=['-g','-debug']
	v['DLINKFLAGS']=['-quiet']
	v['D_shlib_DFLAGS']=['-fPIC']
	v['D_shlib_LINKFLAGS']=['-L-shared']
	v['DHEADER_ext']='.di'
	v['D_HDR_F']=['-H','-Hf']
def detect(conf):
	conf.find_dmd()
	conf.check_tool('ar')
	conf.check_tool('d')
	conf.common_flags_dmd()
	conf.d_platform_flags()
	if conf.env.D_COMPILER.find('ldc')>-1:
		conf.common_flags_ldc()

conftest(find_dmd)
conftest(common_flags_ldc)
conftest(common_flags_dmd)
