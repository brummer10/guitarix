#! /usr/bin/env python
# encoding: utf-8

import os,sys
import Task
from TaskGen import extension,taskgen,after,before
EXT_ASM=['.s','.S','.asm','.ASM','.spp','.SPP']
as_str='${AS} ${ASFLAGS} ${_ASINCFLAGS} ${SRC} -o ${TGT}'
Task.simple_task_type('asm',as_str,'PINK',ext_out='.o',shell=False)
def asm_hook(self,node):
	try:obj_ext=self.obj_ext
	except AttributeError:obj_ext='_%d.o'%self.idx
	task=self.create_task('asm',node,node.change_ext(obj_ext))
	self.compiled_tasks.append(task)
	self.meths.append('asm_incflags')
def asm_incflags(self):
	self.env.append_value('_ASINCFLAGS',self.env.ASINCFLAGS)
	var=('cxx'in self.features)and'CXX'or'CC'
	self.env.append_value('_ASINCFLAGS',self.env['_%sINCFLAGS'%var])
def detect(conf):
	conf.find_program(['gas','as'],var='AS')
	if not conf.env.AS:conf.env.AS=conf.env.CC

extension(EXT_ASM)(asm_hook)
after('apply_obj_vars_cc')(asm_incflags)
after('apply_obj_vars_cxx')(asm_incflags)
before('apply_link')(asm_incflags)
