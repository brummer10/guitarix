enyo.kind({
    name: "gx.LeftRightArranger",
    kind: "LeftRightArranger",
    margin: 0,
    flowControl: function(inControl, inArrangement) {
	if (inControl.panelIndex == this.container.fromIndex ||
	    inControl.panelIndex == this.container.toIndex) {
	    inControl.setShowing(true);
	    this.inherited(arguments);
	} else {
	    inControl.applyStyle("z-index",-1);
	}
    },
});

enyo.kind({
    name: "App",
    kind: "FittableRows",
    components:[
	{name: "panels", kind: "enyo.Panels", arrangerKind: "gx.LeftRightArranger",
	 index: 1, onTransitionStart: "transitionStarted", draggable:true,
	 onTransitionFinish: "transitionFinished",
	 fit: true, components:[
	     {name: "TunerScreen", kind: "gx.TunerScreen", onTunerOff:"showMain"},
	     {name: "MainScreen", kind: "gx.MainScreen", onTunerOn:"tunerOn", onEffects: "EffectsOn"},
	     {name: "EffectScreen", kind: "gx.EffectScreen", onEffectTapped:"showEffect", onMain: "showMain"},
	     {name: "EffectUnit", kind: "gx.EffectUnit", onEffects: "showEffectList"},
	 ]},
	{name: "errorpopup", kind: "onyx.Popup", scrim: true,
	 floating: true, centered: true, autoDismiss: false, components:[
	     {kind: "onyx.Spinner"},
	     {name: "msg", style: "display: inline; margin: 1ex; vertical-align: 100%"},
	 ]},
	{name: "guitarix", kind: "gx.JsonRpcSocket", onNotify: "guitarixNotify",
	 onError: "guitarixError", onClose: "guitarixClose", onOpen: "guitarixOpen",
	 onBadMessage: "guitarixBadMessage", onUnknownMessage: "guitarixUnknownMessage",
	 uri: 'ws://'+(document.location.hostname||'localhost')+':8000/json'}
    ],
    create: function() {
    	this.inherited(arguments);
	var p = this.$.panels.getPanels();
	for (var i = 0; i < p.length; i++) {
	    p[i].panelIndex = i;
	}
	window.guitarix = this.$.guitarix;
    },
    transitionFinished: function(inSender, inEvent) {
	var p;
	var i = inEvent.fromIndex;
	if (i !== undefined) {
	    p = this.$.panels.getPanels()[i];
	    if (p.stopPanel !== undefined) {
		p.stopPanel();
	    }
	}
	p = this.$.panels.getPanels()[inEvent.toIndex];
	if (p.startPanel !== undefined) {
	    p.startPanel();
	}
    },
    transitionStarted: function(inSender, inEvent) {
	var p;
	p = this.$.panels.getPanels()[inEvent.fromIndex];
	if (p.leavePanel !== undefined) {
	    p.leavePanel();
	}
	p = this.$.panels.getPanels()[inEvent.toIndex];
	if (p.preparePanel !== undefined) {
	    p.preparePanel();
	}
    },
    EffectsOn: function() {
	this.$.panels.setIndex(this.$.EffectScreen.panelIndex);
    },
    tunerOn: function() {
	this.$.panels.setIndex(this.$.TunerScreen.panelIndex);
    },
    showMain: function() {
	this.$.panels.setIndex(this.$.MainScreen.panelIndex);
    },
    showEffect: function(inSender, inEvent) {
	var p = this.$.EffectUnit;
	p.setFxId(inEvent.fxId);
	this.$.panels.setIndex(p.panelIndex);
    },
    showEffectList: function(inSender, response) {
	this.$.panels.setIndex(this.$.EffectScreen.panelIndex);
    },
    guitarixUnknownMessage: function(inSender, response) {
	console.log("unknown message", response);
    },
    guitarixBadMessage: function(inSender, inEvent) {
	console.log("bad message", inEvent);
    },
    guitarixNotify: function(inSender, response) {
	switch (response.method) {
	case "preset_changed":
	    this.$.EffectScreen.setCurrentPreset(response.params);
	    this.$.MainScreen.display_preset(response.params[0], response.params[1]);
	    break;
	case "display_bank_preset":
	    this.$.MainScreen.display_preset(response.params[0], response.params[1]);
	    break;
	case "tuner_changed":
	    tuner.freq = response.params[0];
	    break;
	case "state_changed":
	    this.$.MainScreen.setStatus(response.params[0]);
	    this.$.TunerScreen.setStatus(response.params[0]);
	    break;
	case "set_display_state":
	    /*
	    if (!tuner.stop) {
		show_tuner(0);
	    }
	    */
	    this.$.MainScreen.display_state(response.params[0]);
	    break;
	case "show_tuner":
	    if (response.params[0]) {
		this.tunerOn();
	    } else {
		this.showMain();
	    }
	    break;
	case "errormsg":
	    this.$.MainScreen.showMessage(response.params[0]);
	    break;
	default:
	    console.log("unknown notify: ", response);
	    break;
	}
    },
    guitarixError: function(inSender, inEvent) {
	this.$.msg.setContent("Guitarix connection error... retrying");
	this.$.errorpopup.show();
    },
    guitarixClose: function(inSender, inEvent) {
	this.$.msg.setContent("connection to Guitarix closed... retrying");
	this.$.errorpopup.show();
    },
    guitarixOpen: function(inSender, inEvent) {
	//this.$.MainScreen.setRepeat(1100);
	guitarix.notify("listen",["all"])
	guitarix.call(
	    "getstate",[],
	    this.$.MainScreen, function(result) {
		this.setStatus(result);
	    });
	guitarix.call(
	    "get",["system.current_bank","system.current_preset"],
	    this, function(result) {
		var p = [result["system.current_bank"], result["system.current_preset"]];
		this.$.EffectScreen.setCurrentPreset(p);
		this.$.MainScreen.display_preset(p[0], p[1]);
	    });
	this.$.errorpopup.hide();
    },
});
