// dattorros progenitor (Plate reverb)

b.openHorizontalhideBox("");
b.create_master_slider(PARAM("dry/wet"), _("dry/wet"));
b.closeBox();

b.openHorizontalBox("");
b.openVerticalBox("");
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("predelay ms"),  _("predelay ms"));
	b.create_small_rackknob(PARAM("bandwidth"),    _(" bandwidth "));
	b.create_small_rackknob(PARAM("input diff 1"), _(" in diff 1 "));
	b.create_small_rackknob(PARAM("input diff 2"), _(" in diff 2 "));
	b.create_small_rackknob(PARAM("excursion"),    _(" excursion "));

	
}
b.closeBox();
b.openHorizontalBox("");
{
	b.create_small_rackknob(PARAM("decay"),        _("  decay   "));
	b.create_small_rackknob(PARAM("decay diff 1"), _("dec diff 1"));
	b.create_small_rackknob(PARAM("decay diff 2"), _("dec diff 2"));
	b.create_small_rackknob(PARAM("damping"),      _("HF damping"));
	b.create_small_rackknobr(PARAM("dry/wet"),     _("  dry/wet "));
}
b.closeBox();
b.closeBox();
b.closeBox();
