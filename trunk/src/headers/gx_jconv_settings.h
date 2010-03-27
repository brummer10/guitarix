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

namespace gx_jconv
{
// read mode
typedef enum {
	kJConvCopy = 0,
	kJConvRead = 1
} GxJConvMode;

// parameter type
typedef enum {
	kJConvGain = 0,
	kJConvlGain,
	kJConvMem,
	kJConvBuffersize,
	kJConvMode,
	kJConvOffset,
	kJConvLength,
	kJConvDelay,
	kJConvlDelay
} GxJConvParamType;

/* GUI stuff  */
void gx_reload_jcgui();
void gx_show_jconv_dialog_gui (GtkWidget *, gpointer );
void gx_setting_jconv_dialog_gui(GtkWidget*, gpointer);
void gx_acquire_jconv_value     (GtkWidget*, gpointer);
void gx_resample_jconv_ir       (GtkWidget*, gpointer);
void gx_select_and_draw_jconv_ir(GtkWidget*, gpointer);

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
	GxJConvMode     fMode;       // mode (copy or read)
	jack_nframes_t  fBufferSize; // frag
	guint           fOffset;     // offset in IR where to start comvolution
	guint           fLength;     // length of the IR to use for convolution
	guint           fDelay;      // delay when to apply reverb
	guint           flDelay;      // left channel delay when to apply reverb

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
	inline GxJConvMode    getMode      () const { return fMode;       }
	inline jack_nframes_t getBufferSize() const { return fBufferSize; }
	inline guint          getOffset    () const { return fOffset;     }
	inline guint          getLength    () const { return fLength;     }
	inline guint          getDelay     () const { return fDelay;      }
	inline guint          getlDelay    () const { return flDelay;      }

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
	inline void setMode      (GxJConvMode    mode) { fMode       = mode; }
	inline void setBufferSize(jack_nframes_t bs)   { fBufferSize = bs;   }
	inline void setOffset    (guint          offs) { fOffset     = offs; }
	inline void setLength    (guint          leng) { fLength     = leng; }
	inline void setDelay     (guint          del)  { fDelay      = del;  }
	inline void setlDelay    (guint          del)  { flDelay     = del;  }

	// internal setting manipulation
	inline bool isValid()  { return fValidSettings;  }
	void validate();
	void invalidate();
	void resetSetting();


	// --------------- instanciation of jconv handler
	static inline GxJConvSettings* instance()
		{
			static GxJConvSettings jcset;

			// return static instance
			return &jcset;
		}


	// checkbutton state
	static float checkbutton7;

	// dump parameters on demand to stderr
	void dumpParameters();

	void writeJSON(gx_system::JsonWriter& w);
};
} /* end of gx_jconv namespace*/

