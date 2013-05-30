enyo.kind({
    name: "gx.MainScreen",
    layoutKind: "FittableRowsLayout",
    events:{
	onTunerOn: "",
	onEffects: "",
	onSwitch: "",
    },
    components:[
	{classes: "test", fit: true, components:[
	    {name: "bank", kind: "gx.SelectButton", onPrepareList: "showBankList", onSelect: "selectBank"},
	    {name: "preset", kind: "gx.SelectButton", onPrepareList: "showPresetList", onSelect: "selectPreset"},
	    {name: "message", ontap: "messageTap", style: "visibility: hidden; text-align:center", content: "X"},
	]},
	{kind: "onyx.Toolbar", layoutKind: "FittableColumnsLayout", components:[
	    {kind: "onyx.Button", content: "Tuner On", ontap: "TunerOn"},
	    {fit: true, style:"display:inline-table; width:100%", components: [
		{style: "display: table-cell; text-align: center", components:[
		    {kind: "onyx.Button", style: "display:inline", content: "Switch", ontap: "Switch"},
		    {name: "status", style: "display:inline", kind: "gx.StatusDisplay"},
		    {name: "load", style: "display:inline", kind: "gx.LoadDisplay"},
		]},
	    ]},
	    {kind: "onyx.Button", content: "Effects", ontap: "EffectsOn"}
	]},
    ],

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
        guitarix.notify('switch',[]);
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
    getRepeat: function() {return this.$.load.getRepeat();}
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
    rendered: function() {
	this.inherited(arguments);
	this.display_load();
    },
    display_load: function() {
	guitarix.call(
	    'jack_cpu_load',[],
	    this, function(result) {
		this.setContent(result.toFixed(1));
		setTimeout(enyo.bind(this, this.display_load), this.repeat);
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
