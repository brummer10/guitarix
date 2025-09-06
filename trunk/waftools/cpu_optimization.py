import os
import re

def options(opt):
    comp = opt.get_option_group("Configuration options")

    comp.add_option('--debug',
                    action='store_const',
                    default=False,
                    const=True,
                    help='set compiler flags for a debug build')

    comp.add_option('--cxxflags-release',
                    type=str,
                    default='-O3 -DNDEBUG',
                    dest='cxxflags_release',
                    help='additional C++ compiler flags for release version (not used if --debug) [Default: -O3 -DNDEBUG]')

    comp.add_option('--cxxflags-debug',
                    type=str,
                    default='-O2 -g -fstack-protector-all',
                    dest='cxxflags_debug',
                    help='additional C++ compiler flags for debug version (only used if --debug) [Default: -O2 -g -fstack-protector-all]')

    comp.add_option('--cxxflags',
                    type=str,
                    default='-Wall -DGSEAL_ENABLE', # -fomit-frame-pointer -ffast-math -fstrength-reduce -mmmx -mfpmath=sse -DUSE_XMMINTRIN -pipe
                    dest='cxxflags',
                    help='C++ base compiler flags [Default: -Wall -DGSEAL_ENABLE]')

    comp.add_option('--ldflags',
                    type=str,
                    default='',
                    dest='ldflags',
                    help='C++ base linker flags ')

    comp.add_option('--optimization',
                    action='store_const',
                    default=False, #'-fomit-frame-pointer -ffast-math -fstrength-reduce -pipe',
                    const=True,
                    help='automatically select additional C++ compiler optimization flags for the current platform')


def check_cloop(conf):
    code = """
    int
    main (void)
    {
    #define max(x, y) (((x) > (y)) ? (x) : (y))
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    for (int p1=0;p1<=5;p1++) {
        for (int p2=0;p2<=10;p2++) {
            for (int i=max(2*p1,0);i<=min(10,2*p1+1);i++) {
                for (int j=max(2*p2,0);j<=min(20,2*p2+1);j++) {
                    ;
                }
            }
        }
    }
    return 0;
    }
    """
    msg = "Checking for libcloog-ppl0"
    conf.check_cxx(msg = msg, fragment=code, cxxflags=[ '-O3', '-ftree-loop-linear'], define_name="NOOPT", mandatory=0)

def check_v3 (conf, x86_flags):
    if conf.env['IS_LINUX']:
        FLAGS_v3  = ['avx', 'avx2', 'bmi1', 'bmi2', 'f16c', 'fma', 'abm', 'movbe', 'xsave']
        res = True
        s = 'yes'
        f = 'None'
        for el in FLAGS_v3:
            if el not in x86_flags:
                res = False
                s = "not found"
                f = "YELLOW"
                break
    conf.display_msg_1("Checking for x86-64-v3 support", s, f)
    return res

def detect_pi_model():
    """
    Detects and returns the Raspberry Pi board model.
    Returns a string representing the model, or None if not found or on a non-Pi system.
    """
    try:
        with open('/proc/device-tree/model', 'r') as f:
            model = f.read().strip()
            return model
    except FileNotFoundError:
        # This file only exists on Raspberry Pi devices
        return None

