/*
 * Copyright (C) 2013 Andreas Degert
 * WebSocket wrapper based on ideas from Ryan M. Hope <rmh3093 at gmail dot com>
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
    name: "gx.Socket",
    kind: enyo.Component,

    ws: null,

    published: {
    	uri: null,
    },

    events: {
    	onOpen: "",
    	onClose: "",
    	onMessage: "",
    	onError: "",
    },

    constructed: function() {
    	this.inherited(arguments);
	this.queue = [];
	this.uriChanged();
    },

    createSocket: function() {
	if ("WebSocket" in window) {
	    this.ws = new WebSocket(this.uri);
	} else if ("MozWebSocket" in window) {
	    this.ws = newMozWebSocket(this.uri);
	}
	if (this.ws) {
	    this.ws.onopen = enyo.bind(this, "socketOpened");
	    this.ws.onclose = enyo.bind(this, "doClose");
	    this.ws.onmessage = enyo.bind(this, "doMessage");
	    this.ws.onerror = enyo.bind(this, "doError");
	}
    },

    uriChanged: function() {
	if (this.ws !== null) {
	    this.ws.close();
	    this.ws = null;
	}
	if (this.uri === null) {
	    return;
	}
	this.createSocket();
    },

    socketOpened: function(evt) {
	var v = this.queue;
	var n = v.length;
	this.queue = [];
	for (var i = 0; i < n; i++) {
	    this.send(v[i]);
	}
	this.doOpen(evt);
    },

    send: function(message) {
	if (this.ws.readyState == 1) { // open
	    this.ws.send(message);
	} else {
	    this.queue.push(message);
	}
    }

});

enyo.kind({
    name: "gx.JsonRpcSocket",
    kind: gx.Socket,

    published: {
	retry_timeout: 2, // in seconds
    },

    events: {
    	onNotify: "",
	onBadMessage: "",
	onUnknownMessage: "",
    },

    constructed: function() {
    	this.inherited(arguments);
	this.id = 0;
	this.callbacks = {};
    },

    handlers: {
	onMessage: "receive",
	onClose: "retry",
    },

    retry: function(inSender, inEvent) {
	setTimeout(enyo.bind(this, this.createSocket), this.retry_timeout*1000);
    },

    receive: function(inSender, inEvent) {
	var response;
	try {
	    response = enyo.json.parse(inEvent.data);
	} catch(e) {
	    this.doBadMessage(inEvent);
	    return;
	}
	if ('id' in response) {
	    if (this.callbacks[response.id] && 'result' in response) {
		var f = this.callbacks[response.id];
		delete this.callbacks[response.id];
		f(response.result);
		return;
	    }
	} else {
	    this.doNotify(response);
	    return;
	}
	this.doUnknownMessage(response);
    },

    call: function(method, params /*, [inContext], inResponder */) {
	var id = ++this.id;
	var fn = (arguments.length < 4) ? arguments[2] : enyo.bind(arguments[2], arguments[3]);
	this.send(enyo.json.stringify({
	    method:  method,
	    params:  params,
	    id:      id,
	    jsonrpc: "2.0"
	}));
	this.callbacks[id] = fn;
    },

    notify: function(method, params) {
	this.send(enyo.json.stringify({
	    method:  method,
	    params:  params,
	    jsonrpc: "2.0"
	}));
    }

});
