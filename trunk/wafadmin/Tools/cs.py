#! /usr/bin/env python
# encoding: utf-8

import TaskGen,Utils,Task,Options
from Logs import error
from TaskGen import before,after,taskgen,feature
flag_vars=['FLAGS','ASSEMBLIES']
def init_cs(self):
	Utils.def_attrs(self,flags='',assemblies='',resources='',uselib='')
def apply_uselib_cs(self):
	if not self.uselib:
		return
	global flag_vars
	for var in self.to_list(self.uselib):
		for v in self.flag_vars:
			val=self.env[v+'_'+var]
			if val:self.env.append_value(v,val)
def apply_cs(self):
	try:self.meths.remove('apply_core')
	except ValueError:pass
	for i in self.to_list(self.assemblies)+self.env['ASSEMBLIES']:
		self.env.append_unique('_ASSEMBLIES','/r:'+i)
	for i in self.to_list(self.resources):
		self.env.append_unique('_RESOURCES','/resource:'+i)
	self.env['_TYPE']=getattr(self,'type','exe')
	self.env.append_unique('_FLAGS',self.to_list(self.flags))
	self.env.append_unique('_FLAGS',self.env.FLAGS)
	nodes=[self.path.find_resource(i)for i in self.to_list(self.source)]
	self.create_task('mcs',nodes,self.path.find_or_declare(self.target))
Task.simple_task_type('mcs','${MCS} ${SRC} /target:${_TYPE} /out:${TGT} ${_FLAGS} ${_ASSEMBLIES} ${_RESOURCES}',color='YELLOW')
def detect(conf):
	csc=getattr(Options.options,'cscbinary',None)
	if csc:
		conf.env.MCS=csc
	conf.find_program(['gmcs','mcs'],var='MCS')
def set_options(opt):
	opt.add_option('--with-csc-binary',type='string',dest='cscbinary')

feature('cs')(init_cs)
feature('cs')(apply_uselib_cs)
after('init_cs')(apply_uselib_cs)
feature('cs')(apply_cs)
after('apply_uselib_cs')(apply_cs)
before('apply_core')(apply_cs)
