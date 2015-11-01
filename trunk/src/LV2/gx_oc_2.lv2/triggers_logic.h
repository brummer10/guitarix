static const float cmos_threshold = 2.5;
static const float cmos_min = -4.0;
static const float cmos_max = 4.0; 

float FF_JK_4027(int clock)
{	
	static bool state;
	static float buf;
	
	if((buf < 0) && (clock >= cmos_threshold))
		state =! state;

	buf = clock;

	if(state)
	{
		return cmos_max;
	}
	else
	{
		return cmos_min;
	}
}

float FF_D_4013_1(int clock)
{
	static bool state;
	static float buf;
	
	if((buf < 0) && (clock >= cmos_threshold))
		state =! state;

	buf = clock;

	if(state)
	{
		return cmos_max;
	}
	else
	{
		return cmos_min;
	}
}

float FF_D_4013_2(int direct_set, int direct_clear)
{
	static bool state;

	if((direct_set < cmos_threshold) && (direct_clear < cmos_threshold))
	{
		if(state)
		{
			return cmos_max;
		}
		else
		{
			return cmos_min;
		}
	}

	if((direct_set < cmos_threshold) && (direct_clear > cmos_threshold))
	{
		state = false;
		return cmos_min;
	}

	if((direct_set > cmos_threshold) && (direct_clear < cmos_threshold))
	{
		state = true;
		return cmos_max;
	}

	if((direct_set > cmos_threshold) && (direct_clear > cmos_threshold))
	{
		if(state)
		{
			return cmos_max;
		}
		else
		{
			return cmos_min;
		}
	}

	return 0;
}
