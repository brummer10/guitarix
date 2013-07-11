enyo.kind({
    name: "gx.ToggleButton",
    //kind: "onyx.custom.AnimatedToggleButton",
    kind: "onyx.ToggleButton",
    changeValue: function(newval) {
	if (newval != this.value) {
	    this.value = newval;
	    this.updateVisualState();
	}
    },
});

enyo.kind({
    name: "gx.SimpleEffectBox",
    style: "margin-bottom: 20px",
    components: [
	{components:[
	    {name: "on_off", kind: "gx.ToggleButton", onChange: "effSwitched"},
	    {name: "head", style: "vertical-align: 0%; margin-left: 20px"},
	]},
	{name: "slider", kind: "onyx.Slider", lockBar: true, tappable: true,
	 onChange: "effValue", onChanging: "effValue" },
    ],
    create: function() {
	this.inherited(arguments);
	this.$.head.setContent(this.head);
    },
    setValues: function(d) {
	if (this.eff_on_off === undefined) {
	    this.$.on_off.hide();
	} else {
	    this.$.on_off.changeValue(d[this.eff_on_off].value[this.eff_on_off]);
	}
	var s = this.$.slider;
	var o = d[this.eff_value];
	s.setMin(o.lower_bound);
	s.setMax(o.upper_bound);
	s.setValue(o.value[this.eff_value]);
    },
    addSetter: function(d) {
	var el;
	if (this.eff_on_off !== undefined) {
	    el = this.$.on_off;
	    d[this.eff_on_off] = enyo.bind(el, el.changeValue);
	}
	el = this.$.slider;
	d[this.eff_value] = enyo.bind(el, el.setValue);
    },
    effSwitched: function(inSender, inEvent) {
	guitarix.notify("set", [this.eff_on_off, (inEvent.value ? 1 : 0)]);
    },
    effValue: function(inSender, inEvent) {
	guitarix.notify("set", [this.eff_value, inEvent.value]);
    },
});

enyo.kind({
    name: "gx.fixedEffects",
    components:[
	{content: "Fixed Effects", tag: "h4", ontap: "activateDrawer",
	 style:"text-align:center; margin-top:10px; margin-bottom:2px"},
	{name: "drawer", kind: "onyx.Drawer", open: false, components:[
	    {name: "out_master", kind: "gx.SimpleEffectBox", head: "Master Volume", eff_value: "amp.out_master"},
	    {name: "noise_gate", kind: "gx.SimpleEffectBox", head: "noise gate", eff_on_off: "noise_gate.on_off", eff_value: "noise_gate.threshold"},
	    {name: "shaper", kind: "gx.SimpleEffectBox", head: "noise shaper", eff_on_off: "shaper.on_off", eff_value: "shaper.sharper"},
	    {name: "amp", kind: "gx.SimpleEffectBox", head: "mono level out", eff_on_off: "amp.on_off", eff_value: "amp.out_amp"},
	    {name: "clip", kind: "gx.SimpleEffectBox", head: "clip", eff_on_off: "amp.clip.on_off", eff_value: "amp.fuzz"},
	    {name: "bass_boost", kind: "gx.SimpleEffectBox", head: "Bass boost", eff_on_off: "amp.bass_boost.on_off", eff_value: "bassbooster.Level"},
	    {name: "con", kind: "gx.SimpleEffectBox", head: "Presence", eff_on_off: "con.on_off", eff_value: "con.Level"},
	    {name: "reverb", kind: "gx.SimpleEffectBox", head: "Reverb", eff_on_off: "amp.feed_on_off", eff_value: "amp.wet_dry"},
	]}
    ],
    control_setter: {},
    activateDrawer: function() {
        this.$.drawer.setOpen(!this.$.drawer.open);
    },
    rendered: function() {
	this.inherited(arguments);
	guitarix.call("get_parameter", [
	    "amp.out_master",
	    "noise_gate.on_off", "noise_gate.threshold",
	    "shaper.on_off", "shaper.sharper",
	    "amp.on_off", "amp.out_amp",
	    "amp.clip.on_off", "amp.fuzz",
	    "amp.bass_boost.on_off", "bassbooster.Level",
	    "con.on_off", "con.Level",
	    "amp.feed_on_off", "amp.wet_dry",
	], this, function(result) {
	    var c = this.$.drawer.getClientControls();
	    for (var i = 0; i < c.length; i++) {
		c[i].setValues(result);
		c[i].addSetter(this.control_setter);
	    }
	});
    },
    setParameter: function(param_id, value) {
	var setter = this.control_setter[param_id];
	if (setter !== undefined) {
	    setter(value);
	}
    },
});

