import os, re, math, pickle
from pylab import *
from scipy.signal import freqz
from scipy import optimize

def load_crybaby():
    from lv2loader import LV2_Plugin
    return LV2_Plugin('holters-sim/crybaby-1.2/')

def display_parameter(filt):
    print("Parameter:")
    print("\n".join(["    %s=%s [%s..%s]" % ((k,filt[k])+filt.get_range(k))
                     for k in filt.keys()]))

def freqz_scaled(v, rate, rng, n = 2400):
    w, h = freqz(v, worN=n)
    scale = lambda freq: int(round(2 * n * freq / rate))
    n0 = scale(rng[0])
    n1 = scale(rng[1])
    w = w[n0:n1+1]
    h = h[n0:n1+1]
    w *= rate / (2*pi)
    return w, h

def parabolaTurningPoint(w, y, h=None):
    idx = y.argmax()
    yTop = y[idx-1] - y[idx+1]
    yBottom = y[idx+1] + y[idx-1] - 2 * y[idx];
    if yBottom != 0.0:
        x0 = yTop / (2 * yBottom)
    else:
        x0 = 0
    if h is not None:
        if x0 > 0:
            hh = h[idx] + x0 * (h[idx+1]-h[idx])
        else:
            hh = h[idx-1] + x0 * (h[idx]-h[idx-1])
        return w[idx] + x0*(w[idx+1]-w[idx]), hh
    else:
        return w[idx] + x0*(w[idx+1]-w[idx]), y[idx] - (yBottom / 2) * x0 * x0

def db_point(w, h, db):
    d = h - db
    return parabolaTurningPoint(w, -d * d, h)

def plotone(filt, freq, para, impulse, clr='--', fs=44100):
    filt[para] = freq
    filt.compute(zeros(10000,dtype=float32))
    w, h = freqz_scaled(filt.compute(impulse), fs, [30, 15000], 15000)
    h = 20*log10(abs(h))
    wmax, hmax = parabolaTurningPoint(w, h)
    wmax3, hmax3 = db_point(w, h, hmax-3)
    q = wmax/wmax3
    Q = 1/abs(q-1/q)
    print("%.2f %.2f %g %g" % (freq, wmax, hmax, Q))
    semilogx(w, h, clr, label="%.3f" % freq)
    return (freq, wmax, hmax, Q)

def plot_figure(filt, name, para, rg):
    display_parameter(filt)
    impulse = zeros(10000,dtype=float32)
    impulse[0] = 1
    dflt = filt[para]
    subplot(2,2,1)
    title('Guitarix crybaby2')
    ylabel("gain (dB)")
    xlabel("Frequency (Hz)")
    sn = False
    res = []
    for freq in rg:
        res.append(plotone(filt, freq, para, impulse, '-'))
    legend(title="Param.: %s" % name, fancybox=True, loc='upper right')
    a = array(res);
    subplot(2,2,2)
    plot(1/(1.06-a[:,0]), a[:,1])
    subplot(2,2,3)
    plot(a[:,0], a[:,2])
    subplot(2,2,4)
    plot(a[:,0], a[:,3])
    show()

def plot_figure_libcrybaby():
    filt = load_crybaby()
    filt['refvolt'] = 0.1
    para = 'hotpotz'
    name = filt.get_var_attr(para)[0]
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(48000)
    plot_figure(filt, name, para, rg)

def plot_figure_dunwah():
    import dunwah
    filt = dunwah.dsp()
    para = 'wah'
    name = "DunWah"
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(48000)
    plot_figure(filt, name, para, rg)

def save_octave(name, var, fd):
    assert isinstance(var, ndarray) and len(var.shape) == 1
    print("# name:", name, file=fd)
    iscompl = iscomplexobj(var)
    if iscompl:
        print("# type: complex matrix", file=fd)
    else:
        print("# type: matrix", file=fd)
    print("# rows: 1", file=fd)
    print("# columns:", var.shape[0], file=fd)
    if iscompl:
        for v in var:
            print((v.real, v.imag), file=fd, end=' ')
    else:
        for v in var:
            print(v, file=fd, end=' ')
    print(file=fd)

