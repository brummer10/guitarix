declare name "AntiAlias";

faas1 = vslider("feedback", 0.3, 0.3, 0.9, 0.01);
process = +~_''*faas1;
