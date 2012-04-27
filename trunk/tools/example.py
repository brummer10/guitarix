from pylab import *
from scipy.signal import freqz
import pluginloader

fs = 44100
dsp = pluginloader.Plugin("./example_plugin.so")
dsp.init(fs)
print "default level:", dsp["dsp.level"]
dsp["dsp.level"] = 0.5
impulse = zeros(5, dtype=float32)
impulse[0] = 1.0
w, h = freqz(dsp.compute(impulse))
# skip frequency 0 (h[0] == 0)
w = w[1:]
# scale 0..2*pi to 0 .. fs
w = w/(2*pi)*fs
# dB of absolute value
h = 20*log10(abs(h[1:]))
plot(w, h)
show()

## execution time:

inp = array(np.random.uniform(0, 1, 1000), float32)
n = 100
tm = zeros(n)
for i in range(n):
    dsp.compute(inp)
    tm[i] = dsp.nanosec_per_sample
print "%.2f +/- %.3f" % (mean(tm), std(tm))
