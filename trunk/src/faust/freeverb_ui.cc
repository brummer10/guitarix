// ----- freeverb
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("RoomSize"), _("RoomSize"));
b.closeBox();
b.openHorizontalBox("");
{
    b.openFrameBox("");
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("RoomSize"), _("RoomSize"));
	b.create_small_rackknob(PARAM("damp"), _("damp"));
	b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
    }
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
    b.openFrameBox("");
    b.closeBox();
}
b.closeBox();
