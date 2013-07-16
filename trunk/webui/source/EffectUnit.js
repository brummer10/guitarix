enyo.kind({
    name: "gx.ValueDisplay",
    tag: "span",
    classes: "gx-valuedisplay",
    setStep: function(v) {
	if (v < 1) {
	    var l = String(v).length - 2; // "0.xx"
	} else {
	    l = 0;
	}
	this.digits = l;
    },
    setValue: function(v) {
	this.setContent(v.toFixed(this.digits));
    },
});

enyo.kind({
    name: "gx.SimpleSlider",
    kind: "onyx.Slider",
    lockBar: true,
    tappable: true,
    classes: "gx-simpleslider",
    obj: null,
    setRange: function(obj) {
	this.setMin(obj.lower_bound);
	this.setMax(obj.upper_bound);
	this.setValue(obj.value[obj.id]);
	this.obj = obj;
    },
});

enyo.kind({
    name: "gx.ValueSlider",
    classes: "gx-valueslider",
    published: {
	value: null,
	obj: null,
	varname: null,
    },
    components: [
	{components:[
	    {kind: "gx.ValueDisplay", name: "display" },
	    {name: "label", tag:"span"},
	]},
	{name: "slider", kind: "gx.SimpleSlider", onChanging: "doChanging", onChange: "doChanging"},
    ],
    create: function() {
	this.inherited(arguments);
	this.varnameChanged();
	this.objChanged();
    },
    varnameChanged: function() {
	this.$.label.setContent(this.varname);
    },
    objChanged: function() {
	if (this.obj === null) {
	    return;
	}
	this.$.slider.setRange(this.obj);
	var c = this.$.display;
	c.setStep(this.obj.step);
	c.setValue(this.obj.value[this.obj.id]);
    },
    doChanging: function(inSender, inEvent) {
	this.$.display.setValue(inEvent.value);
    },
    valueChanged: function(old, val) {
	this.$.display.setValue(val);
	this.$.slider.setValue(val);
    },
});

enyo.kind({
    name: "gx.EffectControls",
    kind: "enyo.Scroller",
    classes: "gx-effect",
    published:{
	fxId: null,
    },
    events: {
	onParameterChanged: "",
    },
    handlers: {
	onChanging: "valueChanged",
	onChange:   "valueChanged",
    },
    control_setter: null,
    fxIdChanged: function() {
	this.destroyClientControls();
	if (!this.fxId) {
	    return;
	}
	if (this.fxId instanceof Array) {
	    guitarix.call(
		"get_parameter", this.fxId,
		this, function(result) {
		    var builderlist = [];
		    builderlist.push(["create_switch", null, this.fxId[0], null]);
		    for (var i = 1; i < this.fxId.length; i++) {
			builderlist.push(["create_small_rackknob", this.fxId[i], null]);
		    }
		    var b = new UiBuilder();
		    this.control_setter = {};
		    b.build(builderlist, result, this, this.control_setter);
		    this.render();
		});
	} else {
	    guitarix.call(
		"plugin_load_ui", [this.fxId, 1],
		this, function(result) {
		    this.uidesc = result;
		    guitarix.call(
			"queryunit", [this.fxId],
			this, function(result) {
			    var o, id;
			    var builderlist = [];
			    if (this.fxId != "ampstack") {
				id = this.fxId+".on_off"
				if (id in result) {
				    builderlist.push(["create_switch", null, id, "On/Off"]);
				}
			    }
			    if (this.uidesc === null) {
				var m = this.fxId+"\\.(position|s_h|on_off|pp)$";
				for (id in result) {
				    if (id.match(m)) {
					continue;
				    }
				    o = result[id];
				    if (o.ctl_switch) {
					builderlist.push(["create_switch", null, id, null]);
				    } else if (o.ctl_enum) {
					builderlist.push(["create_selector", id, null]);
				    } else {
					builderlist.push(["create_small_rackknob", id, null]);
				    }
				}
			    } else {
				builderlist = builderlist.concat(this.uidesc);
			    }
			    var b = new UiBuilder();
			    this.control_setter = {};
			    b.build(builderlist, result, this, this.control_setter);
			    this.render();
			});
		});
	}
    },
    valueChanged: function(inSender, inEvent) {
	var o = inEvent.originator.obj;
	var v;
	if (o.ctl_switch) {
	    v = (inEvent.value ? 1 : 0);
	} else if (o.ctl_enum) {
	    v = inEvent.selected.key;
	} else {
	    v = inEvent.value;
	}
	guitarix.notify("set", [o.id, v]);
	if (o.id.match(/.*\.on_off$/)) { // signaling up only needed for effect on/off atm.
	    this.doParameterChanged({id: o.id, value: v});
	}
    },
    setParameter: function(param_id, value) {
	if (this.control_setter === null) {
	    return;
	}
	var setter = this.control_setter[param_id];
	if (setter !== undefined) {
	    setter(value);
	}
    }
});

enyo.kind({
    name: "gx.EffectUnit",
    layoutKind: "FittableRowsLayout",
    events:{
	onEffects: "",
    },
    components:[
	{name: "controls", kind: "gx.EffectControls", fit: true},
	{kind: "onyx.Toolbar", components:[
	    {kind: "onyx.Button", content: "List", ontap: "doEffects"},
	]},
    ],
    setFxId: function(id) {
	this.$.controls.setFxId(id);
    },
    setParameter: function(param_id, value) {
	this.$.controls.setParameter(param_id, value);
    },
});
