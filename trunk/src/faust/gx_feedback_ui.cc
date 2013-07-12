b.openHorizontalhideBox("");
b.create_master_slider(PARAM("feedback"),  _("feedback"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("feedback"),  _("feedback"));
	b.create_small_rackknob(PARAM("wet_dry"),  _("dry/wet"));
    }
    b.closeBox();
}
b.closeBox();
