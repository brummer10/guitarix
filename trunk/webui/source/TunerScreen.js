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

enyo.kind({
    name: "gx.TunerScreen",
    layoutKind: "FittableRowsLayout",
    classes: "gx-mainscreen",
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
