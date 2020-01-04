def options(opt):
    comp = opt.add_option_group("Additional Library Options")

    comp.add_option('--includeresampler',
                    action='store_const',
                    default=False,
                    const=True,
                    help='build with included local zita-resample libary (Default NO)')

def configure(conf):
    if conf.options.includeresampler:
        conf.env['HAVE_ZITA_RESAMPLER'] = False
        return
    expected_zita_resampler_version = 1
    code="""
    #include <zita-resampler/resampler.h>
    #include <zita-resampler/resampler-table.h>
    #if ZITA_RESAMPLER_MAJOR_VERSION != %d
    #error
    #endif
    int main(){ return 0; }
    """ % expected_zita_resampler_version
    conf.check_cxx(
        fragment=code,
        lib='zita-resampler',
        uselib_store='ZITA_RESAMPLER',
        msg='Checking for zita-resampler >= %d.0' % expected_zita_resampler_version,
        errmsg="Zita-resampler version %d not found" % expected_zita_resampler_version,
        mandatory=True,
        define_name="ZITA_RESAMPLER")
