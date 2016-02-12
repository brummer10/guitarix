// ----- chorus
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknobr(PARAM("level"), _("  level  "));
    b.create_small_rackknob(PARAM("delay"), _("  delay  "));
    b.create_small_rackknob(PARAM("depth"), _("  depth  "));
    b.create_small_rackknob(PARAM("freq"), _("  freq  "));
}
b.closeBox();
