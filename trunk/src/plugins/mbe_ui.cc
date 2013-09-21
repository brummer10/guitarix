
b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openpaintampBox(" ");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time1"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent1"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox(" ");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time2"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent2"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox(" ");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time3"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent3"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox(" ");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time4"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent4"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low (Hz)"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High (hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox(" ");
b.openHorizontalBox("");
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("time5"), N_("BPM"));
b.set_next_flags(UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("percent5"), N_("Amount"));
b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_RIGHT);
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High Shelf (Hz)"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
b.closeBox();
