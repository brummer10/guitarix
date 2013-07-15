enyo.kind({
    name: "gx.MainScreen",
    layoutKind: "FittableRowsLayout",
    events:{
	onTunerOn: "",
	onEffects: "",
	onSwitch: "",
    },
    components:[
	{fit: true, components:[
	    {name: "bank", kind: "gx.SelectButton", onPrepareList: "showBankList", onSelect: "selectBank"},
	    {name: "preset", kind: "gx.SelectButton", onPrepareList: "showPresetList", onSelect: "selectPreset"},
	    {name: "message", ontap: "messageTap", style: "visibility: hidden; text-align:center", content: "X"},
	    {name: "maxlevel", kind: "gx.LevelDisplay"},
	    {name: "outmaster", kind: "gx.SimpleSlider",
	     onChange: "outmasterChanged", onChanging: "outmasterChanged"},
	]},
	{kind: "onyx.MoreToolbar", layoutKind: "FittableColumnsLayout", components:[
	    {kind: "onyx.Button", content: "Tuner On", ontap: "TunerOn"},
	    {kind: "onyx.Button", content: "Switch", ontap: "Switch"},
	    {name: "status", kind: "gx.StatusDisplay"},
	    {name: "load", kind: "gx.LoadDisplay"},
	    {name: "fullscreen", kind: "onyx.Button", content: "FS", ontap: "toggleFullscreen"},
	    {fit: true},
	    {kind: "onyx.Button", content: "Effects", unmoveable: true, ontap: "EffectsOn"},
	]},
    ],
    rendered: function() {
	if (!this.isFullscreenAvailable()) {
	    this.$.fullscreen.hide();
	}
	this.inherited(arguments);
	guitarix.call("get_parameter", ["amp.out_master"], this, function(result) {
	    var o = result["amp.out_master"];
	    o.id = "amp.out_master";
	    this.$.outmaster.setRange(o);
	});
    },
    setStatus: function(stat) {
	this.$.status.setStatus(stat);
    },
    TunerOn: function(inSender, inEvent) {
	this.doTunerOn(inEvent);
	return true;
    },
    EffectsOn: function(inSender, inEvent) {
	this.doEffects(inEvent);
	return true;
    },
    Switch: function(inSender, inEvent) {
        guitarix.notify('tuner_switcher_toggle',[false]);
	return true;
    },
    showMessage: function(message) {
	var w = this.$.message;
	w.setContent(message);
	this.$.message.applyStyle("visibility","visible");
    },
    messageTap: function(inSender, inEvent) {
	this.$.message.applyStyle("visibility","hidden");
    },	
    selectBank: function(inSender, inEvent) {
	inEvent.activator = this.$.preset;
	this.$.preset.requestShowMenu(inSender, inEvent);
    },
    selectPreset: function(inSender, inEvent) {
	guitarix.notify("setpreset", [this.$.preset.bank, inEvent.content]);
    },
    showBankList: function() {
	guitarix.call(
	    'banks', [],
	    this.$.bank, function(result) {
		var l = this.$.list;
		l.destroyClientControls();
		for (var i = 0; i < result.length; ++i) {
		    l.createComponent({kind:"onyx.MenuItem",content:result[i].name});
		}
		l.render();
	    });
    },
    displayPresetList: function(bank) {
	guitarix.call(
	    'presets', [bank],
	    this.$.preset, function(result) {
		var l = this.$.list;
		l.destroyClientControls();
		for (var i = 0; i < result.length; ++i) {
		    l.createComponent({kind:"onyx.MenuItem",content:result[i]});
		}
		l.render();
		this.bank = bank;
	    });
    },
    showPresetList: function(inSender, inEvent) {
	if (inEvent && inEvent.content) {
	    bank = inEvent.content;
	} else {
	    bank = this.$.bank.getTitle();
	}
	this.displayPresetList(bank);
    },
    display_preset: function(bank, preset) {
	this.$.bank.setTitle(bank);
	this.$.preset.setTitle(preset);
    },
    display_state: function(statename) {
	if (statename == "normal_mode") {
 	    guitarix.call(
		'get',["system.current_bank","system.current_preset"],
		this, function(result) {
		    this.display_preset(result["system.current_bank"], result["system.current_preset"]);
		});
	}
	this.$.bank.display_state(statename);
	this.$.preset.display_state(statename);
    },
    setRepeat: function(v) {this.$.load.setRepeat(v);},
    getRepeat: function() {return this.$.load.getRepeat();},
    isFullscreenAvailable: function () {
	var elem = document.documentElement;
	return elem.requestFullscreen ||   // W3C incl. Opera
	elem.webkitRequestFullScreen && ! window.externalHost ||   // not Google Chrome Frame
	elem.mozRequestFullScreen && ! /Android/.test(window.navigator.userAgent);   // not working in FF17 on TouchPad
    },
    outmasterChanged: function(inSender, inEvent) {
	guitarix.notify("set", ["amp.out_master", inEvent.value]);
    },
    setParameter: function(param_id, value) {
	if (param_id == "amp.out_master") {
	    this.$.outmaster.setValue(value);
	}
    },
    toggleFullscreen: function() {
	var elem = document.documentElement;
	if (elem.requestFullscreen) {
	    this.log("using W3C Fullscreen API");
	    if (document.fullscreenElement) {
		document.exitFullscreen();
	    } else {
		elem.requestFullscreen();
	    }
	} else if (elem.webkitRequestFullScreen) {
	    this.log("using WebKit FullScreen  API");
	    if (document.webkitIsFullScreen) {
		document.webkitCancelFullScreen();
	    } else {
		elem.webkitRequestFullScreen();
	    }
	} else if (elem.mozRequestFullScreen) {
	    this.log("using Mozilla FullScreen  API");
	    if (document.fullscreenElement || document.webkitIsFullScreen || document.mozFullScreenElement) {
		document.mozCancelFullScreen();
	    } else {
		elem.mozRequestFullScreen();
	    }
	} else {
	    this.log("no fullscreen API");
	}
    },
});

