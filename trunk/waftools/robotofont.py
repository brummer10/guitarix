import os

def options(opt):
    style = opt.add_option_group("Style Options (installing font)")

    style.add_option('--install-roboto-font',
                    action='store_const',
                    default=False,
                    const=True,
                    help=("install the included roboto condensed font"))

    style.add_option('--fontdir',
                    type='string',
                    help=('roboto condensed font install directory [Default: <prefix>/share/fonts/truetype]'))

    style.add_option('--no-font-cache-update',
                    action='store_const',
                    default=False,
                    const=True,
                    help='dont automatically update font cache')


def check_roboto_font(conf):
    conf.start_msg('Checking for font RobotoCondensed')
    if conf.exec_command("fc-list | grep -q RobotoCondensed") != 0:
        conf.end_msg(False)
        conf.env.FONTMSG = True
    else:
        conf.end_msg(True)

def configure(conf):
    env = conf.env
    opt = conf.options
    if not opt.install_roboto_font:
        check_roboto_font(conf)
    env.FONT = opt.install_roboto_font
    if opt.install_roboto_font:
        if opt.no_font_cache_update:
            env.NO_UPDATE_FONT_CACHE = True
        fontdir = opt.fontdir
        if not fontdir:
            fontdir = os.path.normpath(os.path.join(env.SHAREDIR, 'fonts','truetype'))
        env.GX_FONTS_DIR = fontdir
