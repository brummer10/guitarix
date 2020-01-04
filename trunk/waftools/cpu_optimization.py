import os

def options(opt):
    comp = opt.get_option_group("Configuration options")

    comp.add_option('--debug',
                    action='store_const',
                    default=False,
                    const=True,
                    help='set compiler flags for a debug build')

    comp.add_option('--cxxflags-release',
                    type='string',
                    default='-O3 -DNDEBUG',
                    dest='cxxflags_release',
                    help='additional C++ compiler flags for release version (not used if --debug) [Default: %default]')

    comp.add_option('--cxxflags-debug',
                    type='string',
                    default='-O2 -g -fstack-protector-all',
                    dest='cxxflags_debug',
                    help='additional C++ compiler flags for debug version (only used if --debug) [Default: %default]')

    comp.add_option('--cxxflags',
                    type='string',
                    default='-Wall -DGSEAL_ENABLE', # -fomit-frame-pointer -ffast-math -fstrength-reduce -mmmx -mfpmath=sse -DUSE_XMMINTRIN -pipe
                    dest='cxxflags',
                    help='C++ base compiler flags [Default: %default]')

    comp.add_option('--disable-cxx11',
                    action='store_const',
                    default=False,
                    const=True,
                    help='deselect C++ compiler flag -std=c++11 [Default: False]')

    comp.add_option('--ldflags',
                    type='string',
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
    conf.check_cxx(msg = msg, fragment=code, cxxflags=[ '-O3', '-ftree-loop-linear'], define_name="NOOPT")

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
        conf.display_msg("Checking CPU Architecture",
                         "cpu model not found in /proc/cpuinfo",
                         "YELLOW")
        return None
    model = cpu_model.split()
    arch = os.uname()[4]
    if "AMD" in model and "x86_64" in arch:
        cxxflags.append ("-march=k8")
    elif "AMD" in model and "Sempron(tm)" in model:
        cxxflags.append ("-march=native")
    elif "Geode" in model :
        cxxflags.append ("-march=geode")
    elif "Core" in model and "x86_64" in arch:
        cxxflags.append ("-march=core2")
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
    cxxflags.append ("-ftree-loop-linear")
    #cxxflags.append ("-ffinite-math-only")
    cxxflags.append ("-fno-math-errno")
    cxxflags.append ("-fno-signed-zeros")
    #cxxflags.append ("-ffast-math") # quicker but doesn't seem to work (difference in sound output)
    #cxxflags.append ("-malign-double")
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
        if conf.env['NOOPT']:
            conf.env['OPT'] = False
            cpu_model = append_optimization_flags(conf, cxxflags)
    if not opt.disable_cxx11:
        cxxflags.append ("-std=c++11")
    conf.env['CXXFLAGS'] += cxxflags
    conf.cpu_model = cpu_model
