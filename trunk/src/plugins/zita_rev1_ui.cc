b.openHorizontalhideBox("");
{
    b.create_master_slider(PARAM("output.level"), "Level");
}
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("Reverb Time T60");
    {
    b.create_small_rackknob(PARAM("input.in_delay"), "In Delay");

	b.create_small_rackknob(PARAM("decay_times.low_rt60"), "Low");
	b.create_small_rackknob(PARAM("decay_times.lf_x"), "Freq X");
	b.create_small_rackknob(PARAM("decay_times.mid_rt60"), "Mid");
	b.create_small_rackknob(PARAM("decay_times.hf_damping"), "HF Damping");

	b.create_small_rackknob(PARAM("output.dry_wet_mix"), "Dry/Wet");
	}
    b.closeBox();

    b.openHorizontalBox("Eq");
    {
	b.create_small_rackknob(PARAM("equalizer1.eq1_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer1.eq1_level"), "Level");

	b.create_small_rackknob(PARAM("equalizer2.eq2_freq"), "Freq");
	b.create_small_rackknob(PARAM("equalizer2.eq2_level"), "Level");

	b.create_small_rackknob(PARAM("output.level"), "Level");
	}
    b.closeBox();
}
b.closeBox();