def load_octave(fd):
    var = []
    d = {}
    for l in fd:
        l = l.strip()
        if l.startswith("#"):
            m = re.match("# *([a-z]+): *(.*)\n", l)
            if not m:
                continue
            d[m.group(1)] = m.group(2)
        elif l:
            var.append(array([float(v) for v in l.split()]))
    return var

def invfreqz(w, h, numzeros=2, numpoles=2):
    with open("/tmp/out", "w") as fd:
        save_octave("F", w, fd)
        save_octave("H", h, fd)
    p = os.popen("octave -q","w")
    p.write(
        "pkg load signal;\n"
        "load /tmp/out;\n"
        "wt = 1 ./ F.^2;\n"
        "[B,A] = invfreqz(H,F,%d,%d,wt);\n"
        "save /tmp/out B A;\n"
        % (numzeros, numpoles))
    p.close()
    with open("/tmp/out") as fd:
        res = load_octave(fd)
    os.remove("/tmp/out")
    return res

Bconst = array((1, -1.04, 0.04))

def estimate(rg, filt, para, impulse, fs):
    aa = zeros(len(rg))
    Q = zeros(len(rg))
    maxh = zeros(len(rg))
    for i, freq in enumerate(rg):
        filt[para] = freq
        filt.compute(zeros(10000,dtype=float32))
        w, h = freqz(filt.compute(impulse), worN=15000)
        k1 = int(round(len(h)*100.0/fs))
        k2 = int(round(len(h)*10000.0/fs))
        B, A = invfreqz(w[k1:k2+1], h[k1:k2+1])

        R = sqrt(A[2])
        theta = math.acos(A[1]/(-2*R))
        aa[i] = fs * theta
        frn = theta / (2*pi)
        Q[i] = (pi * frn) / (1 - R)

        print('Pole frequency = %f Hz' % (aa[i]/(2*pi)))
        #print('Q = %f' % Q[i])
        #print("R =", R)
        #print("frn =", frn, "theta =", theta)

        A = array((1, -2*R*cos(theta), R*R))
        w1, h1 = freqz(Bconst, A, worN=15000)
        maxh[i] = max(abs(h))
        #print("gain =", gain[i])
    return aa, Q, maxh

def fit_param(rg, aa, Q, fs):
    def f(t):
        xx = 1/(t-aa)
        a = polyfit(rg, xx, 3)
        return sum((xx-polyval(a,rg))**2)
    off = optimize.fmin(f, 0.04*fs, disp=False)[0]
    f = 1/(off-aa)
    a1A = polyfit(rg, f, 3)
    #def ff(x, *p):
    #    return off - 1/polyval(p, x)
    #a1A = optimize.curve_fit(ff, rg, aa, a1A)[0]
    print("theta2pi = %g - 1 / (%s);" % (off, string_polyval(a1A, "wah")))
    qA = polyfit(rg, Q, 3)
    print("Q = %s;" % string_polyval(qA, "wah"))
    return off, a1A, qA

def show_param(rg, off, g_off, aa, a1A, Q, qA, gain, gA):
    subplot(2,2,1)
    f = 1/(off-aa)
    plot(rg, f,"b")
    plot(rg,polyval(a1A,rg),"r")
    subplot(2,2,2)
    plot(rg, Q,"g")
    plot(rg, polyval(qA,rg), "r")
    subplot(2,2,3)
    plot(rg, 1/(g_off-gain), "b")
    plot(rg, polyval(gA,rg), "r")
    show()

def string_polyval(a, var):
    s = ""
    for i, v in enumerate(a):
        if i == 0:
            s = "%g" % v
        elif i == 1:
            s = "%s*%s+%g" % (s, var, v)
        else:
            s = "(%s)*%s+%g" % (s, var, v)
    return s

