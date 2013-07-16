b.openHorizontalhideBox("");
{
    b.create_master_slider(PARAM("output.level"), 0);
}
b.closeBox();
b.openVerticalBox("");
{
    b.create_small_rackknob(PARAM("input.in_delay"), 0);
    b.create_small_rackknob(PARAM("output.dry_wet_mix"), 0);
    b.create_small_rackknob(PARAM("output.level"), 0);

    b.openHorizontalBox("Reverb Time T60");
    {
	b.create_small_rackknob(PARAM("decay_times.lf_x"), 0);
	b.create_small_rackknob(PARAM("decay_times.low_rt60"), 0);
	b.create_small_rackknob(PARAM("decay_times.mid_rt60"), 0);
	b.create_small_rackknob(PARAM("decay_times.hf_damping"), 0);
    }
    b.closeBox();

    b.openHorizontalBox("Eq1");
    {
	b.create_small_rackknob(PARAM("equalizer1.eq1_freq"), 0);
	b.create_small_rackknob(PARAM("equalizer1.eq1_level"), 0);
    }
    b.closeBox();

    b.openHorizontalBox("Eq2");
    {
	b.create_small_rackknob(PARAM("equalizer2.eq2_freq"), 0);
	b.create_small_rackknob(PARAM("equalizer2.eq2_level"), 0);
    }
    b.closeBox();
}
b.closeBox();
