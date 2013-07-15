enyo.kind({
    name: "gx.Storage",
    kind: "Component",
    statics: {
	set: function(name, obj){
	    localStorage.setItem(name, JSON.stringify(obj));
	},
	get: function(name){
	    return JSON.parse(localStorage.getItem(name));
	},
	remove: function(name){
	    localStorage.remove(name);
	},
    }
});

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
	     {kind: "onyx.Spinner", style: "float: left"},
	     {name: "msg", style: "margin: 1ex; text-align: center; vertical-align: 100%"},
	     {kind: "onyx.Button", content: "change connection",
	      style: "display: block; margin: auto", ontap: "changeConnection"},
	 ]},
	{name: "guitarix", kind: "gx.JsonRpcSocket", onNotify: "guitarixNotify",
	 onError: "guitarixError", onClose: "guitarixClose", onOpen: "guitarixOpen",
	 onBadMessage: "guitarixBadMessage", onUnknownMessage: "guitarixUnknownMessage"}
    ],
    saveWsHostPort: function(host, port) {
	gx.Storage.set("ws_connection_data",{host:host, port:port});
	this.setWsUri();
    },
    retrieveWsHostPort: function() {
	var s = gx.Storage.get("ws_connection_data");
	var h, p;
	if (s !== null) {
	    h = s.host;
	    p = s.port;
	}
	if (typeof(h) !== "string" || h == "") {
	    h = document.location.hostname||'localhost';
	}
	if (typeof(p) !== "number" || !(p > 0)) {
	    p = 8001;
	}
	return {host: h, port: p};
    },
    retrieveWsUri: function() {
	var s = this.retrieveWsHostPort();
	return 'ws://'+s.host+':'+s.port+'/json'
    },
    setWsUri: function() {
	this.$.guitarix.setUri(this.retrieveWsUri());
    },
    create: function() {
    	this.inherited(arguments);
	var p = this.$.panels.getPanels();
	for (var i = 0; i < p.length; i++) {
	    p[i].panelIndex = i;
	}
	window.guitarix = this.$.guitarix;
	this.setWsUri();
    },
    changeConnection: function(inSender, inEvent) {
	var app = this;
	var p = new onyx.Popup({
	    showing: true,
	    floating: true,
	    centered: true,
	    modal: true,
	    scrim: true,
	    components:[
		{content:"Change connection", style: "text-align: center; font-weight: bold"},
		{tag: "table",components:[
		    {tag: "tr", components:[
			{tag: "th", content: "Host"},
			{tag: "td", components:[{kind:"onyx.InputDecorator", components:[
			    {name: "host", kind: "onyx.Input", selectOnFocus: true, onkeydown: "hostKeyDown"},
			]}]},
		    ]},
		    {tag: "tr", components:[
			{tag: "th", content: "Port"},
			{tag: "td", components:[{kind: "onyx.InputDecorator", components: [
			    {name: "port", type: "number", selectOnFocus: true, kind: "onyx.Input", onkeydown: "portKeyDown"},
			]}]},
		    ]},
		    {tag: "tr", components:[
			{tag: "td", attributes:{colspan:"2", align: "right"}, components:[
			    {kind: "onyx.Button", style: "margin: 10px", content: "Cancel",
			     ontap: "hide"},
			    {kind: "onyx.Button", style: "margin: 10px", content: "Ok",
			     ontap: "save"},
			]},
		    ]},
		]},
	    ],
	    hostKeyDown: function(inSender, inEvent) {
		if (inEvent.keyCode === 13) {
		    this.$.port.focus();
		    return true;
		}
	    },
	    portKeyDown: function(inSender, inEvent) {
		if (inEvent.keyCode === 13) {
		    this.save();
		    return true;
		}
	    },
	    save: function() {
		var host = this.$.host.getValue();
		var port = parseInt(this.$.port.getValue());
		app.saveWsHostPort(host, port);
		this.hide();
	    },
	});
	var s = this.retrieveWsHostPort();
	p.$.host.setValue(s.host);
	p.$.port.setValue(s.port);
	p.render();
	p.$.host.focus();
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
	case "message":
	    if (response.params[0] == "error") {
		this.$.MainScreen.showMessage(response.params[1]);
	    }
	    break;
	case "set":
	    for (var i = 0; i < response.params.length; i += 2) {
		this.$.EffectUnit.setParameter(response.params[i], response.params[i+1]);
		this.$.EffectScreen.setParameter(response.params[i], response.params[i+1]);
		this.$.MainScreen.setParameter(response.params[i], response.params[i+1]);
	    }
	    break;
	case "rack_units_changed":
	    this.$.EffectScreen.rack_units_changed(response.params[0], response.params.slice(1));
	    break;
	default:
	    console.log("unknown notify: ", response);
	    break;
	}
    },
    guitarixError: function(inSender, inEvent) {
	this.$.msg.setContent("Guitarix connection error...\nretrying");
	this.$.errorpopup.show();
    },
    guitarixClose: function(inSender, inEvent) {
	this.$.msg.setContent("connection to Guitarix closed...\nretrying");
	this.$.errorpopup.show();
    },
    guitarixOpen: function(inSender, inEvent) {
	//this.$.MainScreen.setRepeat(1100);
	//this.$.MainScreen.$.maxlevel.setRepeat(5000);
	guitarix.notify("listen", [
	    "preset","state","freq","display","tuner",
	    "presetlist_changed","logger","param","units_changed"])
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
	this.$.MainScreen.$.load.start();
	this.$.MainScreen.$.maxlevel.start();
	this.$.errorpopup.hide();
    },
});
