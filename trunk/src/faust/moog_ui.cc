// moog filter
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("Q"), _("Q"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.create_small_rackknob(PARAM("Q"), _("            Q            "));
    b.create_small_rackknob(PARAM("fr"), _("            Hz           "));
}
b.closeBox();
