// ----- the expander
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("ratio"), N_("ratio"));
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("knee"), N_("knee"));
    b.create_small_rackknobr(PARAM("ratio"), N_("ratio"));
    b.create_small_rackknob(PARAM("threshold"), N_("threshold"));

    b.create_small_rackknob(PARAM("attack"), N_("attack"));
    b.create_small_rackknob(PARAM("release"), N_("release"));
    b.create_simple_meter(PARAM("v1"));
}
b.closeBox();
