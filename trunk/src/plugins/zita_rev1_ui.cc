int load_ui(const UiBuilder& b) {
    b.openVerticalBox("");
    {
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.input.in_delay");
	    b.create_small_rackknob("zita_rev1.decay_times.lf_x");
	    b.create_small_rackknob("zita_rev1.decay_times.low_rt60");
	    b.create_small_rackknob("zita_rev1.decay_times.mid_rt60");
	    b.create_small_rackknob("zita_rev1.decay_times.hf_damping");
	}
	b.closeBox();
	b.openHorizontalBox("");
	{
	    b.create_small_rackknob("zita_rev1.equalizer1.eq1_freq");
	    b.create_small_rackknob("zita_rev1.equalizer1.eq1_level");
	    b.create_small_rackknob("zita_rev1.equalizer2.eq2_freq");
	    b.create_small_rackknob("zita_rev1.equalizer2.eq2_level");
	    b.create_small_rackknob("zita_rev1.output.dry_wet_mix");
	    b.create_small_rackknob("zita_rev1.output.level");
	}
	b.closeBox();
    }
    b.closeBox();
    return 0;
}
