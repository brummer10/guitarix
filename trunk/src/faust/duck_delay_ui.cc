// ----- ducking delay
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
		b.create_small_rackknob(PARAM("time"),     _("   time ms  "));
		b.create_small_rackknob(PARAM("feedback"), _("   feedback "));
		b.create_small_rackknob(PARAM("attack"),   _("   attack s "));
		b.create_small_rackknob(PARAM("relese"),   _("  release s "));
		b.create_small_rackknob(PARAM("amount"),   _("  amount dB "));
    }
    b.closeBox();
}
b.closeBox();

