/*
 * Copyright (C) 2013 Hermann Meyer, Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is part of the Guitarix Audio Engine
 *
 *
 *
 * --------------------------------------------------------------------------
 */


/****************************************************************
 ** class LiveLooper
 */
namespace livelooper {


class LiveLooper: public PluginLV2 {
private:
	int fSamplingFreq;
	float 	fgain;
	float 	*fgain_;
	float 	fRec0[2];
	float 	gain_out;
	float 	fclip1;
	float 	fclip2;
	float 	fclip3;
	float 	fclip4;
	float 	fclips1;
	float 	fclips2;
	float 	fclips3;
	float 	fclips4;
	float 	fspeed1;
	float 	fspeed2;
	float 	fspeed3;
	float 	fspeed4;
	float 	rfplay1;
	float 	rfplay2;
	float 	rfplay3;
	float 	rfplay4;
	float 	record1;
	float 	*gain_out_;
	float 	*fclip1_;
	float 	*fclip2_;
	float 	*fclip3_;
	float 	*fclip4_;
	float 	*fclips1_;
	float 	*fclips2_;
	float 	*fclips3_;
	float 	*fclips4_;
	float 	*fspeed1_;
	float 	*fspeed2_;
	float 	*fspeed3_;
	float 	*fspeed4_;
	float 	*rfplay1_;
	float 	*rfplay2_;
	float 	*rfplay3_;
	float 	*rfplay4_;
	float 	*record1_;
	int 	iVec0[2];
	int 	IOTA1;
	int 	IOTA2;
	int 	IOTA3;
	int 	IOTA4;
	float 	IOTAR1;
	float 	IOTAR2;
	float 	IOTAR3;
	float 	IOTAR4;
	float *tape1;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	freset1;
	float 	*freset1_;
	int 	RecSize1[2];
	float 	rectime0;
	float 	*rectime0_;
	float 	fRec1[2];
	float 	fRec2[2];
	int 	iRec3[2];
	int 	iRec4[2];
	float 	fplay1;
	float 	fplayh1;
	float 	gain1;
	float 	record2;
	float 	*fplay1_;
	float 	*fplayh1_;
	float 	*gain1_;
	float 	*record2_;
	int 	iVec2[2];
	float *tape2;
	float 	freset2;
	float 	*freset2_;
	int 	RecSize2[2];
	float 	rectime1;
	float 	*rectime1_;
	float 	fRec6[2];
	float 	fRec7[2];
	int 	iRec8[2];
	int 	iRec9[2];
	float 	fplay2;
	float 	fplayh2;
	float 	gain2;
	float 	record3;
	float 	*fplay2_;
	float 	*fplayh2_;
	float 	*gain2_;
	float 	*record3_;
	int 	iVec4[2];
	float *tape3;
	float 	freset3;
	float 	*freset3_;
	int 	RecSize3[2];
	float 	rectime2;
	float 	*rectime2_;
	float 	fRec11[2];
	float 	fRec12[2];
	int 	iRec13[2];
	int 	iRec14[2];
	float 	fplay3;
	float 	fplayh3;
	float 	gain3;
	float 	record4;
	float 	*fplay3_;
	float 	*fplayh3_;
	float 	*gain3_;
	float 	*record4_;
	int 	iVec6[2];
	float *tape4;
	float 	freset4;
	float 	*freset4_;
	int 	RecSize4[2];
	float 	rectime3;
	float 	*rectime3_;
	float 	fRec16[2];
	float 	fRec17[2];
	int 	iRec18[2];
	int 	iRec19[2];
	float 	fplay4;
	float 	fplayh4;
	float 	gain4;
	float 	*fplay4_;
	float 	*fplayh4_;
	float 	*gain4_;
	bool save1;
	bool save2;
	bool save3;
	bool save4;
	bool RP1;
	bool RP2;
	bool RP3;
	bool RP4;
    Glib::ustring pfreset_name;
    Glib::ustring cur_name;
    Glib::ustring loop_dir;
    bool save_p;
	bool mem_allocated;
	volatile bool ready;
    void mem_alloc();
	void mem_free();
	void clear_state_f();
	void connect(uint32_t port,void* data);
	int activate(bool start);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
    void save_array(std::string name);
    void load_array(std::string name);
    void save_to_wave(std::string fname, float *tape, float fSize);
    int load_from_wave(std::string fname, float *tape);
    void set_p_state();
    
