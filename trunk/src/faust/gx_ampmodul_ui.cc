// postamp
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("level"), _("level"));
b.closeBox();
b.openHorizontalBox("");
{
    b.insertSpacer();
    b.create_small_rackknobr(PARAM("feedbac"), _("dry/feedback  "));
    b.create_small_rackknob(PARAM("wet_dry"), _("dry/wet"));
    b.create_small_rackknob(PARAM("level"), _("level"));
    b.create_small_rackknob(PARAM("amp2.stage1.tube1"), _("tube1"));
    b.create_small_rackknob(PARAM("amp2.stage2.tube2"), _("tube2"));
    b.create_small_rackknobr(PARAM("feedback"), _("  wet/feedback"));
    b.insertSpacer();
}
b.closeBox();
