int load_ui(const UiBuilder& b) {
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.g1.in_delay");
	    b.create_small_rackknob("zita_rev1.g2.lf_x");
	    b.create_small_rackknob("zita_rev1.g2.low_rt60");
	    b.create_small_rackknob("zita_rev1.g2.mid_rt60");
	    b.create_small_rackknob("zita_rev1.g2.hf_damping");
	}
	b.closeBox();
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.g3.eq1_freq");
	    b.create_small_rackknob("zita_rev1.g3.eq1_level");
	    b.create_small_rackknob("zita_rev1.g4.eq2_freq");
	    b.create_small_rackknob("zita_rev1.g4.eq2_level");
	    b.create_small_rackknob("zita_rev1.g5.dry_wet_mix");
	    b.create_small_rackknob("zita_rev1.g5.level");
	}
	b.closeBox();
    }
    b.closeBox();
    return 0;
}
