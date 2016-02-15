/*
 * Copyright (C) 2013 Andreas Degert
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
 */

var gxeq = 0;

enyo.kind({
    name: "gx.eqLevel",
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
	this.pat.addColorStop(0, rgb(102/255.0,222/255.0,13/255.0));
	this.pat.addColorStop(0.5, rgb(162/255.0,222/255.0,13/255.0));
	this.pat.addColorStop(0.8, rgb(222/255.0,222/255.0,13/255.0));
	this.pat.addColorStop(1, rgb(1.0,0,51/255.0));
    },
    updateBarPosition: function(v) {
	if (this.ctx === undefined) {
	    return;
	}
	var f = this.width * v;
	this.ctx.fillStyle = this.pat;
	this.ctx.fillRect(0, 0, f, this.height);
	this.ctx.fillStyle = rgb(0.1,0.1,0.1);
	this.ctx.fillRect(f, 0, this.width, this.height);
    },
});

enyo.kind({
    name: "gx.SimpleLevelDisplay",
    layoutKind: "FittableColumnsLayout",
    classes: "gx-level",
    published: {
	repeat: 100,
    },
    timeout_handle: null,
    components:[
	{name: "lbar", kind: "gx.eqLevel", fit: true, showStripes: false },
    ],
    //obj: null,
    create: function() {
	this.inherited(arguments);
	this.start();
	this.display_level();
	this.objChanged();
    },
    start: function() {
	if (this.timeout_handle) {
	    clearTimeout(this.timeout_handle);
	}
	this.display_level();
    },
    objChanged: function() {
	if (this.obj === null) {
	    return;
	}
	    this.start();
    },
    display_level: function() {
	if (typeof(this.$.lbar) == "undefined") {
	    return;
	}
	if (this.obj === null) {
	    return;
	}
	this.timeout_handle = null;
	guitarix.call(
	    'get_parameter_value', [this.obj.id],
	    this, function(result) {
		this.$.lbar.setValue(1+Math.log(Math.max(result[0], 0.001))/(3*Math.log(10)));
		if (!this.timeout_handle) {
		    this.timeout_handle = setTimeout(
			enyo.bind(this, this.display_level), this.repeat);
		}
	    }
	);
    },
});

enyo.kind({
    name: "gx.SimpleEQDisplay",
    layoutKind: "FittableColumnsLayout",
    classes: "gx-eqlevel",
    published: {
	repeat: 100,
    },
    timeout_handle: null,
    components:[
	{name: "eqbar", kind: "gx.eqLevel", fit: true, showStripes: false },
    ],
    //obj: null,
    create: function() {
	this.inherited(arguments);
	this.start();
	this.display_level();
	this.objChanged();
    },
    start: function() {
	if (this.timeout_handle) {
	    clearTimeout(this.timeout_handle);
	}
	this.display_level();
    },
    objChanged: function() {
	if (this.obj === null) {
	    return;
	}
	    this.start();
    },
    display_level: function() {
	if (typeof(this.$.eqbar) == "undefined") {
		return;
	}
	if (this.obj === null) {
	    return;
	}
	this.timeout_handle = null;
	if (!gxeq) {
			this.$.eqbar.setValue(0.0);
		if (!this.timeout_handle) {
		    this.timeout_handle = setTimeout(
			enyo.bind(this, this.display_level), this.repeat);
		}
		return;
	}
	guitarix.call(
	    'get_parameter_value', [this.obj.id],
	    this, function(result) {
		this.$.eqbar.setValue(1+Math.log(Math.max(result[0], 0.001))/(3*Math.log(10)));
		if (!this.timeout_handle) {
		    this.timeout_handle = setTimeout(
			enyo.bind(this, this.display_level), this.repeat);
		}
	    }
	);
    },
});

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
	this.setValue(obj.value[obj.id]+0.0001);
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
	    v = Math.round(inEvent.value*100)/100;
	}
	guitarix.notify("set", [o.id, v]);
	if (o.id.match(/.*\.on_off$/)) { // signaling up only needed for effect on/off atm.
	    this.doParameterChanged({id: o.id, value: v});
		if (o.id == "graphiceq.on_off") {
			gxeq = v;
		}
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
