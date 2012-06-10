#! /usr/bin/env python
# encoding: utf-8

import os
all_modifs={}
def modif(dir,name,fun):
	if name=='*':
		lst=[]
		for y in'. Tools 3rdparty'.split():
			for x in os.listdir(os.path.join(dir,y)):
				if x.endswith('.py'):
					lst.append(y+os.sep+x)
		for x in lst:
			modif(dir,x,fun)
		return
	filename=os.path.join(dir,name)
	f=open(filename,'r')
	txt=f.read()
	f.close()
	txt=fun(txt)
	f=open(filename,'w')
	f.write(txt)
	f.close()
def subst(filename):
	def do_subst(fun):
		global all_modifs
		try:
			all_modifs[filename]+=fun
		except KeyError:
			all_modifs[filename]=[fun]
		return fun
	return do_subst
def r1(code):
	code=code.replace("'iluvcuteoverload'","b'iluvcuteoverload'")
	code=code.replace("ABI=7","ABI=37")
	return code
def r2(code):
	code=code.replace("p.stdin.write('\\n')","p.stdin.write(b'\\n')")
	code=code.replace('p.communicate()[0]','p.communicate()[0].decode("utf-8")')
	return code
def r3(code):
	code=code.replace("m.update(str(lst))","m.update(str(lst).encode())")
	code=code.replace('p.communicate()[0]','p.communicate()[0].decode("utf-8")')
	return code
def r33(code):
	code=code.replace('unicode','str')
	return code
def r4(code):
	code=code.replace("up(self.__class__.__name__)","up(self.__class__.__name__.encode())")
	code=code.replace("up(self.env.variant())","up(self.env.variant().encode())")
	code=code.replace("up(x.parent.abspath())","up(x.parent.abspath().encode())")
	code=code.replace("up(x.name)","up(x.name.encode())")
	code=code.replace('class TaskBase(object):\n\t__metaclass__=store_task_type','import binascii\n\nclass TaskBase(object, metaclass=store_task_type):')
	code=code.replace('keys=self.cstr_groups.keys()','keys=list(self.cstr_groups.keys())')
	code=code.replace("sig.encode('hex')",'binascii.hexlify(sig)')
	code=code.replace("os.path.join(Options.cache_global,ssig)","os.path.join(Options.cache_global,ssig.decode())")
	return code
def r5(code):
	code=code.replace("cPickle.dump(data,file,-1)","cPickle.dump(data,file)")
	code=code.replace('for node in src_dir_node.childs.values():','for node in list(src_dir_node.childs.values()):')
	return code
def r6(code):
	code=code.replace('range','range')
	code=code.replace('items','items')
	code=code.replace('maxsize','maxsize')
	code=code.replace('keys','keys')
	code=code.replace('Error as e:','Error as e:')
	code=code.replace('Exception as e:','Exception as e:')
	return code
def r7(code):
	code=code.replace('class task_gen(object):\n\t__metaclass__=register_obj','class task_gen(object, metaclass=register_obj):')
	return code
def r8(code):
	code=code.replace('proc.communicate()[0]','proc.communicate()[0].decode("utf-8")')
	return code
def r9(code):
	code=code.replace('f.write(c)','f.write(c.encode("utf-8"))')
	return code
def r10(code):
	code=code.replace("key=kw['success']","key=kw['success']\n\t\t\t\ttry:\n\t\t\t\t\tkey=key.decode('utf-8')\n\t\t\t\texcept:\n\t\t\t\t\tpass")
	code=code.replace('out=str(out)','out=out.decode("utf-8")')
	code=code.replace('err=str(err)','err=err.decode("utf-8")')
	return code
def r11(code):
	code=code.replace('ret.strip()','ret.strip().decode("utf-8")')
	return code
def fixdir(dir):
	global all_modifs
	for k in all_modifs:
		for v in all_modifs[k]:
			modif(os.path.join(dir,'wafadmin'),k,v)

subst('Constants.py')(r1)
subst('Tools/ccroot.py')(r2)
subst('Utils.py')(r3)
subst('ansiterm.py')(r33)
subst('Task.py')(r4)
subst('Build.py')(r5)
subst('*')(r6)
subst('TaskGen.py')(r7)
subst('Tools/python.py')(r8)
subst('Tools/glib2.py')(r9)
subst('Tools/config_c.py')(r10)
subst('Tools/d.py')(r11)
