// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("bpm"), _(" delay (bpm)"));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalBox("");
    {
        b.openVerticalBox("");
        {
            b.create_selector(PARAM("notes"), "tact");
            b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
            b.create_small_rackknob(PARAM("bpm"), _(" delay (bpm)"));
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.openHorizontalBox("");
            b.openFrameBox("");
            b.closeBox();
            b.create_selector(PARAM("mode"), "mode");
            b.closeBox();
            b.openHorizontalBox("");
            {
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("highpass"), _("highpass(hz)"));
                b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
                b.create_small_rackknob(PARAM("howpass"), _("lowpass(hz)"));
            }
            b.closeBox();
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknob(PARAM("level"), _("level"));
            b.create_small_rackknob(PARAM("feedback"), _("feedback"));
        }
        b.closeBox();
        b.openVerticalBox("");
        {
            b.create_small_rackknobr(PARAM("gain"), _("amount"));
            b.openFrameBox("");
            b.closeBox();
            b.create_switch(sw_rbutton,PARAM("Freeze"), _("freeze"));
        }
        b.closeBox();
    }
    b.closeBox();
}
b.closeBox();
