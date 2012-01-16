#! /usr/bin/env python
# encoding: utf-8

import Options
import Task
def set_options(opt):
	opt.add_option('--with-gcov',action='store_true',help='Use gcov for profiling',default=False)
def setup(bld):
	for name in('cc','cxx'):
		if name not in Task.TaskBase.classes:
			continue
		task=Task.TaskBase.classes[name]
		line=task.run.code.replace('SRC','SRC[0].abspath(env)')
		(fun,v)=Task.compile_fun(name,line,False)
		fun.code=line
		task.run=fun
def detect(conf):
	conf.find_program('gcov')
	gcov_flags='-fprofile-arcs -ftest-coverage'.split()
	conf.env['CXXFLAGS']=conf.env['CFLAGS']=conf.env['LINKFLAGS']=gcov_flags

