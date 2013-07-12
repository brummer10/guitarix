b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalTableBox("");
{
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level1"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak1"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth1"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level2"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak2"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth2"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level3"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak3"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth3"), _("bandwidth"));
    }
    b.closeBox();
    b.openVerticalBox1("");
    {
	b.create_small_rackknob(PARAM("level4"), _("peak"));
	b.insertSpacer();
	b.create_spin_value(PARAM("peak4"), _("frequency"));
	b.insertSpacer();
	b.create_spin_value(PARAM("bandwidth4"), _("bandwidth"));
    }
    b.closeBox();
}
b.closeBox();
