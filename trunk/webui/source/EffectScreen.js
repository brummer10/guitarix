enyo.kind({
    name: "gx.EffectSection",
    events: {
	onAdd: "",
    },
    components: [
	{name: "head", classes: ["onyx-menu"], ontap: "toggle"},
	{name: "drawer", kind: "onyx.Drawer", open: false}
    ],
    toggle: function(inSender, inEvent) {
	this.$.drawer.setOpen(!this.$.drawer.open);
    },
    initComponents: function() {
	this.kindComponents[0].content = this.category;
	var ul = [];
	for (var i = 0; i < this.efflist.length; i++) {
	    ul.push({
		kind: "onyx.Button",
		classes: ["onyx-menu-item"],
		tag: "div",
		content: this.efflist[i].name,
		ontap: "doAdd",
		fx: this.efflist[i],
	    });
	}
	this.kindComponents[1].components = ul;
	this.inherited(arguments);
    },
});

enyo.kind({
    name: "gx.SaveSettingsButton",
    kind: "onyx.Button",
    style: "display: block",
    events: {
	onSaveSettings: "",
    },
    handlers:{
	ontap: "doSaveSettings",
    },
});

enyo.kind({
    name: "gx.BankPresetPopup",
    classes: "onyx-sample-popup",
    kind: "onyx.Popup",
    centered: true,
    modal: true,
    floating: true,
    showDialog: function(bank) {
	this.show();
	if (bank) {
	    this.$.bank.setValue(bank);
	    this.$.bank.setDisabled(true);
	    this.$.preset.focus();
	} else {
	    this.$.bank.focus();
	}
    },
    components: [
	{tag: "table", components:[
	    {tag: "tr", components:[
		{tag: "th", content: "Bank"},
		{tag: "td", components:[{kind: "onyx.InputDecorator", components: [{
		    name: "bank",
		    kind: "onyx.Input",
		    onkeydown: "bankKeyDown",
		}]}]},
	    ]},
	    {tag: "tr", components:[
		{tag: "th", content: "Preset"},
		{tag: "td", components:[{kind: "onyx.InputDecorator", components: [{
		    name: "preset",
		    kind: "onyx.Input",
		    onkeydown: "presetKeyDown",
		}]}]},
	    ]},
	]},
	//
	//]},
	{tag: "br"},
	{kind: "onyx.Button", content: "Cancel", ontap: "hide"},
	{kind: "onyx.Button", content: "Save", ontap: "save"}
    ],
    bankKeyDown: function(inSender, inEvent) {
	if (inEvent.keyCode === 13) {
	    this.$.preset.focus();
	    return true;
	}
    },
    presetKeyDown: function(inSender, inEvent) {
	if (inEvent.keyCode === 13) {
	    this.save();
	    return true;
	}
    },
    save: function() {
	guitarix.notify("save_preset",
			[this.$.bank.getValue(), this.$.preset.getValue()]);
	this.hide();
    },
});

