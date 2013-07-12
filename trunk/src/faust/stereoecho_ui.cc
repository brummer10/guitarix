// echo
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_l"), _("left %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("time_l"), _("left time"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("LFO freq"), _("LFO"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), 0);
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("percent_r"), _("right %"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("time_r"), _("right time"));
	b.insertSpacer();
    }
    b.closeBox();
}
b.closeBox();
