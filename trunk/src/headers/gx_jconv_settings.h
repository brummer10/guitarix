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
 * --------------------------------------------------------------------------
 *
 *  This is the JConv settings handler class used by guitarix
 *  There can only be one instance at all time. To get a pointer
 *  to the unique instance, simply call
 *
 *  GxJConvSettings* jcset = GxJConvSettings::instance();
 *
 *  throughout the entire program.
 *
 *  This class belongs to the gx_jconv namespace
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#include <gxwmm/gainline.h>

namespace gx_jconv
{

/* GUI stuff  */
void gx_reload_jcgui();
void gx_save_jcgui();
void gx_show_jconv_dialog_gui (GtkWidget *, gpointer );

/* main class */
class GxJConvSettings
{
private:
	// main jconv setting
	string          fIRFile;
	string          fIRDir;

	float           fGain;       // jconv gain
	float           flGain;       // jconv left gain
	guint           fMem;        // memory partition
	jack_nframes_t  fBufferSize; // frag
	guint           fOffset;     // offset in IR where to start comvolution
	guint           fLength;     // length of the IR to use for convolution
	guint           fDelay;      // delay when to apply reverb
	guint           flDelay;      // left channel delay when to apply reverb
	Gainline        gainline;

	void read_gainline(gx_system::JsonParser& jp);
	void copy(const GxJConvSettings& s);

	// private constructor (don't call it, call instance())
	GxJConvSettings();

	// invalid IR
	bool fValidSettings;

public:
	GxJConvSettings(gx_system::JsonParser& jp);

	// getters and setters
	inline string getIRFile() const { return fIRFile; }
	inline string getIRDir () const { return fIRDir;  }

	inline string getFullIRPath() const {
		static string slash = "/";
		return fIRDir + slash + fIRFile;
	}

	inline float          getGain      () const { return fGain;       }
	inline float          getlGain     () const { return flGain;       }
	inline guint          getMem       () const { return fMem;        }
	inline jack_nframes_t getBufferSize() const { return fBufferSize; }
	inline guint          getOffset    () const { return fOffset;     }
	inline guint          getLength    () const { return fLength;     }
	inline guint          getDelay     () const { return fDelay;      }
	inline guint          getlDelay    () const { return flDelay;      }
	inline const Gainline& getGainline  () const { return gainline;    }

	inline void setIRFile    (string         name) { fIRFile     = name; }
	inline void setIRDir     (string         name) { fIRDir      = name; }
	inline void setGain      (float          gain)
		{
			gain = round(gain*100);
			fGain       = gain*0.01;
		}
	inline void setlGain      (float          gain)
		{
			gain = round(gain*100);
			flGain       = gain*0.01;
		}
	inline void setMem       (guint          mem ) { fMem        = mem;  }
	inline void setBufferSize(jack_nframes_t bs)   { fBufferSize = bs;   }
	inline void setOffset    (guint          offs) { fOffset     = offs; }
	inline void setLength    (guint          leng) { fLength     = leng; }
	inline void setDelay     (guint          del)  { fDelay      = del;  }
	inline void setlDelay    (guint          del)  { flDelay     = del;  }
	inline void setGainline  (const Gainline& gain){ gainline    = gain; }

	// internal setting manipulation
private:
	inline bool isValid()  { return fValidSettings;  }
	void validate();
	void invalidate();
	void resetSetting();
public:

	// --------------- instanciation of jconv handler
	static inline GxJConvSettings* instance()
		{
			static GxJConvSettings jcset;

			// return static instance
			return &jcset;
		}


	// checkbutton state
	static float checkbutton7;

	void writeJSON(gx_system::JsonWriter& w);
};
} /* end of gx_jconv namespace*/

