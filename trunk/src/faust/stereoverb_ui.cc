//stereoverb
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("RoomSize"), _("RoomSize"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("RoomSize"), _("RoomSize"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("damp"), _("damp"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
	b.insertSpacer();
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.create_small_rackknobr(PARAM("LFO freq"), _("LFO"));
	b.insertSpacer();
	b.create_selector(PARAM("invert"), "invert");
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
}
b.closeBox();
