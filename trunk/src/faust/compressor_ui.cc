// ----- the compressor
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("ratio"), N_("ratio"));
b.closeBox();
b.openHorizontalTableBox("");
{
    b.create_small_rackknob(PARAM("knee"), N_("knee"));
    b.create_small_rackknobr(PARAM("ratio"), N_("ratio"));
    b.create_small_rackknob(PARAM("threshold"), N_("threshold"));

    b.create_small_rackknob(PARAM("attack"), N_("attack"));
    b.create_small_rackknob(PARAM("release"), N_("release"));
}
b.closeBox();
