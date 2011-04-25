import("guitarix.lib");

bal = vslider(".amp.balance[name:Balance]", 0, -1, 1, 0.1);

process = balance(bal);
