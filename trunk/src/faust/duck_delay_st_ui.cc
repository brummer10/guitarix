// ducking delay stereo

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("effect"), _("effect"));
b.closeBox();


b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("time"),         _(" time ms "));
	b.create_small_rackknob(PARAM("feedback"),     _(" feedback "));
	b.create_small_rackknob(PARAM("pingpong"),     _(" ping-pong"));
	b.create_small_rackknob(PARAM("coloration"),   _("coloration"));	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("attack"),        _(" attack "));
	b.create_small_rackknob(PARAM("release"),       _(" release "));
	b.create_small_rackknob(PARAM("amount"),        _(" amount "));
	b.create_small_rackknobr(PARAM("effect"),       _(" effect "));
}
b.closeBox();
b.closeBox();
b.closeBox();