	static void clear_state_f_static(PluginLV2*);
	static int activate_static(bool start, PluginLV2*);
	static void init_static(unsigned int samplingFreq, PluginLV2*);
	static void compute_static(int count, float *input0, float *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	LiveLooper();
	~LiveLooper();
};



LiveLooper::LiveLooper()
	: PluginLV2(),
	  tape1(0),
	  tape2(0),
	  tape3(0),
	  tape4(0),
	  save1(false),
	  save2(false),
	  save3(false),
	  save4(false),
	  RP1(false),
	  RP2(false),
	  RP3(false),
	  RP4(false),
      pfreset_name("tape"),
      cur_name("tape"),
      loop_dir("/gxloops/"),
      save_p(false),
	  mem_allocated(false),
      ready(false) {
	id = "dubber";
	name = N_("Dubber");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
    connect_ports = connect_static;
	delete_instance = del_instance;
}

LiveLooper::~LiveLooper() {
    activate(false);
}

inline void LiveLooper::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<4194304; i++) tape1[i] = 0;
	for (int i=0; i<2; i++) RecSize1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) iVec2[i] = 0;
	for (int i=0; i<4194304; i++) tape2[i] = 0;
	for (int i=0; i<2; i++) RecSize2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) iVec4[i] = 0;
	for (int i=0; i<4194304; i++) tape3[i] = 0;
	for (int i=0; i<2; i++) RecSize3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) iRec14[i] = 0;
	for (int i=0; i<2; i++) iVec6[i] = 0;
	for (int i=0; i<4194304; i++) tape4[i] = 0;
	for (int i=0; i<2; i++) RecSize4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) iRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
}

void LiveLooper::clear_state_f_static(PluginLV2 *p)
{
	static_cast<LiveLooper*>(p)->clear_state_f();
}

inline void LiveLooper::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA1 = 0;
	IOTA2 = 0;
	IOTA3 = 0;
	IOTA4 = 0;
	IOTAR1 = 0;
	IOTAR2 = 0;
	IOTAR3 = 0;
	IOTAR4 = 0;
	fConst0 = (1e+01f / float(fmin(192000, fmax(1, fSamplingFreq))));
	fConst1 = (0 - fConst0);
    fConst2 = (1.0 / float(fmin(192000, fmax(1, fSamplingFreq))));
}

void LiveLooper::init_static(unsigned int samplingFreq, PluginLV2 *p)
{
	static_cast<LiveLooper*>(p)->init(samplingFreq);
}

void LiveLooper::mem_alloc()
{
    try {
        if (!tape1) tape1 = new float[4194304];
        if (!tape2) tape2 = new float[4194304];
        if (!tape3) tape3 = new float[4194304];
        if (!tape4) tape4 = new float[4194304];
        } catch(...) {
            fprintf(stderr, "livelooper out of memory");
            return;
        }
    mem_allocated = true;
    ready = true;
}

void LiveLooper::mem_free()
{
    ready = false;
	mem_allocated = false;
	if (tape1) { delete tape1; tape1 = 0; }
	if (tape2) { delete tape2; tape2 = 0; }
	if (tape3) { delete tape3; tape3 = 0; }
	if (tape4) { delete tape4; tape4 = 0; }
}