enyo.kind({
    name: "gx.EffectScreen",
    layoutKind: "FittableRowsLayout",
    events:{
	onMain: "",
    },
    handlers: {
	onAdd: "addUnit",
	onSaveSettings: "saveSettings",
    },
    current_preset: null,
    loaded_preset: null,
    components:[
	{name: "slider", kind: "gx.SlidingPanel", components: [
	    {name: "slider_content", kind: "enyo.Scroller", classes: "enyo-fit",
	     horizontal: "hidden"},
	]},
	{kind: "enyo.Scroller", horizontal: "hidden", fit: true, components:[
	    {name: "fixed", kind: "gx.fixedEffects"},
	    {layoutKind: "FittableColumnsLayout", components:[
		{content: "Mono", tag: "h4", style:"text-align:center; margin-top:10px; margin-bottom:2px", fit:true},
		{kind: "onyx.Button", content: "Add", ontap: "addMonoEffect"},
	    ]},
	    {name: "mono_rack", kind: "gx.EffectRack", sys_loadvar: "sys.visible_mono_plugins"},
	    {layoutKind: "FittableColumnsLayout", components:[
		{content: "Stereo", tag: "h4", style:"text-align:center; margin-top:10px; margin-bottom:2px", fit:true},
		{kind: "onyx.Button", content: "Add", ontap: "addStereoEffect"},
	    ]},
	    {name: "stereo_rack", kind: "gx.EffectRack", sys_loadvar: "sys.visible_stereo_plugins", stereo: true},
	]},
	{kind: "onyx.Toolbar", components:[
	    {kind: "onyx.Button", content: "Main", ontap: "toMain"},
	    {kind: "onyx.Button", content: "Save", name: "save_button", ontap: "save"},
	    {kind: "onyx.Button", content: "Save As", ontap: "save_as"},
	]},
    ],
    setCurrentPreset: function(p) {
	this.current_preset = p;
    },
    toMain: function(inSender, inEvent) {
	this.doMain(inEvent);
	return true;
    },
    save: function(inSender, inEvent) {
	guitarix.notify("save_current",[]);
    },
    save_as: function(inSender, inEvent) {
	guitarix.call(
	    "banks", [],
	    this, function(result) {
		var l = this.$.slider_content;
		this.$.slider.bank = "";
		l.destroyClientControls();
		l.createComponent({
		    tag: "h3",
		    content: "Select Bank for Saving",
		});
		for (c in result) {
		    var f = result[c];
		    if (f.mutable) {
			l.createComponent({
			    kind: "gx.SaveSettingsButton",
			    content: f.name,
			});
		    }
		}
		l.createComponent({
		    kind: "gx.SaveSettingsButton",
		    content: "- new -",
		});
		l.createComponent({
		    name: "newbank",
		    kind: "gx.BankPresetPopup",
		});
		l.render();
		var p = this.$.slider;
		if (p.getValue() < 0) {
		    p.setShowing(true);
		}
		p.animateToMax();
	    });
    },
    saveSettings: function(inSender, inEvent) {
	if (inEvent.content == "- new -") {
	    this.$.slider_content.$.newbank.showDialog(this.$.slider.bank);
	} else if (this.$.slider.bank) {
	    guitarix.notify("save_preset",
			    [this.$.slider.bank, inEvent.content]);
	} else {
	    this.$.slider.bank = inEvent.content;
	    guitarix.call(
		"presets", [inEvent.content],
		this, function(result) {
		    var l = this.$.slider_content;
		    l.destroyClientControls();
		    l.createComponent({
			tag: "h3",
			content: "Bank "+inEvent.content+": Select Preset for Saving",
		    });
		    for (c in result) {
			var f = result[c];
			l.createComponent({
			    kind: "gx.SaveSettingsButton",
			    content: f,
			});
		    }
		    l.createComponent({
			kind: "gx.SaveSettingsButton",
			content: "- new -",
		    });
		    l.createComponent({
			name: "newbank",
			kind: "gx.BankPresetPopup",
		    });
		    l.render();
		    var p = this.$.slider;
		    if (p.getValue() < 0) {
			p.setShowing(true);
		    }
		    p.animateToMax();
		});
	}
	this.$.slider.animateToMin();
    },
    addMonoEffect: function(inSender, inEvent) {
	this.addEffect(this.$.mono_rack);
    },
    addStereoEffect: function(inSender, inEvent) {
	this.addEffect(this.$.stereo_rack);
    },
    addEffect: function(rack) {
	var l = this.$.slider_content;
	var eff = rack.effects;
	l.destroyClientControls();
	l.createComponent({
	    tag: "h3",
	    content: (rack === this.$.stereo_rack ? "Stereo Effects" : "Mono Effects"),
	});
	for (c in eff) {
	    var f = eff[c];
	    var v = [];
	    for (var i = 0; i < f.length; i++) {
		var e = f[i];
		if (!(e.on_off || e.box_visible)) {
		    v.push(e);
		}
	    }
	    if (v.length) {
		l.createComponent({
		    kind: "gx.EffectSection",
		    category: c,
		    efflist: v,
		});
	    }
	}
	l.render();
	var p = this.$.slider;
	p.current_rack = rack
	if (p.getValue() < 0) {
	    p.setShowing(true);
	}
	p.toggleMinMax();
    },
    addUnit: function(inSender, inEvent) {
	var s = this.$.slider;
	s.current_rack.insertEffect(inEvent.fx);
	s.animateToMin();
    },
    preparePanel: function() {
	if (!this.current_preset) {
	    return;
	}
	this.loaded_preset = this.current_preset;
	guitarix.call(
	    "get_bank", [this.current_preset[0]],
	    this, function(result) {
		this.$.save_button.setDisabled(!result.mutable);
	    });
	this.$.mono_rack.loadEffects(this.current_preset);
	this.$.stereo_rack.loadEffects(this.current_preset);
    },
});
