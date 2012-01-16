#! /usr/bin/env python
# encoding: utf-8
import sys
if sys.hexversion < 0x020400f0: from sets import Set as set
import os,sys,re,optparse
import ccroot
import TaskGen,Utils,Task,Configure,Logs,Build
from Logs import debug,error
from TaskGen import taskgen,feature,after,before,extension
from Configure import conftest
EXT_D=['.d','.di','.D']
D_METHS=['apply_core','apply_vnum','apply_objdeps']
DLIB="""
version(D_Version2) {
	import std.stdio;
	int main() {
		writefln("phobos2");
		return 0;
	}
} else {
	version(Tango) {
		import tango.stdc.stdio;
		int main() {
			printf("tango");
			return 0;
		}
	} else {
		import std.stdio;
		int main() {
			writefln("phobos1");
			return 0;
		}
	}
}
"""
def filter_comments(filename):
	txt=Utils.readf(filename)
	i=0
	buf=[]
	max=len(txt)
	begin=0
	while i<max:
		c=txt[i]
		if c=='"'or c=="'":
			buf.append(txt[begin:i])
			delim=c
			i+=1
			while i<max:
				c=txt[i]
				if c==delim:break
				elif c=='\\':
					i+=1
				i+=1
			i+=1
			begin=i
		elif c=='/':
			buf.append(txt[begin:i])
			i+=1
			if i==max:break
			c=txt[i]
			if c=='+':
				i+=1
				nesting=1
				c=None
				while i<max:
					prev=c
					c=txt[i]
					if prev=='/'and c=='+':
						nesting+=1
						c=None
					elif prev=='+'and c=='/':
						nesting-=1
						if nesting==0:break
						c=None
					i+=1
			elif c=='*':
				i+=1
				c=None
				while i<max:
					prev=c
					c=txt[i]
					if prev=='*'and c=='/':break
					i+=1
			elif c=='/':
				i+=1
				while i<max and txt[i]!='\n':
					i+=1
			else:
				begin=i-1
				continue
			i+=1
			begin=i
			buf.append(' ')
		else:
			i+=1
	buf.append(txt[begin:])
	return buf
class d_parser(object):
	def __init__(self,env,incpaths):
		self.allnames=[]
		self.re_module=re.compile("module\s+([^;]+)")
		self.re_import=re.compile("import\s+([^;]+)")
		self.re_import_bindings=re.compile("([^:]+):(.*)")
		self.re_import_alias=re.compile("[^=]+=(.+)")
		self.env=env
		self.nodes=[]
		self.names=[]
		self.incpaths=incpaths
	def tryfind(self,filename):
		found=0
		for n in self.incpaths:
			found=n.find_resource(filename.replace('.','/')+'.d')
			if found:
				self.nodes.append(found)
				self.waiting.append(found)
				break
		if not found:
			if not filename in self.names:
				self.names.append(filename)
	def get_strings(self,code):
		self.module=''
		lst=[]
		mod_name=self.re_module.search(code)
		if mod_name:
			self.module=re.sub('\s+','',mod_name.group(1))
		import_iterator=self.re_import.finditer(code)
		if import_iterator:
			for import_match in import_iterator:
				import_match_str=re.sub('\s+','',import_match.group(1))
				bindings_match=self.re_import_bindings.match(import_match_str)
				if bindings_match:
					import_match_str=bindings_match.group(1)
				matches=import_match_str.split(',')
				for match in matches:
					alias_match=self.re_import_alias.match(match)
					if alias_match:
						match=alias_match.group(1)
					lst.append(match)
		return lst
	def start(self,node):
		self.waiting=[node]
		while self.waiting:
			nd=self.waiting.pop(0)
			self.iter(nd)
	def iter(self,node):
		path=node.abspath(self.env)
		code="".join(filter_comments(path))
		names=self.get_strings(code)
		for x in names:
			if x in self.allnames:continue
			self.allnames.append(x)
			self.tryfind(x)
def scan(self):
	env=self.env
	gruik=d_parser(env,env['INC_PATHS'])
	gruik.start(self.inputs[0])
	if Logs.verbose:
		debug('deps: nodes found for %s: %s %s'%(str(self.inputs[0]),str(gruik.nodes),str(gruik.names)))
	return(gruik.nodes,gruik.names)
def get_target_name(self):
	v=self.env
	tp='program'
	for x in self.features:
		if x in['dshlib','dstaticlib']:
			tp=x.lstrip('d')
	return v['D_%s_PATTERN'%tp]%self.target
d_params={'dflags':'','importpaths':'','libs':'','libpaths':'','generate_headers':False,}
def init_d(self):
	for x in d_params:
		setattr(self,x,getattr(self,x,d_params[x]))
