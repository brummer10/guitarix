// ----- bitdowner
b.openHorizontalhideBox("");
b.create_master_slider("bitdowner.volume", _(" Volume "));
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
					"bitdowner.input_gain", _(" Input Gain "));
				b.create_small_rackknobr(
					"bitdowner.bit_down", _(" BitDown "));
				b.create_small_rackknobr(
					"bitdowner.downsampling", _(" Downsampling "));
				b.create_small_rackknobr(
					"bitdowner.volume", _(" Volume "));
			}
			b.closeBox();
		}
		b.closeBox();
	}
	b.closeBox();
}
b.closeBox();
