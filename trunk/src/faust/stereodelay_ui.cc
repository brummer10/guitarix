// stereo delay
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("l_gain"), _("left gain"));
    b.create_small_rackknob(PARAM("l_delay"), _("left delay"));
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("LFO freq"), _("LFO"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), 0);
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
    b.create_small_rackknob(PARAM("r_gain"), _("right gain"));
    b.create_small_rackknob(PARAM("r_delay"), _("right delay"));
}
b.closeBox();
