// flanger
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("  level  "));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob(PARAM("feedback gain"), _(" feedback "));
	    b.create_small_rackknob(PARAM("depth"), _("  depth  "));
	    b.create_small_rackknob(PARAM("flange delay"), _("  delay  "));
	    b.create_small_rackknob(PARAM("flange delay offset"), _(" delay offset"));
	    b.create_small_rackknob(PARAM("lfobpm"), _(" LFO freq (bpm)"));
	}
	b.closeBox();
	b.insertSpacer();
	b.openHorizontalBox("");
	{
	    b.insertSpacer();
	    b.create_selector(PARAM("invert"), "invert");
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	    b.insertSpacer();
	}
	b.closeBox();
	b.openFrameBox("");
	b.closeBox();
    }
    b.closeBox();
}
b.closeBox();
