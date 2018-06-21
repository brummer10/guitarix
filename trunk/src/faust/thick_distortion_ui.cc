// ----- thick_distortion
b.openHorizontalhideBox("");
b.create_master_slider("thick_distortion.volume", _(" Volume "));
b.closeBox();
b.openHorizontalBox("");
{
	b.openVerticalBox("");
	{
		b.openFlipLabelBox("");
		{
			b.openHorizontalBox("");
			{
				b.create_small_rackknobr(
					"thick_distortion.input_gain", _(" Input Gain "));
				b.create_small_rackknobr(
					"thick_distortion.thickness", _(" Thickness "));
				b.create_small_rackknobr(
					"thick_distortion.volume", _(" Volume "));
			}
			b.closeBox();
		}
		b.closeBox();
	}
	b.closeBox();
}
b.closeBox();
