// 3 band eq
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.create_small_rackknob(PARAM("Bass"), _("bass"));
    b.create_small_rackknob(PARAM("Middle"), _("middle"));
    b.create_small_rackknob(PARAM("Treble"), _("treble"));
    b.insertSpacer();
    b.create_switch_no_caption(sw_switchit, PARAM("ON"));
    b.create_small_rackknob(PARAM("sharper"), _("sharp"));
}
b.closeBox();
