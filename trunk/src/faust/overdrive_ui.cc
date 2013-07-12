// -----overdrive
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), _("Drive"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.insertSpacer();
    b.create_small_rackknobr(PARAM("drive"), _("  Drive "));
    b.create_small_rackknob(PARAM("wet_dry"), _("Dry/Wet"));
    b.insertSpacer();
}
b.closeBox();
