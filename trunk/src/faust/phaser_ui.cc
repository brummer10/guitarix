// phaser
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("level"), _("  level "));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob(PARAM("feedback gain"), _(" feedback "));
	    b.create_small_rackknob(PARAM("depth"), _("depth"));
	    b.create_small_rackknob(PARAM("Notch width"), _("width"));
	    b.create_small_rackknob(PARAM("NotchFreq"), _("freq"));
	    b.create_small_rackknob(PARAM("MaxNotch1Freq"), _("max Hz"));
	    b.create_small_rackknob(PARAM("MinNotch1Freq"), _("min Hz"));
	    b.create_small_rackknob(PARAM("lfobpm"), _("speed (bpm)"));
	}
	b.closeBox();
	b.insertSpacer();
	b.openHorizontalBox("");
	{
	    b.insertSpacer();
	    b.create_selector(PARAM("invert"), "invert");
	    b.insertSpacer();
	    b.create_selector(PARAM("VibratoMode"),"VibratoMode" );
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
