 
- [Global options](#global-options)
  - [**Engine**](#engine)
  - [**Presets**](#presets)
  - [**Plugins**](#plugins)
  - [**Tube**](#tube)
  - [**Options**](#options)
  - [**About**](#about)
  - [Pool](#pool)
  - [Order](#order)
  - [Tuner](#tuner)
  - [Rack](#rack)
  - [Split](#split)
  - [Fold/Show](#foldshow)
  - [Live](#live)
- [Main view](#main-view)
  - [Plugin bar](#plugin-bar)
  - [Signal chain](#signal-chain)
- [Bottom bar](#bottom-bar)
  - [Preset button](#preset-button)
  - [Preset name](#preset-name)
  - [Bypass Jack insert ports](#bypass-jack-insert-ports)
  - [Engine Status](#engine-status)
  - [Jack Connection Status](#jack-connection-status)
  - [Status of Events](#status-of-events)

Guitarix is fully resizable. Just drag the bottom-right corner to adjust width and height.

## Global options

### **Engine**

- Engine mute: mute the entire signal chain
- Engine bypass: bypass the entire signal chain
- Jack server connection: connect application to local Jack audio. You can either use Jack or ignore it in favor of another engine like Pipewire
- Jack ports: shows list of ports available to Guitarix
- Latency: Provides an ability to change latency amounts between input and audio playback
- Midi Controller: Lists all available Midi controllers

### **Presets**

- Preset selection: Toggles visibility of window that lets users select a preset signal chain
    - Preset banks
        - Scratchpad: Snapshots of unsaved/work in progress signal chains the user is building
        - Musiclab: Premade signal chains provided with the application
    - Save: Saves preset
    - Online: Opens resource with available presets for Guitarix (this currently appears broken)
    - Organize: Rename or delete user-created presets
    - New bank: Creates a new bank/folder for presets
- Next Preset: Cycles to the next preset
- Previous: Goes to the previous preset
- Next Preset Midi Switch: Cycle to the next preset when using a midi controller; user can adjust MIDI CC number to toggle the switch
- Previous Preset Midi Switch:  Goes to the previous preset when using a midi controller; user can adjust MIDI CC number to toggle the switch
- Organize: Toggles the organize preset window
- Bank: Musiclab: List all available presets within Guitarix

### **Plugins**

- Show Plugin Bar: Toggles list of available plugins on the left-hand side of Guitarix
- Rack Configuration: Toggles simplified overview of amp and signal chain; user can add/remove component from this view
- Show Rack: Toggles list of available plugins on the left-hand side of Guitarix
- Order Rack Horizontally:  Toggle a rack split into two columns visually but not affecting the signal chain in any way
- Show Tuner: Toggles the Tuner module before the amplifier module
- Tuner Stick: Moves to the Tuner to the top before the signal chain
- Tuner Midi Out: *(Needs clarification)*
- Mono Plugins: List all available mono Guitarix plugins; user can select to add
- Stereo Plugins: List all available stereo Guitarix plugins; user can select to add
- LADSPA/LV2 Plugins: Allows user to use external LADSPA/LV2 plugins within their signal chain
- Compress All: Collapses all modules in the signal chain visually except for the preamplifier module
- Expand All: Expands all modules in the signal chain visually

### **Tube**

- Lists all available preamplifier models; user can select a model to use as a base for their amplifier

### **Options**

- Live Display: Toggles full screen of preset name and background; user can adjust the brightness at the top right with corresponding slider
- Show Logging Box: Toggles a logging output terminal for debugging
- Meter Bridge: Toggles window showing various audio meters using the Jack audio server
- Skin…: Lists all available colour/texture options for modules in the rack; select and it will change all modules in the signal change to that colour/texture
- Jack Startup Control: Option to choose a program to start Jack if not running
- Include Midi In Preset: (*Needs clarification)*
- Reset All Parameters: Resets all parameters for everything in the signal chain
- Use Animations: Toggles animations for UI elements
- Liveplay Midi Switch: (Needs clarification)
- Bypass Midi Switch: Toggle to bypass MIDI switch; user can enter MIDI CC which performs the action
- Set Midi Channel: Toggle to set exclusive MIDI channel that lets a controller communicate with Guitarix
- Set Midi Feedback: Toggle to let Guitarix send MIDI information back to a MIDI controller
- Osc. Buffer Size: Lists available buffer sizes that a use can select for an oscillator (needs clarification)

### **About**

- About: Shows general information about Guitarix
- Help: Opens community Reddit forum to ask for help
- Get NAM Models: Opens the Tone3000 web page
- Get RTNeural Models: Opens the Tone3000 web page with RTNeural as search term
- Show Tooltips: Toggles tooltips for UI

### Pool

Toggles list of available plugins on the left-hand side of Guitarix

### Order

Toggles simplified overview of amp and signal chain; user can add/remove component from this view; hides preset window if opened

### Tuner

Toggles the Tuner module before the amplifier module

### Rack

Toggle the visibility of the add modules in the signal chain and hides the Split and Fold options; the preamplifier and tuner remain on screen

### Split

Toggle a rack split into two columns visually but not affecting the signal chain in any way

### Fold/Show

Collapses and expands all modules in the signal chain visually

### Live

Full screen live visuals that can be used for live performances

## Main view

### Plugin bar

**Tone control**

This section contains various modules that can change the tone of the signal chain such as EQ, Cabinet, and various filters.

**Neural**

Modules to load NAM (Neural Amp modeler) and RTNeural files

**Distortion**

Various kinds of distortion modules including well-known options such as Tube Screamer and Rat

**Fuzz**

Various fuzz modules including Fuzz Face and Ruiners

**Reverb**

Various reverb modules such as a convolution, plate and stereo reverb

**Echo/Delay**

Various delay and echo modules such as a multi-band delay (MB Delay)

**Modulation**

Various modulation modules such as phaser, flanger and chorus

**Guitar Effects**

Various modules for compression/expansion, wah pedals, and glitch-like sounds

**Misc**

Various extra useful modules such as a live looper, recorder, even a drum sequencer

**External**

List of external plugins imported into Guitarix using LADSPA/LV2 plugins feature

### Signal chain

Shows all the modules within the current signal chain

- Modules can be ordered by drag and drop
- Modules can be bypassed on the top-left via the power button
- Top right contains a button to save presets for the particular module and a show/hide toggle
- Drag or use the mouse wheel to move UI knobs to change values. Right-click the knob to finely increment the values
- Some UI such as the NAM module will let a user load a file. A window will appear and file can be selected. Drag and drop of files is not currently supported

## Bottom bar

### Preset button

Toggles the preset window

### Preset name

Shows the name of the currently selected preset

### Bypass Jack insert ports

A toggle resembling a male-to-female electrical plug that bypasses Jack audio server. Green is used, yellow is bypassed. Use the middle mouse button to connect a MIDI controller

### Engine Status

Toggle to mute the entire audio engine inside of Guitarix

### Jack Connection Status

A toggle resembling a male-to-female electrical plug that opens a window to connect Guitarix to Jack audio server. Green is connected, red is unconnected

### Status of Events

Logs out application events and whether there are issues within the application. Grey note icon represents OK, yellow warning icon represents a warning, and a red X icon is an error