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
    name: "gx.SlidingPanel",
    kind: "enyo.Slideable",
    showing: false,
    value: -100,
    min: -100,
    unit: "%",
    classes: "enyo-fit gx-sliding-panel",
    preventDragPropagation: true,
    captureEvents: true,
    handlers: {
	onAnimateFinish: "animateFinished",
	ondown: "down",
	onkeydown: "keydown",
	//onfocus: "focus",
	//onblur: "blur",
    },
    create: function() {
	this.tools.push({kind: "Signals", onKeydown: "keydown"});
	this.inherited(arguments);
    },
    animateFinished: function() {
	if (this.getValue() < 0) {
	    this.setShowing(false);
	}
    },
    showingChanged: function() {
	this.inherited(arguments);
	if (this.showing) {
	    this.resized();
	    if (this.captureEvents) {
		this.capture();
	    }
	} else {
	    if (this.captureEvents) {
		this.release();
	    }
	}
    },
    capture: function() {
	enyo.dispatcher.capture(this, false);
    },
    release: function() {
	enyo.dispatcher.release();
    },
    down: function(inSender, inEvent) {
	//record the down event to verify in tap
	this.downEvent = inEvent;

	// prevent focus from shifting outside the popup when modal.
	if (!inEvent.dispatchTarget.isDescendantOf(this)) {
	    inEvent.preventDefault();
	}
    },
    tap: function(inSender, inEvent) {
	// dismiss on tap if property is set and click started & ended outside the popup
	if ((!inEvent.dispatchTarget.isDescendantOf(this)) && this.downEvent &&
	    (!this.downEvent.dispatchTarget.isDescendantOf(this))) {
	    this.downEvent = null;
	    this.animateToMin();
	    return true;
	}
    },
    keydown: function(inSender, inEvent) {
	if (this.showing && inEvent.keyCode == 27 /* escape */) {
	    this.animateToMin();
	}
    },
    // If something inside the popup blurred, keep track of it.
    blur: function(inSender, inEvent) {
	if (inEvent.dispatchTarget.isDescendantOf(this)) {
	    this.lastFocus = inEvent.originator;
	}
    },
    // When something outside the popup focuses (e.g., due to tab key), focus our last focused control.
    focus: function(inSender, inEvent) {
	var dt = inEvent.dispatchTarget;
	if (!dt.isDescendantOf(this)) {
	    if (dt.hasNode()) {
		dt.node.blur();
	    }
	    var n = (this.lastFocus && this.lastFocus.hasNode()) || this.hasNode();
	    if (n) {
		n.focus();
	    }
	}
    },
});
