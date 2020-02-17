const char* styles_css = "/****************************************************************\
 * Basic settings for GX Widgets\
 ****************************************************************/\
/* GxSwitch */\
/* line 7, ../rcstyles/minimal.scss */\
.gx_switch check {\
  -gtk-icon-transform: none;\
  -gtk-icon-shadow: none;\
  background-image: none;\
  transition-duration: 0;\
  /*transition-property: none;*/\
  /* no need for reset if duration is 0 */\
  border: none;\
  box-shadow: none;\
  text-shadow: none;\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_button check {\
  -gtk-icon-source: -gtk-icontheme(\"button_off\");\
  min-width: 16px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_button check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"button_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_bypass check {\
  -gtk-icon-source: -gtk-icontheme(\"bypass_off\");\
  min-width: 14px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_bypass check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"bypass_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_cycle check {\
  -gtk-icon-source: -gtk-icontheme(\"cycle_off\");\
  min-width: 15px;\
  min-height: 15px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_cycle check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"cycle_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_fbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"fbutton_off\");\
  min-width: 15px;\
  min-height: 15px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_fbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"fbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_follow check {\
  -gtk-icon-source: -gtk-icontheme(\"follow_off\");\
  min-width: 14px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_follow check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"follow_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_frbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"frbutton_off\");\
  min-width: 21px;\
  min-height: 19px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_frbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"frbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_led check {\
  -gtk-icon-source: -gtk-icontheme(\"led_off\");\
  min-width: 20px;\
  min-height: 20px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_led check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"led_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_minitoggle check {\
  -gtk-icon-source: -gtk-icontheme(\"minitoggle_off\");\
  min-width: 10px;\
  min-height: 10px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_minitoggle check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"minitoggle_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_overdub check {\
  -gtk-icon-source: -gtk-icontheme(\"overdub_off\");\
  min-width: 15px;\
  min-height: 15px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_overdub check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"overdub_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_pbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"pbutton_off\");\
  min-width: 14px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_pbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"pbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_pcycle check {\
  -gtk-icon-source: -gtk-icontheme(\"pcycle_off\");\
  min-width: 15px;\
  min-height: 15px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_pcycle check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"pcycle_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_plus check {\
  -gtk-icon-source: -gtk-icontheme(\"plus_off\");\
  min-width: 16px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_plus check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"plus_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_prbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"prbutton_off\");\
  min-width: 14px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_prbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"prbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_rbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"rbutton_off\");\
  min-width: 16px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_rbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"rbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_resetbutton check {\
  -gtk-icon-source: -gtk-icontheme(\"resetbutton_off\");\
  min-width: 14px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_resetbutton check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"resetbutton_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_switchit check {\
  -gtk-icon-source: -gtk-icontheme(\"switchit_off\");\
  min-width: 37px;\
  min-height: 28px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_switchit check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"switchit_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_switch_mid check {\
  -gtk-icon-source: -gtk-icontheme(\"switch_mid_off\");\
  min-width: 10px;\
  min-height: 10px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_switch_mid check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"switch_mid_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_switch_min check {\
  -gtk-icon-source: -gtk-icontheme(\"switch_min_off\");\
  min-width: 7px;\
  min-height: 7px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_switch_min check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"switch_min_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_switch check {\
  -gtk-icon-source: -gtk-icontheme(\"switch_off\");\
  min-width: 16px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_switch check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"switch_on\");\
}\
\
/* line 19, ../rcstyles/minimal.scss */\
.gx_sw_sync check {\
  -gtk-icon-source: -gtk-icontheme(\"sync_off\");\
  min-width: 16px;\
  min-height: 16px;\
}\
\
/* line 23, ../rcstyles/minimal.scss */\
.gx_sw_sync check:checked {\
  -gtk-icon-source: -gtk-icontheme(\"sync_on\");\
}\
\
/* line 50, ../rcstyles/minimal.scss */\
.gx_sw_frbutton check {\
  padding: 4px 30px 4px 30px;\
}\
\
/* line 54, ../rcstyles/minimal.scss */\
.gx_sw_bypass check {\
  padding: 0px 0px 0px 8px;\
}\
\
/* GxWheel */\
/* line 60, ../rcstyles/minimal.scss */\
gx-wheel {\
  -GxWheel-stock-wheel-back: \"tactile_wheel_101f.png\";\
  -GxWheel-framecount: 101;\
  /* use 0 for auto (assumes square frames)\
				 and >1 for non squareframe animations */\
}\
\
/* GxPlayHead */\
/* line 68, ../rcstyles/minimal.scss */\
gx-play-head {\
  -GxPortDisplay-stock-portdisplay: \"playhead.png\";\
  -GxRegler-show-value: 0;\
}\
\
/* GxWaveView */\
/* line 75, ../rcstyles/minimal.scss */\
gx-wave-view {\
  background-image: linear-gradient(to top, rgba(255, 51, 0, 0.5) 12.5%, rgba(255, 207, 0, 0.5) 40%, rgba(255, 207, 0, 0.5) 60%, rgba(255, 51, 0, 0.5) 87.5%);\
  color: #999999;\
  font: 6pt \"sans\";\
}\
\
/* GxPaintBox */\
/* line 89, ../rcstyles/minimal.scss */\
gx-paint-box {\
  -GxPaintBox-bevel: 0.11;\
  -GxPaintBox-inverse: 0;\
  -GxPaintBox-alternate-box: 60 0 0 0;\
  -GxPaintBox-width: 600;\
  -GxPaintBox-height: 180;\
  -GxPaintBox-icon-set: 7;\
  -GxPaintBox-stock-gxhead: \"live_wallpaper.png\";\
}\
\
/* GxIREdit */\
/* line 101, ../rcstyles/minimal.scss */\
gx-ir-edit {\
  -GxIREdit-shade-alpha: 0.6;\
  -GxIREdit-gain-line-color: #77984f;\
  -GxIREdit-zoom-marker-color: blue;\
  -GxIREdit-no-data-color: darkorange;\
  -GxIREdit-sample-graph-color: darkorange;\
  -GxIREdit-sample-graph-color-out: darkorange;\
}\
\
/* GxSelector */\
/* line 112, ../rcstyles/minimal.scss */\
gx-selector {\
  /*padding: 4px 4px 4px 4px;*/\
  /*border: 4px 32px 4px 8px solid #272727;*/\
  border-style: solid;\
  border-color: #272727;\
  border-width: 4px 24px 4px 8px;\
  padding-top: 3px;\
  background-color: black;\
  color: #ff9000;\
  /*-GxRegler-value-border: 2px 4px 8px 4px;*/\
  /*-GxRegler-value-border: 2px 4px 2px 4px;*/\
  -GxRegler-value-border: 1px 4px 0px 4px;\
  -GxRegler-border-radius: 0px;\
  font-size: 10px;\
  /*padding: 2px 0px 0px 8px;*/\
  border-radius: 3px;\
  -GxRegler-bevel: 0.12;\
}\
\
/* GxRegler + Knobs */\
/* line 132, ../rcstyles/minimal.scss */\
gx-regler,\
gx-knob,\
gx-small-knob,\
gx-small-knob-r,\
gx-mid-knob,\
gx-big-knob {\
  font: 7pt \"Roboto Condensed Regular\";\
  -GxRegler-value-border: 2px 4px 2px 4px;\
  /* border around text */\
  -GxRegler-border-radius: 6px;\
  -GxRegler-bevel: 0.12;\
  -GxKnob-x-center: -1;\
  -GxKnob-y-center: -1;\
  padding: 4px 8px 4px 8px;\
  color: #ff9000;\
  /* text */\
  background-color: #222222;\
  /* border */\
}\
\
/* line 150, ../rcstyles/minimal.scss */\
gx-regler:disabled,\
gx-knob:disabled,\
gx-small-knob:disabled,\
gx-small-knob-r:disabled,\
gx-mid-knob:disabled,\
gx-big-knob:disabled {\
  color: #211006;\
}\
\
/* line 155, ../rcstyles/minimal.scss */\
gx-small-knob {\
  -GxKnob-ring-radius: 15;\
  -GxKnob-ring-width: 2;\
  -GxKnob-ring-led-size: 3;\
  -GxKnob-ring-led-distance: 2;\
  -GxKnob-indicator-radius: 11;\
  -GxKnob-indicator-width: 2;\
  -GxKnob-indicator-length: 5;\
}\
\
/* line 165, ../rcstyles/minimal.scss */\
gx-small-knob-r {\
  -GxKnob-ring-radius: 26;\
  -GxKnob-ring-width: 3;\
  -GxKnob-ring-led-size: 3;\
  -GxKnob-ring-led-distance: 2;\
  -GxKnob-indicator-radius: 12;\
  -GxKnob-indicator-width: 3;\
  -GxKnob-indicator-length: 3;\
}\
\
/* line 175, ../rcstyles/minimal.scss */\
gx-mid-knob {\
  -GxKnob-ring-radius: 35;\
  -GxKnob-ring-width: 6;\
  -GxKnob-ring-led-size: 2;\
  -GxKnob-ring-led-distance: 2;\
  -GxKnob-indicator-radius: 27;\
  -GxKnob-indicator-width: 2;\
  -GxKnob-indicator-length: 6;\
}\
\
/* line 185, ../rcstyles/minimal.scss */\
gx-big-knob {\
  -GxKnob-ring-radius: 50.5;\
  -GxKnob-ring-width: 3;\
  -GxKnob-ring-led-size: 0;\
  -GxKnob-ring-led-distance: 0;\
  -GxKnob-indicator-radius: 46;\
  -GxKnob-indicator-width: 3;\
  -GxKnob-indicator-length: 6;\
}\
\
/* GxValueDisplay */\
/* line 197, ../rcstyles/minimal.scss */\
gx-value-display {\
  font: 7pt \"Roboto Condensed Regular\";\
  -GxRegler-value-border: 4px 8px 4px 8px;\
  /* -GxRegler-value-border: 2px 4px 2px 4px; / border around text */\
  -GxRegler-border-radius: 6px;\
  -GxRegler-value-spacing: 0px;\
  color: #ff9000;\
  /* text */\
  background-color: #222222;\
  /* border */\
}\
\
/* GxFastMeter */\
/* line 209, ../rcstyles/minimal.scss */\
gx-fast-meter {\
  padding: 4px 8px 4px 8px;\
  background-color: #222222;\
  /* border */\
  -GxFastMeter-clr-bottom: #b96901;\
  -GxFastMeter-clr-middle: #d4cd00;\
  -GxFastMeter-clr-top: #ff0500;\
  -GxFastMeter-over: #ff1100;\
  -GxFastMeter-mid-pos: 0.717;\
  -GxFastMeter-dimen: 2;\
  -GxFastMeter-led-border: 1;\
  -GxFastMeter-led-width: 2;\
  -GxFastMeter-led-height: 2;\
}\
\
/* line 223, ../rcstyles/minimal.scss */\
gx-fast-meter:hover {\
  background-color: #222222;\
  /* border hover */\
}\
\
/* GxHSlider */\
/* line 230, ../rcstyles/minimal.scss */\
gx-hslider {\
  -GxHSlider-slider-width: 36;\
}\
\
/* GxMeterScale */\
/* line 236, ../rcstyles/minimal.scss */\
gx-meter-scale {\
  padding: 2px 8px 2px 8px;\
  -GxMeterScale-tick-size: 3;\
  -GxMeterScale-tick-space: 1;\
}\
\
/* GxPortDisplay */\
/* line 244, ../rcstyles/minimal.scss */\
gx-port-display {\
  -GxRegler-show-value: 0;\
}\
\
/* line 246, ../rcstyles/minimal.scss */\
gx-port-display.playhead {\
  /* instead of icon \"portdisplay\" */\
  -GxPortDisplay-icon-name: \"playhead\";\
}\
\
/* GxLevelSlider */\
/* line 254, ../rcstyles/minimal.scss */\
gx-level-slider.lmw {\
  /* smaller slider for class lmw */\
  -GxLevelSlider-icon-name: \"simplelevelslider\";\
  -GxRegler-show-value: 0;\
  -GxLevelSlider-slider-width: 3;\
}\
\
/****************************************************************\
 * Rackbox\
 ****************************************************************/\
/* layout */\
/* line 267, ../rcstyles/minimal.scss */\
#monorackcontainer {\
  min-width: 600px;\
}\
\
/* line 271, ../rcstyles/minimal.scss */\
.minibox {\
  padding-left: 30px;\
}\
\
/* permanent value displays (are not switched off by preference option */\
/* line 277, ../rcstyles/minimal.scss */\
#tuner_reference_pitch,\
#amp #out_amp,\
#show_always,\
#gx_distortion #split_low_freqm,\
#gx_distortion #split_middle_freq,\
#gx_distortion #split_high_freq {\
  -GxRegler-show-value: 1;\
}\
\
/* specific parts */\
/* line 288, ../rcstyles/minimal.scss */\
#PLUI-ampstack #effect_title {\
  min-height: 36px;\
  margin-left: 71px;\
}\
\
/* line 294, ../rcstyles/minimal.scss */\
#tunerbox #vbox_tuner_main {\
  margin-left: 32px;\
  margin-right: 32px;\
  margin-bottom: 4px;\
}\
\
/* line 301, ../rcstyles/minimal.scss */\
#ampdetails > box {\
  margin-right: 28px;\
}\
\
/* line 307, ../rcstyles/minimal.scss */\
#hboxcenter .gx_sw_minitoggle,\
#ampdetails .gx_sw_minitoggle {\
  padding: 5px;\
}\
\
/* line 312, ../rcstyles/minimal.scss */\
#ampbox {\
  padding: 4px;\
}\
\
/* line 314, ../rcstyles/minimal.scss */\
#ampbox #gxlogobox {\
  -GxPaintBox-paint-func: \"logo_expose\";\
  min-height: 16px;\
}\
\
/* line 320, ../rcstyles/minimal.scss */\
#tuner_reference_pitch {\
  -GxRegler-value-spacing: 1;\
  -GxRegler-value-border: 5 8 6 8;\
  font-size: 7pt;\
}";
