def add_zita_convolver(bld, uselib, sources, incl, base=".."):
    if bld.env['ZITA_CONVOLVER']:
        uselib.append('ZITA_CONVOLVER')
    elif bld.env['CONVOLVER_FFMPEG']:
        sources.append(base+'/zita-convolver-ffmpeg/zita-convolver.cc')
        incl.append(base+'/zita-convolver-ffmpeg');
        uselib.append('LIBAVCODEC')
    else:
        sources.append(base+'/zita-convolver/zita-convolver.cc')
        incl.append(base+'/zita-convolver');

def add_zita_resampler(bld, uselib, sources, incl, base=".."):
    if bld.env['ZITA_RESAMPLER']:
        uselib.append('ZITA_RESAMPLER')
    else:
        sources.append(base+'/zita-resampler-1.1.0/resampler.cc')
        sources.append(base+'/zita-resampler-1.1.0/resampler-table.cc')
        incl.append(base+'/zita-resampler-1.1.0')

def get_faust_args(bld):
    float_arg = ["-s","40000","--float"]
    if bld.env['FAUST_DOUBLE']:
        arg = ["--double"]
    else:
        arg = ["--float"]
    if bld.env['FAUST_VECTORIZE']:
        float_arg.append('--vectorize')
        arg.append('--vectorize')
    add_args = bld.env['FAUST_OPTIONS']
    if add_args:
        add_args = "--add=%s" % add_args
        float_arg.append(add_args)
        arg.append(add_args)
    return arg, float_arg
