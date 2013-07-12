// EQ
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_simple_spin_value("eqs.freq31_25");
	b.create_simple_spin_value("eqs.freq62_5");
	b.create_simple_spin_value("eqs.freq125");
	b.create_simple_spin_value("eqs.freq250");
	b.create_simple_spin_value("eqs.freq500");
	b.create_simple_spin_value("eqs.freq1k");
	b.create_simple_spin_value("eqs.freq2k");
	b.create_simple_spin_value("eqs.freq4k");
	b.create_simple_spin_value("eqs.freq8k");
	b.create_simple_spin_value("eqs.freq16k");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_eq_rackslider_no_caption("eqs.fs31_25");
	b.create_eq_rackslider_no_caption("eqs.fs62_5");
	b.create_eq_rackslider_no_caption("eqs.fs125");
	b.create_eq_rackslider_no_caption("eqs.fs250");
	b.create_eq_rackslider_no_caption("eqs.fs500");
	b.create_eq_rackslider_no_caption("eqs.fs1k");
	b.create_eq_rackslider_no_caption("eqs.fs2k");
	b.create_eq_rackslider_no_caption("eqs.fs4k");
	b.create_eq_rackslider_no_caption("eqs.fs8k");
	b.create_eq_rackslider_no_caption("eqs.fs16k");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob("eqs.Qs31_25", "Q");
	b.create_small_rackknob("eqs.Qs62_5", "Q");
	b.create_small_rackknob("eqs.Qs125", "Q");
	b.create_small_rackknob("eqs.Qs250", "Q");
	b.create_small_rackknob("eqs.Qs500", "Q");
	b.create_small_rackknob("eqs.Qs1k", "Q");
	b.create_small_rackknob("eqs.Qs2k", "Q");
	b.create_small_rackknob("eqs.Qs4k", "Q");
	b.create_small_rackknob("eqs.Qs8k", "Q");
	b.create_small_rackknob("eqs.Qs16k", "Q");
    }
    b.closeBox();
}
b.closeBox();
