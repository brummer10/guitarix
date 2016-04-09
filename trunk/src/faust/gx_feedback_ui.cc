b.openHorizontalhideBox("");
b.create_master_slider(PARAM("feedback"),  _("Feedback"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknobr(PARAM("feedback"),  _("Feedback"));
	b.create_small_rackknob(PARAM("wet_dry"),  _("Dry/Wet"));
    }
    b.closeBox();
}
b.closeBox();
