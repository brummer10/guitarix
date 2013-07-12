// ----- IR
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("peak"), _("peak"));
b.closeBox();
b.openVerticalBox1("");
{
    b.openHorizontalBox("");
    {
	b.insertSpacer();
	b.create_selector(PARAM("auto_freq"), 0);
	b.insertSpacer();

	b.openHorizontalTableBox("");
	{
	    b.create_small_rackknob(PARAM("freq"), _(" freq "));
	    b.create_small_rackknob(PARAM("peak"), _(" peak "));
	    b.create_small_rackknob(PARAM("bandwidth"), _(" bandwidth "));
	}
	b.closeBox();
    }
    b.closeBox();
}
b.closeBox();
