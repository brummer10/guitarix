namespace gx_gui { class GxMainInterface; }

class uibuilder {
private:
  gx_gui::GxMainInterface *intf;
public:
  uibuilder(gx_gui::GxMainInterface *i): intf(i) {}
  void openVerticalBox(const char* label = "") const;
  void openHorizontalBox(const char* label = "") const;
  void create_small_rackknob(const char *id) const;
  void create_small_rackknob(const char *id, const char *label) const;
  void closeBox() const;
};

class paramreg {
public:
  void registerVar(const char* id, const char* name, const char* tp,
		   const char* tooltip, float* var, float val = 0,
		   float low = 0, float up = 0, float step = 0,
		   bool exp = false) const;
};

typedef void (*inifunc)(int samplingFreq);
typedef int (*activatefunc)(bool start, int samplingFreq);
//typedef void (*process_mono_audio) (int count, float *buffer);
//typedef void (*process_stereo_audio) (int count, float *buffer1, float *buffer2);
typedef void (*process_mono_audio) (int count, float *input, float *output);
typedef void (*process_stereo_audio) (int count, float *input1, float *input2, float *output1, float *output2);
typedef int (*registerfunc)(const paramreg& reg);
typedef int (*uiloader)(const uibuilder& builder);

enum {
  PGN_NO_PRE  = 0x01,
  PGN_NO_POST = 0x02,
};

#define PLUGINDEF_VERSION 0x0100
#define PLUGINDEF_VERMAJOR 0xff00

struct plugindef {
  int version;
  int flags;
  const char* id;
  const char* name;
  process_mono_audio mono_audio;
  process_stereo_audio stereo_audio;
  inifunc set_samplerate;
  activatefunc activate_plugin;
  registerfunc register_params;
  uiloader load_ui;
  };

typedef int (*plugin_inifunc)(int *count, plugindef **p);
