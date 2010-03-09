balance = vslider(".amp.balance[name:Balance][old:fslider25]", 0, -1, 1, 0.1);

process = *(1 - max(0, balance)), *(1 - max(0, -balance));
