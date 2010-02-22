faas1 = vgroup("anti_aliase", vslider("feedback[name:Feedback]", 0.3, 0.3, 0.9, 0.01));
process = +~_''*faas1;