inline int LiveLooper::load_from_wave(std::string fname, float *tape)
{
    SF_INFO sfinfo;
    int n,f,c;
    int fSize = 0;
    sfinfo.format = 0;
    SNDFILE *sf = sf_open(fname.c_str(),SFM_READ,&sfinfo);
    if (sf ) {
        f = sfinfo.frames;
        c = sfinfo.channels;
        n = f*c;
        fSize = sf_read_float(sf,tape,n);
    }
    sf_close(sf);
    return fSize;
}

inline void LiveLooper::load_array(std::string name)
{
    std::string pPath = getenv("HOME");
    pPath += loop_dir;
    RecSize1[1] = load_from_wave(pPath+name+"1.wav", tape1);
    IOTAR1= RecSize1[1] - int(RecSize1[1]*(100-fclips1)*0.01);
    
    RecSize2[1] = load_from_wave(pPath+name+"2.wav", tape2);
    IOTAR2= RecSize2[1] - int(RecSize2[1]*(100-fclips2)*0.01);
    
    RecSize3[1] = load_from_wave(pPath+name+"3.wav", tape3);
    IOTAR3= RecSize3[1] - int(RecSize3[1]*(100-fclips3)*0.01);
    
    RecSize4[1] = load_from_wave(pPath+name+"4.wav", tape4);
    IOTAR4= RecSize4[1] - int(RecSize4[1]*(100-fclips4)*0.01);
    
    cur_name = pfreset_name;
}

inline void LiveLooper::save_to_wave(std::string fname, float *tape, float fSize)
{
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = fSamplingFreq;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    
    SNDFILE * sf = sf_open(fname.c_str(), SFM_WRITE, &sfinfo);
    if (sf) {
        size_t lSize = 4194304 - int(fSize/fConst2);
        sf_write_float(sf,tape, lSize);
        sf_write_sync(sf);
    }
    sf_close(sf);
}

