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


function UiBuilder() {
}

UiBuilder.prototype.build = function(builderlist, param, ownerwidget, control_setter) {
    this.param = param;
    this.owner = [ownerwidget];
    this.control_setter = control_setter;
    this.level = 0;
    this.counter = 0;
    this.state = 0; // 0: before on/off, 1: after on/off, 2: minibox, 3: rackbox

    for (var i = 0; i < builderlist.length; i++) {
	this["if_"+builderlist[i][0]].apply(this, builderlist[i].slice(1));
    }
}

UiBuilder.prototype.prepare_obj = function(id) {
    // side effect: store parameter id
    var o = this.param[id];
    o.id = id;
    return o;
}

UiBuilder.prototype.activateDrawer = function(inSender) {
    var w = inSender.getParent().getClientControls()[1];
    w.setOpen(!w.open);
}

UiBuilder.prototype.openBox = function(label) {
    if (this.state != 3) { // rackbox
	this.state = 2; // minibox
    }
    var own = this.owner[this.owner.length-1];
    if (this.state == 2 || label === null || label == "" || label == "Analyze") {
	this.owner.push(own);
    } else {
	var nm = "drawer_" + this.counter++;
	own.createComponent({
	    components: [
		{kind: "onyx.Button", style: "margin-top: 20px", content: label, ontap: "activateDrawer"},
		{name: nm, kind: "onyx.Drawer", open: false},
	    ],
	});
	own.activateDrawer = this.activateDrawer;
	this.owner.push(own.$[nm]);
    }
    this.level++;
}

UiBuilder.prototype.if_openTabBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openVerticalBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openVerticalBox1 = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openVerticalBox2 = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openHorizontalBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openHorizontalhideBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openHorizontalTableBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openFrameBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openFlipLabelBox = UiBuilder.prototype.openBox;
UiBuilder.prototype.if_openpaintampBox = UiBuilder.prototype.openBox;

UiBuilder.prototype.if_closeBox = function() {
    this.level--;
    this.owner.pop();
    if (this.state == 2 && this.level == 0) {
	this.state = 3;
    }
}

UiBuilder.prototype.if_insertSpacer = function() {}
UiBuilder.prototype.if_set_next_flags = function(flags) {}

UiBuilder.prototype.get_name = function(label, name, id) {
    if (label === undefined) {
	return "";
    }
    if (label !== null) {
	return label;
    }
    if (name == "") {
	return id;
    }
    return name;
}

UiBuilder.prototype.create_slider = function(id, label) {
    if (this.state == 2) { // minibox
	return;
    }
    this.state = 3; // rackbox
    var o = this.prepare_obj(id);
    var el = this.owner[this.owner.length-1].createComponent(
	{kind: "gx.ValueSlider", classes: "gx-control-slider",
	 varname: this.get_name(label, o.name, id), obj: o});
    this.control_setter[id] = enyo.bind(el, el.setValue);
}

UiBuilder.prototype.create_simple_meter = function(id, label) {
    if (this.state == 2) { // minibox
	return;
    }
    this.state = 3; // rackbox
    var o = this.prepare_obj(id);
    var el = this.owner[this.owner.length-1].createComponent(
	{kind: "gx.SimpleLevelDisplay", classes: "gx-maxlevel",
	 varname: this.get_name(label, o.name, id), obj: o});
    this.control_setter[id] = enyo.bind(el, el.display_level);
}

UiBuilder.prototype.create_eq_meter = function(id, label) {
    if (this.state == 2) { // minibox
	return;
    }
    this.state = 3; // rackbox
    var o = this.prepare_obj(id);
    var el = this.owner[this.owner.length-1].createComponent(
	{kind: "gx.SimpleEQDisplay", classes: "gx-maxlevel",
	 varname: this.get_name(label, o.name, id), obj: o});
    this.control_setter[id] = enyo.bind(el, el.display_level);
}

