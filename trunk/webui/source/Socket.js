/**
 * Copyright (c) 2012 Ryan M. Hope <rmh3093 at gmail dot com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
	this.createSocket();
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