inline void LiveLooper::save_array(std::string name)
{
    struct stat sb;
    std::string pPath = getenv("HOME");
    pPath += loop_dir;
    if (!(stat(pPath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        mkdir(pPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    if (name.compare("tape")==0 || save_p) {
        if (save1) {
            save_to_wave(pPath+name+"1.wav",tape1,rectime0);
            save1 = false;
        }
        if (save2) {
            save_to_wave(pPath+name+"2.wav",tape2,rectime1);
            save2 = false;
        }
        if (save3) {
            save_to_wave(pPath+name+"3.wav",tape3,rectime2);
            save3 = false;
        }
        if (save4) {
            save_to_wave(pPath+name+"4.wav",tape4,rectime3);
            save4 = false;
        }
    }
}

int LiveLooper::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
            load_array(pfreset_name);
		}
	} else if (mem_allocated) {
        save_array(cur_name);
		mem_free();
	}
	return 0;
}

int LiveLooper::activate_static(bool start, PluginLV2 *p)
{
	return static_cast<LiveLooper*>(p)->activate(start);
}

void LiveLooper::set_p_state() {
    if (!pfreset_name.empty()) {
        ready = false;
        activate(true);
        if(save_p) {
            save1 = true;
            save2 = true;
            save3 = true;
            save4 = true;
            cur_name = pfreset_name;
        }
        activate(false);
        activate(true);
        ready = true;
        save_p = false;
    }
}

void always_inline LiveLooper::compute(int count, float *input0, float *output0)
{
    if (!ready) {
        memcpy(output0, input0, count * sizeof(float));
        return;
    }
#define fclip1 (*fclip1_)
#define fclip2 (*fclip2_)
#define fclip3 (*fclip3_)
#define fclip4 (*fclip4_)
#define fclips1 (*fclips1_)
#define fclips2 (*fclips2_)
#define fclips3 (*fclips3_)
#define fclips4 (*fclips4_)
#define fspeed1 (*fspeed1_)
#define fspeed2 (*fspeed2_)
#define fspeed3 (*fspeed3_)
#define fspeed4 (*fspeed4_)
*rectime0_ = (rectime0);
*rectime1_ = (rectime1);
*rectime2_ = (rectime2);
*rectime3_ = (rectime3);
#define fgain (*fgain_)
#define gain1 (*gain1_)
#define gain2 (*gain2_)
#define gain3 (*gain3_)
#define gain4 (*gain4_)
#define gain_out (*gain_out_)
#define fplay1 (*fplay1_)
#define fplay2 (*fplay2_)
#define fplay3 (*fplay3_)
#define fplay4 (*fplay4_)
#define rfplay1 (*rfplay1_)
#define rfplay2 (*rfplay2_)
#define rfplay3 (*rfplay3_)
#define rfplay4 (*rfplay4_)
#define fplayh1 (*fplayh1_)
#define fplayh2 (*fplayh2_)
#define fplayh3 (*fplayh3_)
#define fplayh4 (*fplayh4_)
#define record1 (*record1_)
#define record2 (*record2_)
#define record3 (*record3_)
#define record4 (*record4_)
#define freset1 (*freset1_)
#define freset2 (*freset2_)
#define freset3 (*freset3_)
#define freset4 (*freset4_)
    // trigger save array on exit
	if(record1 || freset1) save1 = true;
    if(record2 || freset2) save2 = true;
    if(record3 || freset3) save3 = true;
    if(record4 || freset4) save4 = true;
    // make fplay/ reverse fplay button act as radio button
    if (rfplay1 && !RP1) {fplay1 = 0.0;RP1=true;}
    else if (fplay1 && RP1) {rfplay1 = 0.0;RP1=false;}
    if (rfplay2 && !RP2) {fplay2 = 0.0;RP2=true;}
    else if (fplay2 && RP2) {rfplay2 = 0.0;RP2=false;}
    if (rfplay3 && !RP3) {fplay3 = 0.0;RP3=true;}
    else if (fplay3 && RP3) {rfplay3 = 0.0;RP3=false;}
    if (rfplay4 && !RP4) {fplay4 = 0.0;RP4=true;}
    else if (fplay4 && RP4) {rfplay4 = 0.0;RP4=false;}
    // switch off record when buffer is full
    record1     = rectime0? record1 : 0.0;
	record2     = rectime1? record2 : 0.0;
	record3     = rectime2? record3 : 0.0;
	record4     = rectime3? record4 : 0.0;
    // freset clip when freset is pressed
    if (freset1) {fclip1=100.0;fclips1=0.0;}
    if (freset2) {fclip2=100.0;fclips2=0.0;}
    if (freset3) {fclip3=100.0;fclips3=0.0;}
    if (freset4) {fclip4=100.0;fclips4=0.0;}
    // switch off freset button when buffer is empty 
    freset1     = (rectime0 < 4194304*fConst2)? freset1 : 0.0;
	freset2     = (rectime1 < 4194304*fConst2)? freset2 : 0.0;
	freset3     = (rectime2 < 4194304*fConst2)? freset3 : 0.0;
	freset4     = (rectime3 < 4194304*fConst2)? freset4 : 0.0;
    // set fplay head position
    
    float ph1      = RecSize1[0] ? 1.0/(RecSize1[0] * 0.001) : 0.0;
    fplayh1 = (1-iVec0[0]) * fmin(1000,fmax(0,float(IOTAR1*ph1)));
    float ph2      = RecSize2[0] ? 1.0/(RecSize2[0] * 0.001) : 0.0;
    fplayh2 = (1-iVec2[0]) *  fmin(1000,fmax(0,float(IOTAR2*ph2)));
    float ph3      = RecSize3[0] ? 1.0/(RecSize3[0] * 0.001) : 0.0;
    fplayh3 = (1-iVec4[0]) *  fmin(1000,fmax(0,float(IOTAR3*ph3)));
    float ph4      = RecSize4[0] ? 1.0/(RecSize4[0] * 0.001) : 0.0;
    fplayh4 = (1-iVec6[0]) *  fmin(1000,fmax(0,float(IOTAR4*ph4)));
    // fplayback speed
    float speed1 = fspeed1;
    float speed2 = fspeed2;
    float speed3 = fspeed3;
    float speed4 = fspeed4;
    // engine var settings
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fgain)));
	float 	fSlow1 = gain_out;
    int 	iSlow3 = int(record1);
	int 	iSlow4 = int((1 - freset1));
	float 	fSlow5 = (((1 - iSlow3) * gain1) * (fplay1+rfplay1));
	int 	iSlow6 = int(record2);
	int 	iSlow7 = int((1 - freset2));
	float 	fSlow8 = (((1 - iSlow6) * gain2) * (fplay2+rfplay2));
	int 	iSlow9 = int(record3);
	int 	iSlow10 = int((1 - freset3));
	float 	fSlow11 = (((1 - iSlow9) * gain3) * (fplay3+rfplay3));
	int 	iSlow12 = int(record4);
	int 	iSlow13 = int((1 - freset4));
	float 	fSlow14 = (((1 - iSlow12) * gain4) * (fplay4+rfplay4));
	float 	fSlow15 = (0.0001f * fSlow1);
    float   iClip1  = fclip1*0.01;
	float   iClip2  = fclip2*0.01;
	float   iClip3  = fclip3*0.01;
	float   iClip4  = fclip4*0.01;
	float   iClips1  = (100-fclips1)*0.01;
	float   iClips2  = (100-fclips2)*0.01;
	float   iClips3  = (100-fclips3)*0.01;
	float   iClips4  = (100-fclips4)*0.01;
    // run loop
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float fTemp0 = ((float)input0[i] * fRec0[0]);
		iVec0[0] = iSlow3;
		float fTemp1 = (iSlow3 * fTemp0);
        RecSize1[0] = fmin(4194304, (int)(iSlow4 * (((iSlow3 - iVec0[1]) <= 0) * (iSlow3 + RecSize1[1]))));
		int iTemp2 = (4194304 - RecSize1[0]);
		rectime0 = iTemp2*fConst2;
        int iTemp3 = fmin(4194304-1, (int)(4194304 - iTemp2));
		if (iSlow3 == 1) {
        IOTA1 = IOTA1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):IOTA1+1;
		tape1[IOTA1] = fTemp1;
        }
        if (rfplay1) {
        IOTAR1 = IOTAR1-speed1< (iTemp3 - int(iTemp3*iClips1))? int(iTemp3*iClip1):(IOTAR1-speed1)-1;
        } else if (fplay1) {
        IOTAR1 = IOTAR1+speed1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):(IOTAR1+speed1)+1;
        }
		
        float fTemp4 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iTemp3 != iRec3[1]))))?fConst0:((int(((fRec2[1] == 1.0f) & (iTemp3 != iRec4[1]))))?fConst1:0)));
		fRec1[0] = fTemp4;
		fRec2[0] = fmax(0.0f, fmin(1.0f, (fRec2[1] + fTemp4)));
		iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iTemp3))))?iTemp3:iRec3[1]);
		iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iTemp3))))?iTemp3:iRec4[1]);
		iVec2[0] = iSlow6;
		float fTemp5 = (iSlow6 * fTemp0);
		RecSize2[0] = fmin(4194304, (int)(iSlow7 * (((iSlow6 - iVec2[1]) <= 0) * (iSlow6 + RecSize2[1]))));
		int iTemp6 = (4194304 - RecSize2[0]);
		rectime1 = iTemp6*fConst2;
		int iTemp7 = fmin(4194304-1, (int)(4194304 - iTemp6));
		if (iSlow6 == 1) {
		IOTA2 = IOTA2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):IOTA2+1;
		tape2[IOTA2] = fTemp5;
        }
		if (rfplay2) {
        IOTAR2 = IOTAR2-speed2< (iTemp7 - int(iTemp7*iClips2))? int(iTemp7*iClip2):(IOTAR2-speed2)-1;
        } else if (fplay2) {
        IOTAR2 = IOTAR2+speed2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):(IOTAR2+speed2)+1;
        }
		
        float fTemp8 = ((int((fRec6[1] != 0.0f)))?((int(((fRec7[1] > 0.0f) & (fRec7[1] < 1.0f))))?fRec6[1]:0):((int(((fRec7[1] == 0.0f) & (iTemp7 != iRec8[1]))))?fConst0:((int(((fRec7[1] == 1.0f) & (iTemp7 != iRec9[1]))))?fConst1:0)));
		fRec6[0] = fTemp8;
		fRec7[0] = fmax(0.0f, fmin(1.0f, (fRec7[1] + fTemp8)));
		iRec8[0] = ((int(((fRec7[1] >= 1.0f) & (iRec9[1] != iTemp7))))?iTemp7:iRec8[1]);
		iRec9[0] = ((int(((fRec7[1] <= 0.0f) & (iRec8[1] != iTemp7))))?iTemp7:iRec9[1]);
		iVec4[0] = iSlow9;
		float fTemp9 = (iSlow9 * fTemp0);
		RecSize3[0] = fmin(4194304, (int)(iSlow10 * (((iSlow9 - iVec4[1]) <= 0) * (iSlow9 + RecSize3[1]))));
		int iTemp10 = (4194304 - RecSize3[0]);
		rectime2 = iTemp10*fConst2;
		int iTemp11 = fmin(4194304-1, (int)(4194304 - iTemp10));
		if (iSlow9 == 1) {
		IOTA3 = IOTA3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):IOTA3+1;
		tape3[IOTA3] = fTemp9;
        }
		if (rfplay3) {
        IOTAR3 = IOTAR3-speed3< (iTemp11 - int(iTemp11*iClips3))? int(iTemp11*iClip3):(IOTAR3-speed3)-1;
        } else if (fplay3) {
        IOTAR3 = IOTAR3+speed3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):(IOTAR3+speed3)+1;
        }
		
        float fTemp12 = ((int((fRec11[1] != 0.0f)))?((int(((fRec12[1] > 0.0f) & (fRec12[1] < 1.0f))))?fRec11[1]:0):((int(((fRec12[1] == 0.0f) & (iTemp11 != iRec13[1]))))?fConst0:((int(((fRec12[1] == 1.0f) & (iTemp11 != iRec14[1]))))?fConst1:0)));
		fRec11[0] = fTemp12;
		fRec12[0] = fmax(0.0f, fmin(1.0f, (fRec12[1] + fTemp12)));
		iRec13[0] = ((int(((fRec12[1] >= 1.0f) & (iRec14[1] != iTemp11))))?iTemp11:iRec13[1]);
		iRec14[0] = ((int(((fRec12[1] <= 0.0f) & (iRec13[1] != iTemp11))))?iTemp11:iRec14[1]);
		iVec6[0] = iSlow12;
		float fTemp13 = (iSlow12 * fTemp0);
		RecSize4[0] = fmin(4194304, (int)(iSlow13 * (((iSlow12 - iVec6[1]) <= 0) * (iSlow12 + RecSize4[1]))));
		int iTemp14 = (4194304 - RecSize4[0]);
		rectime3 = iTemp14*fConst2;
		int iTemp15 = fmin(4194304-1, (int)(4194304 - iTemp14));
		if (iSlow12 == 1) {
		IOTA4 = IOTA4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):IOTA4+1;
		tape4[IOTA4] = fTemp13;
        }
		if (rfplay4) {
        IOTAR4 = IOTAR4-speed4< (iTemp15 - int(iTemp15*iClips4))? int(iTemp15*iClip4):(IOTAR4-speed4)-1;
        } else if (fplay4) {
        IOTAR4 = IOTAR4+speed4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):(IOTAR4+speed4)+1;
        }
		
        float fTemp16 = ((int((fRec16[1] != 0.0f)))?((int(((fRec17[1] > 0.0f) & (fRec17[1] < 1.0f))))?fRec16[1]:0):((int(((fRec17[1] == 0.0f) & (iTemp15 != iRec18[1]))))?fConst0:((int(((fRec17[1] == 1.0f) & (iTemp15 != iRec19[1]))))?fConst1:0)));
		fRec16[0] = fTemp16;
		fRec17[0] = fmax(0.0f, fmin(1.0f, (fRec17[1] + fTemp16)));
		iRec18[0] = ((int(((fRec17[1] >= 1.0f) & (iRec19[1] != iTemp15))))?iTemp15:iRec18[1]);
		iRec19[0] = ((int(((fRec17[1] <= 0.0f) & (iRec18[1] != iTemp15))))?iTemp15:iRec19[1]);
		output0[i] = (float)((fSlow15 * ((fSlow14 * ((fRec17[0] * tape4[int(IOTAR4)]) + ((1.0f - fRec17[0]) * tape4[int(IOTAR4)]))) + ((fSlow11 * ((fRec12[0] * tape3[int(IOTAR3)]) + ((1.0f - fRec12[0]) * tape3[int(IOTAR3)]))) + ((fSlow8 * ((fRec7[0] * tape2[int(IOTAR2)]) + ((1.0f - fRec7[0]) * tape2[int(IOTAR2)]))) + (fSlow5 * ((fRec2[0] * tape1[int(IOTAR1)]) + ((1.0f - fRec2[0]) * tape1[int(IOTAR1)]))))))) + (fTemp0));
		// post processing
		iRec19[1] = iRec19[0];
		iRec18[1] = iRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		RecSize4[1] = RecSize4[0];
		iVec6[1] = iVec6[0];
		iRec14[1] = iRec14[0];
		iRec13[1] = iRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		RecSize3[1] = RecSize3[0];
		iVec4[1] = iVec4[0];
		iRec9[1] = iRec9[0];
		iRec8[1] = iRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		RecSize2[1] = RecSize2[0];
		iVec2[1] = iVec2[0];
		iRec4[1] = iRec4[0];
		iRec3[1] = iRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		RecSize1[1] = RecSize1[0];
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
	}
