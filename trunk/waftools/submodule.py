import re, shutil
from waflib import Task, Configure, Logs, Options, Context
from waflib.TaskGen import extension

def check_submodule(conf):
    opt = conf.options
    env = conf.env
    s = conf.cmd_and_log("git submodule update --init --recursive", quiet=True)
    if s:
        conf.msg(msg='Checking for git submodule',result="Update submodule",color='RED')
    else:
        conf.msg(msg='Checking for git submodule',result="Up to Date")

def configure(conf):
    check_submodule(conf)
