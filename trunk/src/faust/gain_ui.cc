// ----- gain
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("gain"), _("gain"));
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("gain"), _("gain"));
}
b.closeBox();