class d_taskgen(TaskGen.task_gen):
	def __init__(self,*k,**kw):
		TaskGen.task_gen.__init__(self,*k,**kw)
		if len(k)>1:
			self.features.append('d'+k[1])
TaskGen.bind_feature('d',D_METHS)
def init_d(self):
	Utils.def_attrs(self,dflags='',importpaths='',libs='',libpaths='',uselib='',uselib_local='',generate_headers=False,compiled_tasks=[],add_objects=[],link_task=None)
def apply_d_libs(self):
	env=self.env
	self.uselib=self.to_list(self.uselib)
	names=self.to_list(self.uselib_local)
	seen=set([])
	tmp=Utils.deque(names)
	while tmp:
		lib_name=tmp.popleft()
		if lib_name in seen:
			continue
		y=self.name_to_obj(lib_name)
		if not y:
			raise Utils.WafError('object %r was not found in uselib_local (required by %r)'%(lib_name,self.name))
		y.post()
		seen.add(lib_name)
		if getattr(y,'uselib_local',None):
			lst=y.to_list(y.uselib_local)
			if'dshlib'in y.features or'dprogram'in y.features:
				lst=[x for x in lst if not'dstaticlib'in self.name_to_obj(x).features]
			tmp.extend(lst)
		if getattr(y,'link_task',None):
			link_name=y.target[y.target.rfind(os.sep)+1:]
			if'dstaticlib'in y.features or'dshlib'in y.features:
				env.append_unique('DLINKFLAGS',env.DLIB_ST%link_name)
				env.append_unique('DLINKFLAGS',env.DLIBPATH_ST%y.link_task.outputs[0].parent.bldpath(env))
			self.link_task.set_run_after(y.link_task)
			dep_nodes=getattr(self.link_task,'dep_nodes',[])
			self.link_task.dep_nodes=dep_nodes+y.link_task.outputs
		for v in self.to_list(y.uselib):
			if not v in self.uselib:
				self.uselib.insert(0,v)
		if getattr(y,'export_incdirs',None):
			for x in self.to_list(y.export_incdirs):
				node=y.path.find_dir(x)
				if not node:
					raise Utils.WafError('object %r: invalid folder %r in export_incdirs'%(y.target,x))
				self.env.append_unique('INC_PATHS',node)
def apply_d_link(self):
	link=getattr(self,'link',None)
	if not link:
		if'dstaticlib'in self.features:link='static_link'
		else:link='d_link'
	outputs=[t.outputs[0]for t in self.compiled_tasks]
	self.link_task=self.create_task(link,outputs,self.path.find_or_declare(get_target_name(self)))
def apply_d_vars(self):
	env=self.env
	dpath_st=env['DPATH_ST']
	lib_st=env['DLIB_ST']
	libpath_st=env['DLIBPATH_ST']
	importpaths=self.to_list(self.importpaths)
	libpaths=[]
	libs=[]
	uselib=self.to_list(self.uselib)
	for i in uselib:
		if env['DFLAGS_'+i]:
			env.append_unique('DFLAGS',env['DFLAGS_'+i])
	for x in self.features:
		if not x in['dprogram','dstaticlib','dshlib']:
			continue
		x.lstrip('d')
		d_shlib_dflags=env['D_'+x+'_DFLAGS']
		if d_shlib_dflags:
			env.append_unique('DFLAGS',d_shlib_dflags)
	for i in uselib:
		if env['DPATH_'+i]:
			for entry in self.to_list(env['DPATH_'+i]):
				if not entry in importpaths:
					importpaths.append(entry)
	for path in importpaths:
		if os.path.isabs(path):
			env.append_unique('_DIMPORTFLAGS',dpath_st%path)
		else:
			node=self.path.find_dir(path)
			self.env.append_unique('INC_PATHS',node)
			env.append_unique('_DIMPORTFLAGS',dpath_st%node.srcpath(env))
			env.append_unique('_DIMPORTFLAGS',dpath_st%node.bldpath(env))
	for i in uselib:
		if env['LIBPATH_'+i]:
			for entry in self.to_list(env['LIBPATH_'+i]):
				if not entry in libpaths:
					libpaths.append(entry)
	libpaths=self.to_list(self.libpaths)+libpaths
	for path in libpaths:
		if not os.path.isabs(path):
			node=self.path.find_resource(path)
			if not node:
				raise Utils.WafError('could not find libpath %r from %r'%(path,self))
			path=node.abspath(self.env)
		env.append_unique('DLINKFLAGS',libpath_st%path)
	for i in uselib:
		if env['LIB_'+i]:
			for entry in self.to_list(env['LIB_'+i]):
				if not entry in libs:
					libs.append(entry)
	libs.extend(self.to_list(self.libs))
	for flag in self.to_list(self.dflags):
		env.append_unique('DFLAGS',flag)
	for lib in libs:
		env.append_unique('DLINKFLAGS',lib_st%lib)
	for i in uselib:
		dlinkflags=env['DLINKFLAGS_'+i]
		if dlinkflags:
			for linkflag in dlinkflags:
				env.append_unique('DLINKFLAGS',linkflag)
