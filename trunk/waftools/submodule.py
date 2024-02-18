import re, shutil
from waflib import Task, Configure, Logs, Options, Context
from waflib.Errors import WafError, ConfigurationError
from waflib.TaskGen import extension

def check_submodule(conf):
    opt = conf.options
    env = conf.env
    try:
        s = conf.cmd_and_log("git submodule update --init --recursive", quiet=True)
        if s:
            conf.msg(msg='Checking for git submodule',result="update submodule",color='RED')
        else:
            conf.msg(msg='Checking for git submodule',result="up to date")
    except WafError:
        conf.msg(msg='Checking for git submodule',result="not checked",color='YELLOW')

def configure(conf):
    check_submodule(conf)
