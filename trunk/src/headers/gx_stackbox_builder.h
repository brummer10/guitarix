#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

namespace gx_gui {

struct uiToggleButton : public gx_ui::GxUiItemBool {
    Gtk::ToggleButton* fButton;
    uiToggleButton(gx_ui::GxUI* ui, bool* zone, Gtk::ToggleButton* b)
                   : gx_ui::GxUiItemBool(ui, zone), fButton(b) {}
    void toggled();
    virtual void reflectZone();
};

/****************************************************************/

#define stackSize 256
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

class StackBoxBuilder {
protected:
    int&                  fTop;
    GtkWidget*            (&fBox)[stackSize];
    gx_engine::GxEngine&  engine;
    gx_engine::ParamMap&  pmap;
    int                   (&fMode)[stackSize];
    //MainMenu&             mainmenu;  // crash if before GxSettings though not clear why
    Gxw::WaveView&        fWaveView;
    Gtk::Label&           convolver_filename_label;
    gx_ui::GxUI&          ui;
    Glib::RefPtr<Gdk::Pixbuf> window_icon;

    static const          gboolean expand   = true;
    static const          gboolean fill     = true;
    static const          gboolean homogene = false;
    void loadRackFromGladeData(const char *xmldesc);
protected:
    virtual void openMonoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_pre_post, const char *id_dialog) = 0;
    virtual void closeMonoRackBox() = 0;
    virtual void openStereoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_dialog) = 0;
    virtual void closeStereoRackBox() = 0;
    virtual void openVerticalMidiBox(const char* label = "") = 0;
    // functions used in interfaces
    void create_master_slider(string id) {
            addwidget(UiRackMasterRegler::create(ui, new Gxw::HSlider(), id));
        }
    void create_master_slider(string id, Glib::ustring(label)) {
            addwidget(UiRackMasterRegler::create(ui, new Gxw::HSlider(), id, label));
        }

    void closeBox();
    void openSpaceBox(const char* label = "");
    void create_small_rackknob(string id) {
            addwidget(UiRackReglerWithCaption::create(ui, new Gxw::SmallKnob(), id));
        }
    void create_small_rackknob(string id, Glib::ustring label) {
            addwidget(UiRackReglerWithCaption::create(ui, new Gxw::SmallKnob(), id, label));
        }

    void create_small_rackknobr(string id) {
            addwidget(UiRackReglerWithCaption::create(ui, new Gxw::SmallKnobR(), id));
        }
    void create_small_rackknobr(string id, Glib::ustring label) {
            addwidget(UiRackReglerWithCaption::create(ui, new Gxw::SmallKnobR(), id, label));
        }

    void openVerticalBox(const char* label = "");
    void openFrameBox(const char* label);
    void openHorizontalBox(const char* label = "");
    void addLiveWaveDisplay(const char* label);
    void openVerticalHideBox(const char* label = "");
    void openHorizontalhideBox(const char* label = "");
    void openHorizontalTableBox(const char* label);
    void create_switch_no_caption(const char *sw_type, string id) {
            addwidget(UiSwitch::create(ui, sw_type, id));
        }
    void openpaintampBox(const char* label = "");
    void create_wheel(string id, bool show_value = false) {
            addwidget(UiRegler::create(ui, new Gxw::Wheel(), id, show_value));
        }
    void create_spin_value(string id) {
            addwidget(UiRegler::create(ui, new Gxw::ValueDisplay(), id, true));
        }
    void create_simple_spin_value(string id) {
            addwidget(UiRegler::create(ui, new Gxw::SimpleValueDisplay(), id, true));
        }
    void create_eq_rackslider_no_caption(string id) {
            addwidget(UiRackRegler::create(ui, new Gxw::EqSlider(), id));
        }
    void create_selector(string id, const char *widget_name=0);
    void openFlipLabelBox(const char* = "");
    void openVerticalBox1(const char* label = "");
    void openPaintBox2(const char* label = "");
    void openTabBox(const char* label = "");
    void addCheckButton(string id, const char* label = 0);
    void addNumEntry(string id, const char* label = 0);
    void addMToggleButton(string id, const char* label = 0);
    void addStatusDisplay(const char* label, bool* zone );
    void addSmallJConvFavButton(const char* label, gx_jconv::IRWindow *irw);
    void openSetLabelBox();
    void addJConvFavButton(const char* label, gx_jconv::IRWindow *irw);
    void addJConvButton(const char* label, float* zone, gx_jconv::IRWindow *irw);
    void addJToggleButton(const char* label, bool* zone);
protected:
    // functions used indirectly
    void          pushBox(int mode, GtkWidget* w);
    GtkWidget*            addWidget(const char* label, GtkWidget* w);
    void addwidget(GtkWidget *widget) {
	if (widget) gtk_container_add(GTK_CONTAINER(fBox[fTop]), widget);
    }
    void addwidget(Gtk::Widget *widget) {
	if (widget) {
	    gtk_container_add(GTK_CONTAINER(fBox[fTop]), manage(widget)->gobj());
	}
    }
    void addCheckButton(const char* label, bool* zone);
    void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    void addMToggleButton(const char* label, bool* zone);
public:
    StackBoxBuilder(
	int& fTop_, GtkWidget*(&fBox_)[stackSize], gx_engine::GxEngine& engine_,
	gx_engine::ParamMap& pmap_, int (&fMode_)[stackSize],
	Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_, gx_ui::GxUI& ui,
	Glib::RefPtr<Gdk::Pixbuf> window_icon);
    ~StackBoxBuilder();
    friend class UiBuilderImpl;
    // mono
    void make_rackbox_ampdetail();
    void make_rackbox_overdrive();
    void make_rackbox_echo();
    void make_rackbox_delay();
    void make_rackbox_freeverb();
    void make_rackbox_oscilloscope();
    void make_rackbox_low_highpass();
    void make_rackbox_eqs();
    void make_rackbox_crybaby();
    void make_rackbox_gx_distortion();
    void make_rackbox_IR();
    void make_rackbox_compressor();
    void make_rackbox_biquad();
    void make_rackbox_tremolo();
    void make_rackbox_phaser_mono();
    void make_rackbox_chorus_mono();
    void make_rackbox_flanger_mono();
    void make_rackbox_feedback();
    void make_rackbox_amp_tonestack();
    void make_rackbox_cab();
    void make_rackbox_midi_out();
    // stereo
    void make_rackbox_chorus();
    void make_rackbox_flanger();
    void make_rackbox_phaser();
    void make_rackbox_stereodelay();
    void make_rackbox_stereoecho();
    void make_rackbox_moog();
    void make_rackbox_ampmodul();
    void make_rackbox_tonemodul();
    void make_rackbox_jconv();
    void make_rackbox_stereoverb();
};

} // end namespace gx_gui
