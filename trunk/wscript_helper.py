def add_zita_convolver(bld, uselib, sources, incl, base=".."):
    uselib.append('ZITA_CONVOLVER')

def add_zita_resampler(bld, uselib, sources, incl, base=".."):
    uselib.append('ZITA_RESAMPLER')

def get_faust_args(bld):
    float_arg = ["-s","40000","--float"]
    double_arg = ["--double"]
    if bld.env['FAUST_DOUBLE']:
        arg = ["--double"]
    else:
        arg = ["--float"]
    if bld.env['FAUST_VECTORIZE']:
        float_arg.append('--vectorize')
        arg.append('--vectorize')
        double_arg.append('--vectorize')
    elif bld.env['FAUST_VECTORIZE_FLOAT']:
        float_arg.append('--vectorize')
        if not bld.env['FAUST_DOUBLE']:
            arg.append('--vectorize')
    add_args = bld.env['FAUST_OPTIONS']
    if add_args:
        add_args = "--add=%s" % add_args
        float_arg.append(add_args)
        double_arg.append(add_args)
        arg.append(add_args)
    return arg, float_arg, double_arg
