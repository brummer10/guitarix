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
	    }
	});
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
	this.$.name.setContent(e.name);
	this.$.state.changeValue(e.on_off);
	if (e.id == "ampstack") {
	    this.$.state.setDisabled(true);
	    this.$.del.setDisabled(true);
	}
    },
    rendered: function() {
	this.inherited(arguments);
	this.resized(); // onyx.ToggleButton seems to resize after rendered()
    },
    stateChanged: function(inSender, inEvent) {
	guitarix.notify("set", [this.fx.id+".on_off", inEvent.value ? 1 : 0]);
    },
    deleteModule: function(inSender, inEvent) {
	guitarix.notify("set", [this.fx.id+".on_off", 0]);
	guitarix.notify("set", ["ui."+this.fx.id, 0]);
	this.fx.on_off = 0;
	this.fx.box_visible = 0;
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
    loadEffects: function() {
	guitarix.call(
	    "get", [this.sys_loadvar],
	    this, function(result) {
		this.effects = {}
		this.destroyClientControls();
		var l = result[this.sys_loadvar];
		for (var i=0; i < l.length; i++) {
		    e = l[i];
		    if (e.category) {
			if (!(e.category in this.effects)) {
			    this.effects[e.category] = [];
			}
			this.effects[e.category].push(e);
		    }
		    if (e.on_off || e.box_visible) {
			this.createComponent({kind: "gx.EffectBox",	fx: e});
		    }
		}
		this.render();
	    });
    },
    insertEffect: function(fx) {
	var c;
	var fxId = fx.id;
	var param = ["ui."+fxId, 1, fxId+".position", 0, fxId+".on_off", 1];
	if (!this.stereo) {
	    param.push(fxId+".pp");
	    param.push("pre");
	}
	c = this.getClientControls();
	for (var i = 0; i < c.length; i++) {
	    var e = c[i].fx;
	    if (e === undefined || e.id == "ampstack") {
		continue;
	    }
	    if (this.stereo || e.post_pre == 1) {
		param.push(e.id+".position");
		param.push(e.position+1);
	    }
	}
	guitarix.notify("set", param);
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
	var param = [];
	var before = true;
	var pp = "pre";
	var pos = 0;
	function send_param(id) {
	    if (id == "ampstack") {
		pp = "post";
		pos = 0;
	    } else {
		param.push(id+".position");
		param.push(pos);
		param.push(id+".pp");
		param.push(pp);
	    }
	    pos += 1;
	}
	for (var i = 0; i < c.length; i++) {
	    var e = c[i].fx;
	    if (e === undefined) {
		continue;
	    }
	    if (e.id == this.start_move) {
		before = false;
		continue;
	    }
	    if (before && e.id == inEvent.fxId) {
		send_param(this.start_move);
	    }
	    send_param(e.id);
	    if (!before && e.id == inEvent.fxId) {
		send_param(this.start_move);
	    }
	}
	this.start_move = "";
	guitarix.notify("set", param);
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