def append_optimization_flags(conf, cxxflags):
    cpu_model = None
    x86_flags = None
    try:
        for line in open("/proc/cpuinfo"):
            if cpu_model is None:
                if line.startswith("model name"):
                    cpu_model = line.split(":",1)[1].strip()
            elif x86_flags is None:
                if line.startswith("flags"):
                    x86_flags = line.split(":",1)[1].strip()
            else:
                break
    except IOError:
        pass
    if cpu_model is None or x86_flags is None:
        try:
            v = os.popen('lscpu').read()
            for line in v.splitlines():
                if cpu_model is None:
                    if line.startswith("Model name"):
                        cpu_model = line.split(":",1)[1].strip()
                elif x86_flags is None:
                    if line.startswith("Flags"):
                        x86_flags = line.split(":",1)[1].strip()
                else:
                    break
        except IOError:
            pass
    if cpu_model is None or x86_flags is None:
        conf.display_msg_1("Checking CPU Architecture",
                         "cpu model not found in /proc/cpuinfo",
                         "YELLOW")
        return None
    
    model = cpu_model.split()
    arch = os.uname()[4]

    pi_model = detect_pi_model()
    
    if check_v3(conf, x86_flags):
        cxxflags.append ("-march=x86-64-v3")
    elif "AMD" in model and "x86_64" in arch:
        cxxflags.append ("-march=k8")
    elif "AMD" in model and "Sempron(tm)" in model:
        cxxflags.append ("-march=native")
    elif "Geode" in model :
        cxxflags.append ("-march=geode")
    elif "Core" in model and "x86_64" in arch:
        cxxflags.append ("-march=core2")
    elif "Cortex-A76" in model : # PI 5
        cxxflags.append ("-march=armv8-a")
        cxxflags.append ("-mtune=cortex-a76")
    elif "Cortex-A72" in model : # PI 4
        cxxflags.append ("-march=armv8-a")
        cxxflags.append ("-mtune=cortex-a72")
    elif "Cortex-A53" in model : # PI 3
        cxxflags.append ("-march=armv8-a")
        cxxflags.append ("-mtune=cortex-a53")
    elif pi_model != None and "Raspberry Pi" in pi_model:
        cxxflags.extend (["-mcpu=native", "-march=native", "-mtune=native"])
    elif "i386" in arch:
        cxxflags.append ("-march=i386")
    elif "i486" in arch:
        cxxflags.append ("-march=i486")
    elif "i586" in arch:
        cxxflags.append ("-march=i586")
    elif "i686" in arch:
        cxxflags.append ("-march=i686")
    else:
        cxxflags.append ("-march=native")

    if "mmx" in x86_flags:
        cxxflags.append ("-mmmx")
    if "3dnow" in x86_flags:
        cxxflags.append ("-m3dnow")

    if "sse5" in x86_flags:
        cxxflags.append ("-msse5")
        cxxflags.append ("-mfpmath=sse")
    elif "sse4_2" in x86_flags:
        cxxflags.append ("-msse4.2")
        cxxflags.append ("-mfpmath=sse")
    elif "sse4_1" in x86_flags:
        cxxflags.append ("-msse4.1")
        cxxflags.append ("-mfpmath=sse")
    elif "ssse3" in x86_flags:
        cxxflags.append ("-mssse3")
        cxxflags.append ("-mfpmath=sse")
    elif "sse4a" in x86_flags:
        cxxflags.append ("-msse4a")
        cxxflags.append ("-mfpmath=sse")
    elif "sse4" in x86_flags:
        cxxflags.append ("-msse4")
        cxxflags.append ("-mfpmath=sse")
    elif "sse3" in x86_flags:
        cxxflags.append ("-msse3")
        cxxflags.append ("-mfpmath=sse")
    elif "sse2" in x86_flags:
        cxxflags.append ("-msse2")
        cxxflags.append ("-mfpmath=sse")
        #cxxflags.append ("-DUSE_XMMINTRIN")
    elif "sse" in x86_flags:
        cxxflags.append ("-msse")
        cxxflags.append ("-mfpmath=sse")
        # cxxflags.append ("-DUSE_XMMINTRIN")

    if not conf.options.debug:
        cxxflags.append ("-fomit-frame-pointer")
    if conf.env['NOOPT']:
        cxxflags.append ("-ftree-loop-linear")
    #cxxflags.append ("-ffinite-math-only")
    cxxflags.append ("-fno-math-errno")
    cxxflags.append ("-fno-signed-zeros")
    #cxxflags.append ("-ffast-math") # quicker but doesn't seem to work (difference in sound output)
    #cxxflags.append ("-malign-double")
    if any('clang' not in s for s in conf.env["CXX"]):
        cxxflags.append ("-fstrength-reduce")
    cxxflags.append ("-pipe")
    return cpu_model


def configure(conf):
    opt = conf.options
    # g++ flags
    cxxflags = opt.cxxflags.split()
    if opt.debug:
        cxxflags += opt.cxxflags_debug.split()
    else:
        cxxflags += opt.cxxflags_release.split()
    if  opt.enable_lfs:
        cxxflags.append ("-D_FILE_OFFSET_BITS=64")
    cpu_model = None
    if opt.optimization:
        check_cloop(conf)
        #if conf.env['NOOPT']:
        conf.env['OPT'] = False
        cpu_model = append_optimization_flags(conf, cxxflags)

    if any(x.startswith('-flto') for x in cxxflags):
        conf.env['LTO'] = True
        if any('clang' not in s for s in conf.env["CXX"]):
            cxxflags.append ("-ffat-lto-objects")

    cxxflags.append ("-std=c++20")
   # cxxflags.append ("-Ofast")
    cxxflags.append ("-DDSP_SAMPLE_FLOAT")
    cxxflags.append ("-DNAM_SAMPLE_FLOAT")
    cxxflags.append ("-Dneural_amp_modeler_EXPORTS")
    cxxflags.append ("-DRTNEURAL_DEFAULT_ALIGNMENT=32")
    cxxflags.append ("-DRTNEURAL_USE_EIGEN=1")
    cxxflags.append ("-DRTNEURAL_NAMESPACE=RTNeural")
    conf.env['CXXFLAGS'] += cxxflags
    conf.cpu_model = cpu_model
