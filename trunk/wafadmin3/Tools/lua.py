#! /usr/bin/env python
# encoding: utf-8

import TaskGen
from TaskGen import taskgen,feature
from Constants import*
TaskGen.declare_chain(name='luac',rule='${LUAC} -s -o ${TGT} ${SRC}',ext_in='.lua',ext_out='.luac',reentrant=False,install='LUADIR',)
def init_lua(self):
	self.default_chmod=O755
def detect(conf):
	conf.find_program('luac',var='LUAC',mandatory=True)

feature('lua')(init_lua)
