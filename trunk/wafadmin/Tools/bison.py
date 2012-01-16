#! /usr/bin/env python
# encoding: utf-8

import Task
from TaskGen import extension
bison='${BISON} ${BISONFLAGS} ${SRC[0].abspath()} -o ${TGT[0].name}'
cls=Task.simple_task_type('bison',bison,'GREEN',ext_in='.yc .y .yy',ext_out='.c .cxx .h .l',shell=False)
def big_bison(self,node):
	has_h='-d'in self.env['BISONFLAGS']
	outs=[]
	if node.name.endswith('.yc'):
		outs.append(node.change_ext('.tab.cc'))
		if has_h:
			outs.append(node.change_ext('.tab.hh'))
	else:
		outs.append(node.change_ext('.tab.c'))
		if has_h:
			outs.append(node.change_ext('.tab.h'))
	tsk=self.create_task('bison',node,outs)
	tsk.cwd=node.bld_dir(tsk.env)
	self.allnodes.append(outs[0])
def detect(conf):
	bison=conf.find_program('bison',var='BISON',mandatory=True)
	conf.env['BISONFLAGS']='-d'

extension(['.y','.yc','.yy'])(big_bison)