#undef fclip1
#undef fclip2
#undef fclip3
#undef fclip4
#undef fclips1
#undef fclips2
#undef fclips3
#undef fclips4
#undef fspeed1
#undef fspeed2
#undef fspeed3
#undef fspeed4
#undef fgain
#undef gain1
#undef gain2
#undef gain3
#undef gain4
#undef gain_out
#undef fplay1
#undef fplay2
#undef fplay3
#undef fplay4
#undef rfplay1
#undef rfplay2
#undef rfplay3
#undef rfplay4
#undef fplayh1
#undef fplayh2
#undef fplayh3
#undef fplayh4
#undef record1
#undef record2
#undef record3
#undef record4
#undef freset1
#undef freset2
#undef freset3
#undef freset4
}

void __rt_func LiveLooper::compute_static(int count, float *input0, float *output0, PluginLV2 *p)
{
	static_cast<LiveLooper*>(p)->compute(count, input0, output0);
}

void LiveLooper::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case clip1: 
		fclip1_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
		break;
	case clip2: 
		fclip2_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
		break;
	case clip3: 
		fclip3_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
		break;
	case clip4: 
		fclip4_ = (float*)data; // , 1e+02f, 0.0f, 1e+02f, 1.0f 
		break;
	case clips1: 
		fclips1_ = (float*)data; // ,  0.0f, 0.0f, 1e+02f, 1.0f 
		break;
	case clips2: 
		fclips2_ = (float*)data; // ,  0.0f, 0.0f, 1e+02f, 1.0f 
		break;
	case clips3: 
		fclips3_ = (float*)data; // ,  0.0f, 0.0f, 1e+02f, 1.0f 
		break;
	case clips4: 
		fclips4_ = (float*)data; // ,  0.0f, 0.0f, 1e+02f, 1.0f 
		break;
	case speed1: 
		fspeed1_ = (float*)data; // ,  0.0f, -0.9f, 0.9f, 0.01f 
		break;
	case speed2: 
		fspeed2_ = (float*)data; // ,  0.0f, -0.9f, 0.9f, 0.01f 
		break;
	case speed3: 
		fspeed3_ = (float*)data; // ,  0.0f, -0.9f, 0.9f, 0.01f 
		break;
	case speed4: 
		fspeed4_ = (float*)data; // ,  0.0f, -0.9f, 0.9f, 0.01f 
		break;
	case bar1: 
		rectime0_ = (float*)data; // ,  0.0, 0.0, 96.0, 1.0 
		break;
	case bar2: 
		rectime1_ = (float*)data; // ,  0.0, 0.0, 96.0, 1.0 
		break;
	case bar3: 
		rectime2_ = (float*)data; // ,  0.0, 0.0, 96.0, 1.0 
		break;
	case bar4: 
		rectime3_ = (float*)data; // ,  0.0, 0.0, 96.0, 1.0 
		break;
	case gain: 
		fgain_ = (float*)data; // ,  0.0f, -2e+01f, 12.0f, 0.1f 
		break;
	case level1: 
		gain1_ = (float*)data; // ,  5e+01f, 0.0f, 1e+02f, 1.0f 
		break;
	case level2: 
		gain2_ = (float*)data; // ,  5e+01f, 0.0f, 1e+02f, 1.0f 
		break;
	case level3: 
		gain3_ = (float*)data; // ,  5e+01f, 0.0f, 1e+02f, 1.0f 
		break;
	case level4: 
		gain4_ = (float*)data; // ,  5e+01f, 0.0f, 1e+02f, 1.0f 
		break;
	case mix: 
		gain_out_ = (float*)data; // ,  1e+02f, 0.0f, 1.5e+02f, 1.0f 
		break;
	case play1: 
		fplay1_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case play2: 
		fplay2_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case play3: 
		fplay3_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case play4: 
		fplay4_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rplay1: 
		rfplay1_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rplay2: 
		rfplay2_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rplay3: 
		rfplay3_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rplay4: 
		rfplay4_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case playh1: 
		fplayh1_ = (float*)data; // ,  0.0, 0.0, 1000.0, 1.0
		break;
	case playh2: 
		fplayh2_ = (float*)data; // ,  0.0, 0.0, 1000.0, 1.0
		break;
	case playh3: 
		fplayh3_ = (float*)data; // ,  0.0, 0.0, 1000.0, 1.0
		break;
	case playh4: 
		fplayh4_ = (float*)data; // ,  0.0, 0.0, 1000.0, 1.0
		break;
	case rec1: 
		record1_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rec2: 
		record2_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rec3: 
		record3_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case rec4: 
		record4_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case reset1: 
		freset1_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case reset2: 
		freset2_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case reset3: 
		freset3_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	case reset4: 
		freset4_ = (float*)data; // ,  0.0, 0.0, 1.0, 1.0
		break;
	default:
		break;
	}
}

void LiveLooper::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<LiveLooper*>(p)->connect(port, data);
}

PluginLV2 *plugin() {
	return new LiveLooper();
}

void LiveLooper::del_instance(PluginLV2 *p)
{
	delete static_cast<LiveLooper*>(p);
}

/*
typedef enum
{
    clip1,
    clip2,
    clip3,
    clip4,
    clips1,
    clips2,
    clips3,
    clips4,
    speed1,
    speed2,
    speed3,
    speed4,
    bar1,
    bar2,
    bar3,
    bar4,
    gain,
    level1,
    level2,
    level3,
    level4,
    mix,
    play1,
    play2,
    play3,
    play4,
    rplay1,
    rplay2,
    rplay3,
    rplay4,
    playh1,
    playh2,
    playh3,
    playh4,
    rec1,
    rec2,
    rec3,
    rec4,
    reset1,
    reset2,
    reset3,
    reset4,
} PortIndex;
*/
} // end namespace livelooper
