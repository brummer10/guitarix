// ----- the expander
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("ratio"), _("ratio"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.create_small_rackknob(PARAM("knee"), _("knee"));
    b.create_small_rackknobr(PARAM("ratio"), _("ratio"));
    b.create_small_rackknob(PARAM("threshold"), _("threshold"));

    b.create_small_rackknob(PARAM("attack"), _("attack"));
    b.create_small_rackknob(PARAM("release"), _("release"));
}
b.closeBox();
