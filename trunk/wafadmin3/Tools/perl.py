#! /usr/bin/env python
# encoding: utf-8

import os
import Task,Options,Utils
from Configure import conf
from TaskGen import extension,taskgen,feature,before
xsubpp_str='${PERL} ${XSUBPP} -noprototypes -typemap ${EXTUTILS_TYPEMAP} ${SRC} > ${TGT}'
EXT_XS=['.xs']
def init_perlext(self):
	self.uselib=self.to_list(getattr(self,'uselib',''))
	if not'PERL'in self.uselib:self.uselib.append('PERL')
	if not'PERLEXT'in self.uselib:self.uselib.append('PERLEXT')
	self.env['shlib_PATTERN']=self.env['perlext_PATTERN']
def xsubpp_file(self,node):
	outnode=node.change_ext('.c')
	self.create_task('xsubpp',node,outnode)
	self.allnodes.append(outnode)
Task.simple_task_type('xsubpp',xsubpp_str,color='BLUE',before='cc cxx',shell=False)
def check_perl_version(conf,minver=None):
	if getattr(Options.options,'perlbinary',None):
		conf.env.PERL=Options.options.perlbinary
	else:
		conf.find_program('perl',var='PERL',mandatory=True)
	try:
		version=Utils.cmd_output([conf.env.PERL,'-e','printf "%vd",$^V'])
	except:
		conf.fatal('could not determine the perl version')
	conf.env.PERL_VERSION=version
	cver=''
	if minver:
		try:
			ver=tuple(map(int,version.split('.')))
		except:
			conf.fatal('unsupported perl version %r'%version)
		if ver<minver:
			conf.fatal('perl is too old')
		cver='.'.join(map(str,minver))
	conf.check_message('perl',cver,True,version)
def check_perl_module(conf,module):
	cmd=[conf.env['PERL'],'-e','use %s'%module]
	r=Utils.pproc.call(cmd,stdout=Utils.pproc.PIPE,stderr=Utils.pproc.PIPE)==0
	conf.check_message("perl module %s"%module,"",r)
	return r
def check_perl_ext_devel(conf):
	if not conf.env.PERL:
		conf.fatal('perl detection is required first')
	def read_out(cmd):
		return Utils.to_list(Utils.cmd_output([conf.env.PERL,'-MConfig','-e',cmd]))
	conf.env.LINKFLAGS_PERLEXT=read_out('print $Config{lddlflags}')
	conf.env.CPPPATH_PERLEXT=read_out('print "$Config{archlib}/CORE"')
	conf.env.CCFLAGS_PERLEXT=read_out('print "$Config{ccflags} $Config{cccdlflags}"')
	conf.env.XSUBPP=read_out('print "$Config{privlib}/ExtUtils/xsubpp$Config{exe_ext}"')
	conf.env.EXTUTILS_TYPEMAP=read_out('print "$Config{privlib}/ExtUtils/typemap"')
	conf.env.perlext_PATTERN='%s.'+read_out('print $Config{dlext}')[0]
	if getattr(Options.options,'perlarchdir',None):
		conf.env.ARCHDIR_PERL=Options.options.perlarchdir
	else:
		conf.env.ARCHDIR_PERL=read_out('print $Config{sitearch}')[0]
def set_options(opt):
	opt.add_option("--with-perl-binary",type="string",dest="perlbinary",help='Specify alternate perl binary',default=None)
	opt.add_option("--with-perl-archdir",type="string",dest="perlarchdir",help='Specify directory where to install arch specific files',default=None)

before('apply_incpaths','apply_type_vars','apply_lib_vars')(init_perlext)
feature('perlext')(init_perlext)
extension(EXT_XS)(xsubpp_file)
conf(check_perl_version)
conf(check_perl_module)
conf(check_perl_ext_devel)
