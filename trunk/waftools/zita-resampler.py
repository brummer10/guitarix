from waflib.Errors import ConfigurationError

def options(opt):
    comp = opt.add_option_group("Additional Library Options")

    comp.add_option('--includeresampler',
                    action='store_const',
                    default=False,
                    const=True,
                    help='build with included local zita-resample library (Default NO)')

def configure(conf):
    if conf.options.includeresampler:
        conf.env['HAVE_ZITA_RESAMPLER'] = False
        return
    try:
        expected_zita_resampler_version = 1
        code="""
        #include <zita-resampler/resampler.h>
        #include <zita-resampler/resampler-table.h>
        int main() {
            int maj = zita_resampler_major_version();
            if (maj == %d) { return 0; };
            return 1;
        }
        """ % expected_zita_resampler_version
        conf.check_cxx(
            fragment=code,
            lib='zita-resampler',
            uselib_store='ZITA_RESAMPLER',
            msg='Checking for zita-resampler >= %d.0' % expected_zita_resampler_version,
            errmsg="Zita-resampler version %d not found" % expected_zita_resampler_version,
            mandatory=True,
            define_name="ZITA_RESAMPLER")
    except ConfigurationError:
        conf.env['HAVE_ZITA_RESAMPLER'] = False
