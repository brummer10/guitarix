
b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive1"), N_("Drive"));
b.create_small_rackknob(PARAM("Gain1"), N_("Gain"));
b.insertSpacer();
b.insertSpacer();
b.insertSpacer();
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive2"), N_("Drive"));
b.create_small_rackknob(PARAM("Gain2"), N_("Gain"));
b.create_small_rackknob(PARAM("crossover_b1_b2"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive3"), N_("Drive"));
b.create_small_rackknob(PARAM("Gain3"), N_("Gain"));
b.create_small_rackknob(PARAM("crossover_b2_b3"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive4"), N_("Drive"));
b.create_small_rackknob(PARAM("Gain4"), N_("Gain"));
b.create_small_rackknob(PARAM("crossover_b3_b4"), N_("Low"));
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("High"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openpaintampBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Drive5"), N_("Drive"));
b.create_small_rackknob(PARAM("Gain5"), N_("Gain"));
b.create_small_rackknob(PARAM("crossover_b4_b5"), N_("Low"));
b.closeBox();
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();

b.create_mid_rackknob(PARAM("Gain"), N_("Gain"));

b.openVerticalBox2("Analyze");
b.create_simple_meter(PARAM("v1"));
b.create_simple_meter(PARAM("v2"));
b.create_simple_meter(PARAM("v3"));
b.create_simple_meter(PARAM("v4"));
b.create_simple_meter(PARAM("v5"));
b.closeBox();

b.closeBox();
