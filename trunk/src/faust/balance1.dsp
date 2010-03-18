import("guitarix.lib");

bal = vslider(".amp.balance[name:Balance][alias]", 0, -1, 1, 0.1);

process = _ <: balance(bal);
