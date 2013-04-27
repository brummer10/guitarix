/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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
 */


class MaxLevel: public PluginLV2 {
protected:
    float        maxlevel;
    float        resetmaxlevel;
    float        *resetmaxlevel_;
    float        *maxlevel_;

private:
    static void  init(unsigned int samplerate, PluginLV2 *plugin);
    static void  process(int count, float *input0, float *output0, PluginLV2*);
    static void  connect(uint32_t port,void* data, PluginLV2 *p);
    static void  del_instance(PluginLV2 *p);

public:
    static float get_level(MaxLevel& self) { return self.maxlevel;}
    MaxLevel();
    ~MaxLevel()  {};
};

MaxLevel::MaxLevel()
    : PluginLV2() {
    version = PLUGINLV2_VERSION;
    id = "maxlevel";
    name = "?maxlevel";
    set_samplerate = init;
    mono_audio = process;
    connect_ports = connect;
    activate_plugin = 0;
    delete_instance = del_instance;
}

void MaxLevel::init(unsigned int samplerate,PluginLV2 *plugin)
{
    MaxLevel& self = *static_cast<MaxLevel*>(plugin);
    self.maxlevel = 0;
    self.maxlevel_ = NULL;
    self.resetmaxlevel = 1;
    self.resetmaxlevel_ = NULL;
}

void MaxLevel::connect(uint32_t port,void* data, PluginLV2 *plugin)
{
    MaxLevel& self = *static_cast<MaxLevel*>(plugin);
    switch ((PortIndex)port)
    {
    case MAXL: 
      self.maxlevel_ = static_cast<float*>(data) ;
      break;
    case RESET: 
      self.resetmaxlevel_ = static_cast<float*>(data) ;
      break;
    default:
      break;
    }
}

void MaxLevel::process(int count, float *input1, float*, PluginLV2 *plugin) {
    MaxLevel& self = *static_cast<MaxLevel*>(plugin);
    if(abs(self.resetmaxlevel - *(self.resetmaxlevel_))>0.1) {
        self.maxlevel = 0;
        self.resetmaxlevel = *(self.resetmaxlevel_);
    }
    const float *data = input1;
        float level = 0;
        for (int i = 0; i < count; i++) {
            level = max(fabs(data[i]),level);
        }
        *(self.maxlevel_) = self.maxlevel = max(self.maxlevel, level);
}

PluginLV2 *vu_plugin() {
	return new MaxLevel();
}

void MaxLevel::del_instance(PluginLV2 *p)
{
	delete static_cast<MaxLevel*>(p);
}

