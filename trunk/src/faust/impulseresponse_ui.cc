// ----- IR
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("peak"), _("Peak"));
b.closeBox();
b.openVerticalBox1("");
{
    b.openHorizontalBox("");
    {
	b.insertSpacer();
	b.create_selector(PARAM("auto_freq"), "auto_freq");
	b.insertSpacer();

	b.openHorizontalTableBox("");
	{
	    b.create_small_rackknob(PARAM("freq"), _("Freq"));
	    b.create_small_rackknob(PARAM("peak"), _("Peak"));
	    b.create_small_rackknob(PARAM("bandwidth"), _("Bandwidth"));
	}
	b.closeBox();
    }
    b.closeBox();
}
b.closeBox();