def add_shlib_d_flags(self):
	for linkflag in self.env['D_shlib_LINKFLAGS']:
		self.env.append_unique('DLINKFLAGS',linkflag)
def d_hook(self,node):
	task=self.create_task(self.generate_headers and'd_with_header'or'd')
	try:obj_ext=self.obj_ext
	except AttributeError:obj_ext='_%d.o'%self.idx
	task.inputs=[node]
	task.outputs=[node.change_ext(obj_ext)]
	self.compiled_tasks.append(task)
	if self.generate_headers:
		header_node=node.change_ext(self.env['DHEADER_ext'])
		task.outputs+=[header_node]
d_str='${D_COMPILER} ${DFLAGS} ${_DIMPORTFLAGS} ${D_SRC_F}${SRC} ${D_TGT_F}${TGT}'
d_with_header_str='${D_COMPILER} ${DFLAGS} ${_DIMPORTFLAGS} \
${D_HDR_F}${TGT[1].bldpath(env)} \
${D_SRC_F}${SRC} \
${D_TGT_F}${TGT[0].bldpath(env)}'
link_str='${D_LINKER} ${DLNK_SRC_F}${SRC} ${DLNK_TGT_F}${TGT} ${DLINKFLAGS}'
def override_exec(cls):
	old_exec=cls.exec_command
	def exec_command(self,*k,**kw):
		if isinstance(k[0],list):
			lst=k[0]
			for i in xrange(len(lst)):
				if lst[i]=='-of':
					del lst[i]
					lst[i]='-of'+lst[i]
					break
		return old_exec(self,*k,**kw)
	cls.exec_command=exec_command
cls=Task.simple_task_type('d',d_str,'GREEN',before='static_link d_link',shell=False)
cls.scan=scan
override_exec(cls)
cls=Task.simple_task_type('d_with_header',d_with_header_str,'GREEN',before='static_link d_link',shell=False)
override_exec(cls)
cls=Task.simple_task_type('d_link',link_str,color='YELLOW',shell=False)
override_exec(cls)
def generate_header(self,filename,install_path):
	if not hasattr(self,'header_lst'):self.header_lst=[]
	self.meths.append('process_header')
	self.header_lst.append([filename,install_path])
def process_header(self):
	env=self.env
	for i in getattr(self,'header_lst',[]):
		node=self.path.find_resource(i[0])
		if not node:
			raise Utils.WafError('file not found on d obj '+i[0])
		task=self.create_task('d_header')
		task.set_inputs(node)
		task.set_outputs(node.change_ext('.di'))
d_header_str='${D_COMPILER} ${D_HEADER} ${SRC}'
Task.simple_task_type('d_header',d_header_str,color='BLUE',shell=False)
def d_platform_flags(conf):
	v=conf.env
	binfmt=v.DEST_BINFMT or Utils.unversioned_sys_platform_to_binary_format(v.DEST_OS or Utils.unversioned_sys_platform())
	if binfmt=='pe':
		v['D_program_PATTERN']='%s.exe'
		v['D_shlib_PATTERN']='lib%s.dll'
		v['D_staticlib_PATTERN']='lib%s.a'
	else:
		v['D_program_PATTERN']='%s'
		v['D_shlib_PATTERN']='lib%s.so'
		v['D_staticlib_PATTERN']='lib%s.a'
def check_dlibrary(conf):
	ret=conf.check_cc(features='d dprogram',fragment=DLIB,mandatory=True,compile_filename='test.d',execute=True)
	conf.env.DLIBRARY=ret.strip()

feature('d')(init_d)
before('apply_type_vars')(init_d)
feature('d')(init_d)
before('apply_d_libs')(init_d)
feature('d')(apply_d_libs)
after('apply_d_link','init_d')(apply_d_libs)
before('apply_vnum','apply_d_vars')(apply_d_libs)
feature('dprogram','dshlib','dstaticlib')(apply_d_link)
after('apply_core')(apply_d_link)
feature('d')(apply_d_vars)
after('apply_core')(apply_d_vars)
feature('dshlib')(add_shlib_d_flags)
after('apply_d_vars')(add_shlib_d_flags)
extension(EXT_D)(d_hook)
taskgen(generate_header)
before('apply_core')(process_header)
conftest(d_platform_flags)
conftest(check_dlibrary)
