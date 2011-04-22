/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head interface builder,
 *    it's a part of the class GxMainInterface
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"
#include <glibmm/i18n.h>

//-------- the gx_head user interface build instruktions

namespace gx_gui {

#ifndef NDEBUG
// debug_check
inline void all_midi_params_assigned()
{
     for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
          if (i->second->isControllable() && ! i->second->isUsed() && ! i->second->isExperimental())
               gx_system::gx_print_error("Debug Check",
                                         "midi-parameter not assigned in ui: " + i->first);
     }
}
#endif

/* -------- user interface builder ---------- */
void GxMainInterface::setup()
{
	
     //----- the main box, all visible widgets are a child of this box
     openVerticalBox("");

     //----- add the menubar on top
     {
          addMainMenu();
      openHorizontalBox("");
      {    
		  openVerticalBox("");
          {
			  openToolBar(_("Plugins"));
			  {
			  }
			  closeBox();	
			  addNumDisplay();
		  }
		  closeBox();	 
		  
       openVerticalBox("");
       {
		   
          openEventBox(" ");
          {
               //----- this is a dummy widget, only for save settings for the latency warning dialog
               openWarningBox("WARNING", &gx_engine::audio.fwarn);
               setSkinBox("SKIN", &gx_engine::audio.fskin);
               openHorizontalBox("");
               {
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();

                    openFlipLabelBox("gx-2    ");
                    {
                         openHorizontalBox("");
                         {
                              openSpaceBox("");
                              closeBox();
                              openSpaceBox("");
                              closeBox();


                              openVerticalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   create_bigknob("amp2.stage1.Pregain", _("Pre gain"));
                                   openSpaceBox("");
                                   closeBox();

                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();



                              openVerticalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();


                                   create_bigknob("gxdistortion.drive",_("  Drive "));
                                   openSpaceBox("");
                                   closeBox();

                              }
                              closeBox();

                              openSpaceBox("");
                              closeBox();




                              openHorizontalBox("");
                              {
                                   openVerticalBox("");
                                   {
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();


                                        create_bigknob("amp2.stage2.gain1", _("Master gain"));
                                        openSpaceBox("");
                                        closeBox();

                                   }
                                   closeBox();

                              }
                              closeBox();//end switchbox
                              openSpaceBox("");
                              closeBox();




                              openFlipLabelBox(_("tone"));
                              {
                                   openVerticalBox("");
                                   {
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();


                                        openSpaceBox("");
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             openSpaceBox("");
                                             closeBox();
                                             create_smallknob("amp.tonestack.Bass",_("Bass"));
                                             openSpaceBox("");
                                             closeBox();
                                             create_smallknob("amp.tonestack.Middle",_("Middle"));
                                             openSpaceBox("");
                                             closeBox();
                                             create_smallknob("amp.tonestack.Treble",_("Treble"));
                                             openSpaceBox("");
                                             closeBox();
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             openVerticalBox1("");
                                             closeBox();
                                             create_switch(sw_minitoggle, "amp.bass_boost.on_off", _(" Bass boost  "), Gtk::POS_RIGHT);
                                             openSpaceBox("");
                                             closeBox();
                                             openSpaceBox("");
                                             closeBox();
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             openVerticalBox1("");
                                             closeBox();
                                             create_cab_switch("cab.on_off",_(" Cabinet        "), Gtk::POS_RIGHT);
                                             openSpaceBox("");
                                             closeBox();
                                             openSpaceBox("");
                                             closeBox();
                                        }
                                        closeBox();
                                        openHorizontalBox("");
                                        {
                                             create_selector("amp.tonestack.select");
                                             openVerticalBox1("");
                                             closeBox();
                                        }
                                        closeBox();
                                        openSpaceBox("");
                                        closeBox();
                                   }
                                   closeBox();

                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openSpaceBox("");
                              closeBox();

                              openVerticalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   create_switch(sw_minitoggle, "amp.feed_on_off", _(" reverb  "), Gtk::POS_RIGHT);
                                   create_minislider("amp.wet_dry");
                                   openSpaceBox("");
                                   closeBox();
                                   openSpaceBox("");
                                   closeBox();
                                   openVerticalBox1("Convolver");
                                   {
                                   }
                                   closeBox();
                                   addJConvButton(_("set"), &gx_engine::audio.filebutton);
                                   addJToggleButton(_("run"), &gx_jconv::GxJConvSettings::checkbutton7);

                                   openSpaceBox("");
                                   closeBox();
                              }
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openSpaceBox("");
                              closeBox();
                              openVerticalBox("");
                              {
                                   openSpaceBox("");
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                                   openHorizontalBox("");
                                   {
                                        openFrameBox("");
                                        closeBox();
                                        // add a meter level box: out of box stack, no need to closeBox
                                        openLevelMeterBox("Signal Level");
                                        openFrameBox("");
                                        closeBox();
                                   }
                                   closeBox();
                                   openFrameBox("");
                                   closeBox();
                              }
                              closeBox();

                              openSpaceBox("");
                              closeBox();
                              openSpaceBox("");
                              closeBox();

                         }
                         closeBox();
                         openSpaceBox("");
                         closeBox();
                         openSpaceBox("");
                         closeBox();
                         openSpaceBox("");
                         closeBox();
                    }
                    closeBox();
                    openSpaceBox("");
                    closeBox();

                    openSpaceBox("");
                    closeBox();

                    openSpaceBox("");
                    closeBox();
                    openSpaceBox("");
                    closeBox();

                    openSpaceBox("");
                    closeBox();

                    openSpaceBox("");
                    closeBox();
               }
               closeBox();
          }
          closeBox();
         
         
		
		
		 openScrollBox("");
               {
		 openPlugBox(_("Mono Rack"));
		 {
			#include "gx_rack_builder.cc"		
		 }
		 closeBox();
		 
		 openAmpBox(_("Stereo Rack"));
		 {
			#include "gx_srack_builder.cc"		
		 }
		 closeBox();
		 }
		 closeBox();
		  }
		 closeBox();
	  }
      closeBox(); 
      }
      closeBox(); 
     // add a Patch Info widget
     openPatchInfoBox(&gx_gui::show_patch_info);
     
     openTextLoggingBox(_("Logging Window"));
	 
     debug_check(all_midi_params_assigned);
	}

}