enyo.kind({
    name: "gx.CenteredMenu",
    kind: "onyx.Menu",
    centered: true,
    floating: true,
    showOnTop: true,
    create: function() {
	//this.childComponents[0].touchOverscroll = false;
	this.childComponents[0].strategyKind = "ScrollStrategy";
	this.inherited(arguments);
    },
    adjustPosition: function() {
	this.setMaxHeight(document.body.offsetHeight-30);
	this.inherited(arguments);
    },
});


enyo.kind({

    name: "gx.SelectButton",

    kind: "onyx.MenuDecorator",

    events:{
	onPrepareList: "",
    },

    published:{
	title: "",
    },

    requestShowMenu: function(inSender, inEvent) {
	this.activator = this.$.title;
	this.doPrepareList(inEvent);
	this.inherited(arguments);
    },

    titleChanged: function(old) {
	this.$.title.setContent(this.title);
    },

    components: [
	{name: "title", classes:"preset"},
	{name: "list", kind: "gx.CenteredMenu"}
    ],

    _state_dict: {"wait_start": "yellow", "listening": "red", "wait_stop": "green", "normal_mode": null},

    display_state: function(statename) {
	this.$.title.applyStyle("color", this._state_dict[statename]);
    },
});

enyo.kind({
    name: "gx.LoadDisplay",
    tag: "span",
    style: "width: 3em; text-align: right",
    published: {
	repeat: 5100,
    },
    timeout_handle: null,
    start: function() {
	if (this.timeout_handle) {
	    clearTimeout(this.timeout_handle);
	}
	this.display_load();
    },
    display_load: function() {
	this.timeout_handle = null;
	guitarix.call(
	    'jack_cpu_load',[],
	    this, function(result) {
		this.setContent(result.toFixed(1));
		if (!this.timeout_handle) {
		    this.timeout_handle = setTimeout(
			enyo.bind(this, this.display_load), this.repeat);
		}
	    }
	);
    },
});

