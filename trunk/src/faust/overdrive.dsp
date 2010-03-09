import("music.lib");
import("guitarix.lib");

drive = vslider("drive[old:drive]", 1, 1, 20, 0.1);
f = drive * -0.5 : db2linear : smoothi(0.999);

process(x) = (x*(abs(x) + drive)/(x*x + (drive-1)*abs(x) + 1)) * f;
