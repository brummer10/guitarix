/*
jsonrpcws.js
JSON-RPC over WebSocket client implementation
@author: Martin Boros <brainrape@chaosmedia.hu>

*/

//TODO: fix inconsistencies with py
//TODO: doc
//TODO: licence

function JsonRpcWsService(uri, service_def) {
    if(!window.console){window.console={log:function(){}}}
    if(!window.WebSocket){throw "jsonrpcws error: WebSockets not available"}
    if(!window.JSON){throw "jsonrpcws error: JSON (de)serializer not available"}

    //make `this` available in closures
    var that = this
    
    //apply the service definition
    this.local = service_def['local']
    this.onopen = service_def['onopen']
    this.onclose = service_def['onclose']
    
    //set up instance variables
    this._CALLBACK_QUEUE_SIZE = 32
    this._id = null
    this._next_id = 1
    this._callbacks = []
    this.uri = uri

    // Set up WebSocket and event handlers
    this.ws = new WebSocket(uri);

    this.ws.onopen = function(){
        console.log("WebSocket to "+uri+" - connection open.")
        if(that['onopen']){ that.onopen.apply(service) }
    }

    this.ws.onmessage = function(evt) {
        //TODO: error checking
        data = JSON.parse(evt.data);
        console.log("WebSocket to "+uri+" - got data: ", evt.data);
        if (data['method']){
            service_method = that.local[data['method']]
            that._id = data['id']
            ret = service_method.apply(that, data['params'])
            service._id = null
            if(data['id']){
                that.respond(data['id'], ret[0], ret[1])
            }
        } else if (data['result']){
            for(var i=0; i<that._callbacks.length; i++){
                if(that._callbacks[i][0] == data['id']){
                    var callback = that._callbacks.splice(i,1)[0][1]
                    callback.apply(that, [data['result'], data['error']])
                    break;
                }
            }
        } else {
            console.log("WebSocket to "+uri+" - JSONRPC error.");
            that.close()
        }
    };

    this.ws.onerror = function(){
        console.log("WebSocket to "+uri+" - error.");
        if(that['onclose']){ that.onclose.apply(that, error) }
    }

    this.ws.onclose = function(){
        console.log("WebSocket to "+uri+" - connection closed.")
        if(that['onclose']){ that.onclose.apply(that, undefined) }
    }
}


JsonRpcWsService.prototype = {
    request: function(method, params, callback){
        /// Send a request
        //set id
        var id = null
        if(callback){ id = this._next_id; this._next_id += 1; }
        
        //save callback
        if(this._callbacks.length > this._CALLBACK_QUEUE_SIZE){
            this._callbacks.pop()
        }
        if(callback){
            this._callbacks = [[id, callback]].concat(this._callbacks)
        }

        //send message
        message = JSON.stringify({id:id, method:method, params:params})
        console.log("WebSocket to "+this.uri+" - sending data: "+message)
        this.ws.send(message)
    },
    notify: function(method, params){
        /// Send a notification
        this.request (method, params, undefined)
    },
    respond: function(id, result, error){
        /// Send a response
        message = JSON.stringify({id:id, result:result, error:error})
        console.log("WebSocket to "+this.uri+" - sending data: "+message)
        this.ws.send(message)
    },
    close: function(){
        /// Close the connection
        this.ws.close()
    }
}
