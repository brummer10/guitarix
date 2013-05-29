enyo.kind({
    name: "gx.TunerScreen",
    layoutKind: "FittableRowsLayout",
    events:{
	onTunerOff: "",
    },
    components:[
	{fit:true, style: "display: table; width: 100%; height: 100%", components:[
	    {style: "display: table-cell; vertical-align: middle", components:[
		{name: "canvas", tag: "canvas"},
	    ]}
	]},
	{kind: "onyx.Toolbar", layoutKind: "FittableColumnsLayout", components:[
	    {kind: "onyx.Button", content: "Tuner Off", ontap:"tunerOff"},
	    {fit:true},
	    {name: "status", kind: "gx.StatusDisplay", runstate: "bypassed"},
	]},
    ],
    setStatus: function(stat) {
	this.$.status.setStatus(stat);
    },
    tunerOff: function(inSender, inEvent) {
	this.doTunerOff(inEvent);
	return true;
    },
    create: function() {
	create_tuner();
	this.inherited(arguments);
    },
    rendered: function() {
	this.inherited(arguments);
	prepareCanvas(this.$.canvas.hasNode());
    },
    startPanel: function() {
	guitarix.notify("setstate", ["bypassed"]);
	guitarix.notify("switch_tuner", [1]);
	var w = this.$.canvas;
	if (w.hasNode()) {
	    drawCanvas(w.node);
	}
    },
    stopPanel: function() {
	guitarix.notify("setstate", ["running"]);
	guitarix.notify("switch_tuner", [0]);
	tuner.stop = 1;
    },
});
