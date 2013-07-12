// low high pass filter
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openHorizontalBox("");
    {
	b.create_small_rackknob("low_high_pass.lhp.high_freq", _("high-pass "));
	b.create_small_rackknob("low_high_pass.lhp.low_freq", _(" low-pass "));
	b.create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
    }
    b.closeBox();
    b.insertSpacer();
    b.openHorizontalBox("");
    {
	b.create_small_rackknob("low_high_pass.lhc.low_freq", _("low-cut "));
	b.create_small_rackknob("low_high_pass.lhc.high_freq", _("high-cut "));
	b.create_switch_no_caption(sw_switchit, "low_high_pass.lhc.on_off");
    }
    b.closeBox();
}
b.closeBox();
