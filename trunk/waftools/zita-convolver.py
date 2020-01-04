from waflib.Errors import ConfigurationError

def options(opt):
    comp = opt.add_option_group("Additional Library Options")

    comp.add_option('--includeconvolver',
                    action='store_const',
                    default=False,
                    const=True,
                    help='build with included local zita-convolver libary (Default NO)')

    comp.add_option('--convolver-ffmpeg',
                    action='store_const',
                    default=False,
                    const=True,
                    help='modified zita-convolver libary that uses ffmpeg instead of fftw3 for FFT (Default NO)')

def configure(conf):
    opt = conf.options
    conf.env['HAVE_CONVOLVER_FFMPEG'] = False
    conf.env['HAVE_ZITA_CONVOLVER'] = False
    if opt.includeconvolver:
        conf.define ('ZITA_CONVOLVER_VERSION', 3)
    elif opt.convolver_ffmpeg:
        conf.check_cfg(package='libavcodec', args='--cflags --libs', uselib_store='LIBAVCODEC', mandatory=1)
        conf.check_cfg(package='libavutil', args='--cflags --libs', uselib_store='LIBAVUTIL', mandatory=1)
        conf.env['HAVE_CONVOLVER_FFMPEG'] = True
        conf.define ('CONVOLVER_FFMPEG', 1)
        conf.define ('ZITA_CONVOLVER_VERSION', 3)
    else:
        try:
            expected_zita_convolver_version = 3
            code="""
            #include <zita-convolver.h>
            #if ZITA_CONVOLVER_MAJOR_VERSION != %d
            #error
            #endif
            int main(){ return 0; }
            """ % expected_zita_convolver_version
            conf.check_cxx(
                fragment=code,
                lib="zita-convolver",
                uselib_store='ZITA_CONVOLVER',
                msg='Checking for zita-convolver >= %d.0' % expected_zita_convolver_version,
                errmsg="Zita-convolver version %d not found, trying version 4" % expected_zita_convolver_version,
                mandatory=True,
                define_name="ZITA_CONVOLVER")
            conf.define ('ZITA_CONVOLVER_VERSION', 3)
        except ConfigurationError:
            expected_zita_convolver_version = 4
            code="""
            #include <zita-convolver.h>
            #if ZITA_CONVOLVER_MAJOR_VERSION != %d
            #error
            #endif
            int main(){ return 0; }
            """ % expected_zita_convolver_version
            conf.check_cxx(
                fragment=code,
                lib="zita-convolver",
                uselib_store='ZITA_CONVOLVER',
                msg='Checking for zita-convolver >= %d.0' % expected_zita_convolver_version,
                errmsg="Zita-convolver version %d not found" % expected_zita_convolver_version,
                mandatory=True,
                define_name="ZITA_CONVOLVER")
            conf.define ('ZITA_CONVOLVER_VERSION', 4)