def make_gain(rg, off, a1A, qA, maxh, fs):
    gain = zeros(len(rg))
    for i, freq in enumerate(rg):
        q  = polyval(qA, freq)
        a1 = (off - 1 / polyval(a1A, freq)) / fs
        r = 1 - a1/(2*q)

        A = array((1, -2*r*math.cos(a1), r*r))
        w1, h1 = freqz(Bconst, A, worN=15000)
        gain[i] = maxh[i]/max(abs(h1))
    g_off = 0.025
    a = polyfit(rg, 1/(g_off-gain), 4)
    def f(x, *p):
        return g_off-1/polyval(p, x)
    a = optimize.curve_fit(f, rg, gain, a)
    a = a[0]
    print("g = %g - 1 / (%s):" % (g_off, string_polyval(a, "wah")))
    return g_off, gain, a

def output_freqz_libcrybaby():
    filt = load_crybaby()
    filt['refvolt'] = 0.1
    para ='hotpotz'
    name = filt.get_var_attr(para)[0]
    fs = 44100
    filt.init(fs)
    impulse = zeros(10000,dtype=float32)
    impulse[0] = 1
    #rg = linspace(*filt.get_range(para), num=20)
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=20))
    if True:
        aa, Q, maxh = estimate(rg, filt, para, impulse, fs)
        with open("p.out","wb") as fd:
            pickle.dump((aa,Q,maxh), fd)
    else:
        with open("p.out","rb") as fd:
            aa, Q, maxh = pickle.load(fd)
    off, a1A, qA = fit_param(rg, aa, Q, fs)
    g_off, gain, gA = make_gain(rg, off, a1A, qA, maxh, fs)
    #show_param(rg, off, g_off, aa, a1A, Q, qA, gain, gA)
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    for i, freq in enumerate(rg):
        filt[para] = freq
        filt.compute(zeros(10000,dtype=float32))
        w, h = freqz(filt.compute(impulse), worN=15000)
        k1 = int(round(len(h)*30.0/fs))
        k2 = int(round(len(h)*5000.0/fs))
        B, A = invfreqz(w[k1:k2+1], h[k1:k2+1])

        R = sqrt(A[2])
        theta = math.acos(A[1]/(-2*R))
        aa[i] = A[1]/(-2*R)
        frn = theta / (2*pi)
        Q[i] = (pi * frn) / (1 - R)

        print('Pole frequency = %f Hz' % (frn * fs))
        print('Q = %f' % Q[i])

        if False:
            A = array((1, -2*R*cos(theta), R*R))
            w1, h1 = freqz(Bconst, A, worN=15000)
            gain[i] = max(abs(h))/max(abs(h1))
            B *= gain[i]
            h1 *= gain[i]
            print("gain =", gain[i])
            #h = h1

        if True:
            q  = polyval(qA, freq)
            a1 = (off - 1 / polyval(a1A, freq)) / fs
            frn = a1/(2*pi)
            r = 1 - a1/(2*q)
            #print("R =", r)
            #print("frn =", frn, "theta =", math.acos(a1))
            g = g_off - 1 / polyval(gA, freq)

            A = array((1, -2*r*cos(a1), r*r))
            w1, h1 = freqz(Bconst*g, A, worN=15000)

            R = sqrt(A[2])
            theta = math.acos(A[1]/(-2*R))
            frn = theta / (2*pi)
            bq = (pi * frn) / (1 - R)
            print('Pole frequency = %f Hz' % (frn * fs))
            print('Q = %f' % q)
            print("gain =", g)

        w *= fs / (2*pi)
        semilogx(w[1:], 20*log10(abs(h[1:])), "b")
        semilogx(w[1:], 20*log10(abs(h1[1:])), "r")
    show()

def display_parameter(filt):
    print("Parameter:")
    print("\n".join(["    %s=%s [%s..%s]" % ((k,filt[k])+filt.get_range(k))
                     for k in filt.keys()]))

if __name__ == "__main__":
    try:
        #plot_figure_libcrybaby()
        #plot_figure_dunwah()
        output_freqz_libcrybaby()
    except KeyboardInterrupt:
        pass