enyo.kind({
    name: "gx.Level",
    tag: "canvas",
    published: {
	value: 0,
    },
    valueChanged: function() {
	this.value = Math.max(0, Math.min(this.value, 1));
	this.updateBarPosition(this.value);
    },
    rendered: function() {
	this.inherited(arguments);
	var node = this.hasNode();
	this.width = node.width;
	this.height = node.height;
	this.ctx = node.getContext('2d');
	this.pat = this.ctx.createLinearGradient(0, 0, node.width, 0);
	this.pat.addColorStop(0, rgb(222/255.0,222/255.0,13/255.0));
	this.pat.addColorStop(1, rgb(1.0,0,51/255.0));
    },
    updateBarPosition: function(v) {
	if (this.ctx === undefined) {
	    return;
	}
	var f = this.width * v;
	this.ctx.fillStyle = this.pat;
	this.ctx.fillRect(0, 0, f, this.height);
	this.ctx.fillStyle = rgb(0,0,0);
	this.ctx.fillRect(f, 0, this.width, this.height);
    },
});

enyo.kind({
    name: "gx.LevelDisplay",
    layoutKind: "FittableColumnsLayout",
    classes: "gx-maxlevel",
    led_hold_count: 10,
    led_left: 0,
    timeout_handle: null,
    published: {
	repeat: 100,
	overload: false,
    },
    components:[
	{name: "bar", kind: "gx.Level", fit: true, showStripes: false },
	{name: "led", classes: "led"},
    ],
    overloadChanged: function(old) {
	this.$.led.addRemoveClass("led-on", this.overload);
    },
    start: function() {
	if (this.timeout_handle) {
	    clearTimeout(this.timeout_handle);
	}
	this.display_level();
    },
    display_level: function() {
	this.timeout_handle = null;
	guitarix.call(
	    'get_max_output_level',[2],
	    this, function(result) {
		var v = result[0] > result[1] ? result[0] : result[1];
		v = 1+Math.log(Math.max(v, 0.001))/(3*Math.log(10)); // -60dB..0dB -> 0..1
		if (v >= 1) {
		    this.led_left = this.led_hold_count;
		    this.setOverload(true);
		} else if (this.led_left) {
		    if (--this.led_left == 0) {
			this.setOverload(false);
		    }
		}
		this.$.bar.setValue(v);
		if (!this.timeout_handle) {
		    this.timeout_handle = setTimeout(
			enyo.bind(this, this.display_level), this.repeat);
		}
	    }
	);
    },
});

enyo.kind({
    name: "gx.StatusButton",
    kind: "onyx.Button",
    showing: false,
    published: {
	src: "",
    },
    components: [{kind: "enyo.Image", style: "width: 75px"}],
    create: function() {
	this.inherited(arguments);
	this.srcChanged();
    },
    srcChanged: function() {
	this.getControls()[0].setSrc(this.src);
    },
});

enyo.kind({
    name: "gx.StatusDisplay",
    published: {
	status: "stopped",
	runstate: "running",
    },
    defaultKind: "gx.StatusButton",
    handlers: {
	ontap: "tapped",
    },
    components: [
	{name: "stopped", src: "assets/mute.svg"},
	{name: "bypassed", src: "assets/bypass.svg"},
	{name: "running", src: "assets/on.svg"},
    ],
    create: function() {
	this.inherited(arguments);
	this.statusChanged();
    },
    statusChanged: function(old) {
	if (old) {
	    this.$[old].hide();
	}
	this.$[this.status].show();
    },
    tapped: function(inSender, inEvent) {
	var newstate = this.runstate;
	switch (inSender.name) {
	case "running":
	    newstate = "stopped";
	    break;
	case "bypassed":
	    if (newstate == "bypassed") {
		newstate = "stopped";
	    }
	    break;
	}
	guitarix.notify("setstate", [newstate]);
    },
});