enyo.kind({
    name: "gx.EffectBox",
    classes: "gx-effect-box",
    layoutKind: "FittableColumnsLayout",
    fx: null,
    events: {
	onEffectTapped: "",
	onEffectHold: "",
    },
    components:[
	{name: "state", kind: "gx.ToggleButton", onChange: "stateChanged"},
	{name: "before", kind: "onyx.Button", showing: false, content: "B", ontap: "insertBefore"},
	{name: "after", kind: "onyx.Button", showing: false, content: "A", ontap: "insertAfter"},
	{name: "name", kind: "onyx.Button", fit: true, ontap: "displayUnit", onhold: "startMove", onup: "checkMoveTap"},
	{name: "del", kind: "onyx.IconButton", style: "height: 32px", src: "assets/remove-icon.png", ontap: "deleteModule"},
    ],
    create: function() {
	this.inherited(arguments);
	this.$.name.setContent(this.fx.name);
	this.$.state.changeValue(this.fx.on_off);
	if (this.fx.id == "ampstack") {
	    this.$.state.applyStyle("visibility", "hidden");
	    this.$.del.applyStyle("visibility", "hidden");
	    this.addClass("gx-amp-box");
	}
    },
    setActive: function (v) {
	this.$.state.changeValue(v);
    },
    stateChanged: function(inSender, inEvent) {
	guitarix.notify("set", [this.fx.id+".on_off", inEvent.value ? 1 : 0]);
    },
    deleteModule: function(inSender, inEvent) {
	guitarix.notify("remove_rack_unit", [this.fx.id, (this.stereo ? 1 : 0)]);
	this.destroy();
    },
    displayUnit: function(inSender, inEvent) {
	inEvent.fxId = this.fx.id;
	this.doEffectTapped(inEvent);
    },
    startMove: function(inSender, inEvent) {
	this.start_move = true;
	inEvent.fxId = this.fx.id;
	this.doEffectHold(inEvent);
    },
    checkMoveTap: function(inSender, inEvent) {
	if (this.start_move) {
	    inEvent.preventTap();
	    this.start_move = false;
	}
    }
});

enyo.kind({
    name: "gx.EffectRack",
    handlers: {
	onEffectTapped: "checkTap",
	onEffectHold: "startMoveEffect",
    },
    sys_loadvar: null,
    stereo: false,
    effects: {},
    control_setter: {},
    loadEffects: function() {
	guitarix.call(
	    "get", [this.sys_loadvar],
	    this, function(result) {
		var nm, el;
		this.effects = {}
		this.destroyClientControls();
		var l = result[this.sys_loadvar];
		for (var i=0; i < l.length; i++) {
		    var e = l[i];
		    if (e.id == "oscilloscope") {
			continue;
		    }
		    if (e.category) {
			if (!(e.category in this.effects)) {
			    this.effects[e.category] = [];
			}
			this.effects[e.category].push(e);
		    }
		    if (e.on_off || e.box_visible) {
			nm = "eff_" + e.id;
			this.createComponent({kind: "gx.EffectBox", name: nm, fx: e});
			el = this.$[nm];
			this.control_setter[e.id+".on_off"] = enyo.bind(el, el.setActive);
		    }
		}
		this.render();
		this.parent.resized();
	    });
    },
    setParameter: function(param_id, value) {
	var setter = this.control_setter[param_id];
	if (setter !== undefined) {
	    setter(value);
	}
    },
    insertEffect: function(fx) {
	guitarix.notify("insert_rack_unit", [fx.id, "", (this.stereo ? 1 : 0)]);
	this.loadEffects();
    },
    checkTap: function(inSender, inEvent) {
	if (!this.start_move) {
	    return false;
	}
	if (this.start_move == inEvent.fxId) {
	    this.startMoveEffect(inSender, inEvent);
	    return true;
	}
	var c = this.getClientControls();
	var state = 0;
	var before_id = "";
	for (var i = 0; i < c.length; i++) {
	    var e = c[i].fx;
	    if (e === undefined) {
		continue;
	    }
	    if (state == 2) {
		before_id = e.id;
		break;
	    }
	    if (e.id == this.start_move) {
		state = 1;
		continue;
	    }
	    if (e.id == inEvent.fxId) {
		if (state == 0) {
		    before_id = e.id;
		    break;
		} else {
		    state = 2;
		}
	    }
	}
	guitarix.notify("insert_rack_unit",[this.start_move, before_id, (this.stereo ? 1 : 0)]);
	this.start_move = "";
	this.loadEffects();
	return true;
    },
    startMoveEffect: function(inSender, inEvent) {
	var id, s;
	var c = this.getClientControls();
	if (this.start_move) {
	    for (var i = 0; i < c.length; i++) {
		c[i].removeClass("gx-selected");
		c[i].removeClass("gx-before-selected");
		c[i].removeClass("gx-after-selected");
	    }
	    this.start_move = "";
	} else {
	    var id = inEvent.fxId;
	    var s = "gx-before-selected";
	    this.start_move = id;
	    for (var i = 0; i < c.length; i++) {
		var e = c[i].fx;
		if (e === undefined) {
		    continue;
		}
		if (e.id == id) {
		    c[i].addClass("gx-selected");
		    s = "gx-after-selected";
		} else {
		    c[i].addClass(s);
		}
	    }
	}
    },
});
