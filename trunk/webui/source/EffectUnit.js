enyo.kind({
    name: "gx.EffectControls",
    kind: "enyo.Scroller",
    classes: "gx-effect",
    published:{
	fxId: null,
    },
    handlers: {
	onChanging: "valueChanged",
	onChange:   "valueChanged",
    },
    control_setter: {},
    fxIdChanged: function() {
	this.destroyClientControls();
	if (!this.fxId) {
	    return;
	}
	guitarix.call(
	    "queryunit", [this.fxId],
	    this, function(result) {
		var name, o, a, i, id, nm, el;
		var m = this.fxId+"\\.(position|s_h|on_off|pp)$";
		a = [];
		if (this.fxId != "ampstack") {
		    id = this.fxId+".on_off"
		    o = result[id];
		    if (o !== undefined) {
			o.id = id;
			a.push(o);
		    }
		}
		for (id in result) {
		    if (id.match(m)) {
			continue;
		    }
		    o = result[id]
		    o.id = id
		    a.push(o);
		}
		for (i = 0; i < a.length; i++) {
		    o = a[i];
		    name = o.name;
		    if (!name) {
			name = o.id;
		    }
		    nm = "eff_"+o.id;
		    if (o.ctl_switch) {
			this.createComponent({
			    components: [
				{content: name},
				{kind: "onyx.ToggleButton",
				 name: nm,
				 value: o.value[o.id],
				 obj: o,
				}],
			});
			el = this.$[nm];
			this.control_setter[o.id] = enyo.bind(el, el.setValue);
		    } else if (o.ctl_enum) {
			var c = [];
			var v = o.value[o.id];
			for (var j = 0; j < o.value_names.length; j++) {
			    var p = o.value_names[j];
			    var s = {content: p[1], key: p[0]};
			    if (p[0] == v) {
				s.active = true;
			    }
			    c.push(s);
			}
			this.createComponent({
			    components: [
				{content: name},
				{kind: "onyx.PickerDecorator", components: [
				    {},
				    {kind: "onyx.Picker",
				     name: nm,
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
			el = this.$[nm];
			this.control_setter[o.id] = enyo.bind(el, el.setValue);
		    } else {
			this.createComponent({
			    components: [
				{content: name},
				{kind: "onyx.Slider",
				 name: nm,
				 lockBar: true,
				 tappable: true,
				 value: o.value[o.id],
				 min: o.lower_bound,
				 max: o.upper_bound,
				 obj: o,
				}],
			});
			el = this.$[nm];
			this.control_setter[o.id] = enyo.bind(el, el.setValue);
		    }
		}
		this.render();
		this.setupDone = true;
	    });
    },
    setupDone: false,
    valueChanged: function(inSender, inEvent) {
	if (!this.setupDone) {
	    return;
	}
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
    },
    setParameter: function(param_id, value) {
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