UiBuilder.prototype.create_simple_c_meter = function(id, idl, label) {
    if (this.state == 2) { // minibox
	return;
    }
    this.state = 3; // rackbox
    var o = this.prepare_obj(idl);
    var el = this.owner[this.owner.length-1].createComponent(
	{kind: "gx.EQSlider", classes: "gx-control-slider",
	 varname: this.get_name(label, o.name, idl), obj: o});
    this.control_setter[idl] = enyo.bind(el, el.setValue);
    this.create_eq_meter(id, label);
}

UiBuilder.prototype.create_p_meter = function(id, idl, idh, label) {
    if (this.state == 2) { // minibox
	return;
    }
    this.state = 3; // rackbox
    var o = this.prepare_obj(id);
    var el = this.owner[this.owner.length-1].createComponent(
	{kind: "gx.SimpleLevelDisplay", classes: "gx-maxlevel",
	 varname: this.get_name(label, o.name, id), obj: o});
    this.control_setter[id] = enyo.bind(el, el.setValue);
}

UiBuilder.prototype.create_switch = function(sw_type, id, label) {
    if (this.state == 2) { // minibox
	return;
    }
    if (this.state == 0) { // before on/off
	this.state == 1; // after on/off switch
    } else {
	this.state == 3; // rackbox
    }
    var o = this.prepare_obj(id);
    el = this.owner[this.owner.length-1].createComponent({
	classes: "gx-control-switch",
	components: [
	    {kind: "onyx.ToggleButton", value: o.value[id], obj: o},
	    {tag: "span", content: this.get_name(label, o.name, id)},
	],
    });
    el = el.getClientControls()[0]; // Button
    this.control_setter[id] = enyo.bind(el, el.setValue);
	if (id == "graphiceq.on_off") {
		gxeq = o.value[id];
	}
}

UiBuilder.prototype.create_selector = function(id, label) {
    if (this.state == 2) {
	return;
    }
    this.state = 3;
    var o = this.prepare_obj(id);
    var c = [];
    var v = o.value[id];
    for (var j = 0; j < o.value_names.length; j++) {
	var p = o.value_names[j];
	var s = {content: p[1], key: p[0]};
	if (p[0] == v) {
	    s.active = true;
	}
	c.push(s);
    }
    el = this.owner[this.owner.length-1].createComponent({
	classes: "gx-control-select",
	components: [
	    {content: this.get_name(label, o.name, id)},
	    {kind: "onyx.PickerDecorator", components: [
		{},
		{kind: "onyx.Picker",
		 components: c,
		 obj: o,
		 setValue: function(v) {
		     var cc = this.getClientControls();
		     for (var i = 0; i < cc.length; i++) {
			 if (i == v) {
			     cc[i].setActive(true);
			 }
		     }
		 },
		}],
	    }],
    });
    el = el.getClientControls()[1].getClientControls()[1]; // Picker
    this.control_setter[id] = enyo.bind(el, el.setValue);
}

UiBuilder.prototype.if_create_big_rackknob = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_mid_rackknob = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_small_rackknob = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_small_rackknobr = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_master_slider = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_feedback_slider = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_selector_no_caption = UiBuilder.prototype.create_selector; // label === undefined
UiBuilder.prototype.if_create_selector = UiBuilder.prototype.create_selector;
UiBuilder.prototype.if_create_switch_no_caption = UiBuilder.prototype.create_switch;  // label === undefined
UiBuilder.prototype.if_create_feedback_switch = UiBuilder.prototype.create_switch;  // label === undefined
UiBuilder.prototype.if_create_switch = UiBuilder.prototype.create_switch;
UiBuilder.prototype.if_create_wheel = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_port_display = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_p_display = UiBuilder.prototype.create_p_meter;
UiBuilder.prototype.if_create_spin_value = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_simple_spin_value = UiBuilder.prototype.create_slider; // label === undefined
UiBuilder.prototype.if_create_eq_rackslider_no_caption = UiBuilder.prototype.create_slider;
UiBuilder.prototype.if_create_simple_meter = UiBuilder.prototype.create_simple_meter; // label === undefined
UiBuilder.prototype.if_create_simple_c_meter = UiBuilder.prototype.create_simple_c_meter; // label === undefined
// void load_glade(const char *data)        does not happen because we ask for StackBuilder format
// void load_glade_file(const char *fname)  is transformed to load_glade by the backend
