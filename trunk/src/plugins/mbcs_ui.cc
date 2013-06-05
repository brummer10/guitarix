
b.openHorizontalhideBox("");
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");

b.openTabBox("");

b.openHorizontalBox(N_("Band 1"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Makeup1 (db)"), N_("Makeup (db)"));
b.create_small_rackknob(PARAM("Makeup-Threshold1 (db)"), N_("Anticlip (db)"));
b.create_small_rackknob(PARAM("show_always.Crossover B1-B2 (hz)"), N_("Low Shelf (Hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode1"));
b.create_small_rackknob(PARAM("Ratio1"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack1 (sec)"), N_("Attack"));
b.create_small_rackknob(PARAM("Release1 (sec)") ,N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 2"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Makeup2 (db)"), N_("Makeup (db)"));
b.create_small_rackknob(PARAM("Makeup-Threshold2 (db)"), N_("Anticlip (db)"));
b.create_small_rackknob(PARAM("show_always.Crossover B1-B2 (hz)"), N_("Low (hz)"));
b.create_small_rackknob(PARAM("show_always.Crossover B2-B3 (hz)"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode2"));
b.create_small_rackknob(PARAM("Ratio2"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack2 (sec)"), N_("Attack"));
b.create_small_rackknob(PARAM("Release2 (sec)"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 3"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Makeup3 (db)"), N_("Makeup (db)"));
b.create_small_rackknob(PARAM("Makeup-Threshold3 (db)"), N_("Anticlip (db)"));
b.create_small_rackknob(PARAM("show_always.Crossover B2-B3 (hz)"), N_("Low (hz)"));
b.create_small_rackknob(PARAM("show_always.Crossover B3-B4 (hz)"), N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode3"));
b.create_small_rackknob(PARAM("Ratio3"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack3 (sec)"), N_("Attack"));
b.create_small_rackknob(PARAM("Release3 (sec)"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 4"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Makeup4 (db)"), N_("Makeup (db)"));
b.create_small_rackknob(PARAM("Makeup-Threshold4 (db)"), N_("Anticlip (db)"));
b.create_small_rackknob(PARAM("show_always.Crossover B3-B4 (hz)"),N_("Low (hz)"));
b.create_small_rackknob(PARAM("show_always.Crossover B4-B5 (hz)"),N_("High (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode4"));
b.create_small_rackknob(PARAM("Ratio4"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack4 (sec)"), N_("Attack"));
b.create_small_rackknob(PARAM("Release4 (sec)"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Band 5"));
b.openVerticalBox("");
b.openHorizontalBox("");
b.create_small_rackknob(PARAM("Makeup5 (db)"), N_("Makeup (db)"));
b.create_small_rackknob(PARAM("Makeup-Threshold5 (db)"), N_( "Anticlip (db)"));
b.create_small_rackknob(PARAM("show_always.Crossover B4-B5 (hz)"), N_("High Shelf (hz)"));
b.closeBox();
b.openHorizontalBox("");
b.create_selector_no_caption(PARAM("Mode5"));
b.create_small_rackknob(PARAM("Ratio5"), N_("Ratio"));
b.create_small_rackknob(PARAM("Attack5 (sec)"), N_("Attack"));
b.create_small_rackknob(PARAM("Release5 (sec)"), N_("Release"));
b.closeBox();
b.closeBox();
b.closeBox();

b.closeBox();
b.closeBox();
b.closeBox();
