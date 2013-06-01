enyo.kind({
    name: "gx.EffectControls",
    kind: "enyo.Scroller",
    published:{
	fxId: null,
    },
    handlers: {
	onChanging: "valueChanged",
	onChange:   "valueChanged",
    },
    fxIdChanged: function() {
	this.destroyClientControls();
	if (!this.fxId) {
	    return;
	}
	guitarix.call(
	    "queryunit", [this.fxId],
	    this, function(result) {
		var name, o;
		var m = this.fxId+"\\.(position|s_h|on_off|pp)$";
		for (var key in result) {
		    if (key.match(m)) {
			continue;
		    }
		    o = result[key];
		    name = o.name;
		    if (!name) {
			name = key;
		    }
		    o.id = key
		    if (o.ctl_switch) {
			this.createComponent({
			    components: [
				{content: name},
				{kind: "onyx.ToggleButton",
				 value: o.value[key],
				 obj: o,
				}],
			});
		    } else if (o.ctl_enum) {
			var c = [];
			var v = o.value[key];
			for (var i = 0; i < o.value_names.length; i++) {
			    var p = o.value_names[i];
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
				     components: c,
				     obj: o,
				    }],
				}],
			});
		    } else {
			this.createComponent({
			    components: [
				{content: name},
				{kind: "onyx.Slider",
				 lockBar: true,
				 tappable: true,
				 value: o.value[key],
				 min: o.lower_bound,
				 max: o.upper_bound,
				 obj: o,
				}],
			});
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
});
