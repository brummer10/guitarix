import os, re, math, pickle
from pylab import *
from scipy.signal import freqz, lfilter
from scipy import optimize

def load_crybaby():
    from lv2loader import LV2_Plugin
    return LV2_Plugin('holters-sim/crybaby-1.2/')

def load_dunwah():
    import dunwah
    return dunwah.dsp()

def display_parameter(filt):
    print("Parameter:")
    print("\n".join(["    %s=%s [%s..%s]" % ((k,filt[k])+tuple(filt.get_range(k)))
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

def plot_figure(filt, name, para, rg, clr="-", fs=44100):
    display_parameter(filt)
    impulse = zeros(10000,dtype=float32)
    impulse[0] = 1
    dflt = filt[para]
    #subplot(2,2,1)
    title('Guitarix crybaby2')
    ylabel("gain (dB)")
    xlabel("Frequency (Hz)")
    sn = False
    res = []
    for freq in rg:
        res.append(plotone(filt, freq, para, impulse, clr, fs))
    #legend(title="Param.: %s" % name, fancybox=True, loc='upper right')
    #a = array(res);
    #subplot(2,2,2)
    #plot(1/(1.06-a[:,0]), a[:,1])
    #subplot(2,2,3)
    #plot(a[:,0], a[:,2])
    #subplot(2,2,4)
    #plot(a[:,0], a[:,3])
    #show()

def plot_figure_libcrybaby(clr="-",fs=44100):
    filt = load_crybaby()
    filt['refvolt'] = 0.1
    para = 'hotpotz'
    name = filt.get_var_attr(para)[0]
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(fs)
    plot_figure(filt, name, para, rg, clr, fs)

def plot_figure_dunwah(clr="-", fs=44100):
    filt = load_dunwah()
    para = 'wah'
    name = "DunWah"
    #rg = linspace(*filt.get_range(para), num=10)
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(fs)
    plot_figure(filt, name, para, rg, clr, fs)

def plot_figure_crybaby(clr="-", fs=44100):
    import crybaby
    para = '.crybaby.wah'
    filt = crybaby.dsp()
    name = "Pot"
    #rg = linspace(*filt.get_range(para), num=10)
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(fs)
    plot_figure(filt, name, para, rg, clr, fs)

def plot_figure_autowah(clr="-", fs=44100):
    import ladspaloader
    filt = ladspaloader.Ladspa("/usr/lib/ladspa/autowah.so", fs)
    filt["Drive"] = 0
    filt["Decay"] = 0
    filt["Range"] = 0
    filt["Mix"] = 1
    name = "Freq"
    para = "Freq"
    rg = linspace(0, 1, num=10)
    plot_figure(filt, name, para, rg, clr, fs)

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

def invfreqz(w, h):
    # w: frequency points array
    # h: response array (complex values)
    # returns the fitted polinomial coeffients A and B of order 3
    # (biquad filter)
    with open("/tmp/out", "w") as fd:
        save_octave("F", w, fd)
        save_octave("H", h, fd)
    p = os.popen("octave -q","w")
    p.write(
        "pkg load signal;\n"
        "load /tmp/out;\n"
        "wt = 1 ./ F.^2;\n"
        "[B,A] = invfreqz(H,F,3,3,wt);\n"
        "save /tmp/out B A;\n")
    p.close()
    with open("/tmp/out") as fd:
        res = load_octave(fd)
    os.remove("/tmp/out")
    return res

def run_filter(filt,impulse,fs):
    # returns a biquad filter estimate (coefficients B, A) and the
    # (complex) frequency response h
    #
    # skip transients
    filt.compute(zeros(10000,dtype=float32))
    # calculate frequency response
    w, h = freqz(filt.compute(impulse), worN=15000)
    # calculate filter coefficients
    k1 = int(round(len(h)*10.0/fs))
    k2 = int(round(len(h)*20000.0/fs))
    B, A = invfreqz(w[k1:k2+1], h[k1:k2+1])
    return B, A, h

def estimate(rg, filt, para, impulse, fs):
    # para: parameter to sweep
    # rg: range of values for parameter para
    # filt: filter to be analyzed
    # impulse: input vector
    # fs: sample rate
    # returns biquad filter estimates for each parameter value:
    #  0: (aa) vector of biquad theta * fs
    #  1: (Q) vector of biquad quality factors
    #  2: (maxh) vector of maxium absolute value of frequency response
    #  3: mean value of real roots
    #  4: (Bconst)  B for freq_const
    #  5: (freq_const)  para value at center of range
    aa = zeros(len(rg))
    Q = zeros(len(rg))
    maxh = zeros(len(rg))
    real_roots = zeros(len(rg))
    for i, freq in enumerate(rg):
        filt[para] = freq
        B, A, h = run_filter(filt, impulse, fs)
        maxh[i] = max(abs(h))
        # use a constant B
        #print(B/B[0])
        if i == (len(rg)+1)//2:
            Bconst = B
            freq_const = freq
        # use just the two conjugate roots for the biquad
        # the real root is nearly constant
        bq_roots = []
        for j, v in enumerate(roots(A)):
            if v.imag == 0:
                real_roots[i] = v.real
            else:
                bq_roots.append(v)
        A_bq = poly(bq_roots)
        # calculate pole frequency and quality factor
        R = sqrt(A_bq[2])
        theta = math.acos(A_bq[1]/(-2*R))
        aa[i] = fs * theta
        Q[i] = theta / (2 - 2*R)

        print('Pole frequency = %f Hz' % (aa[i]/(2*pi)))
        #print('Q = %f' % Q[i])
        #print("R =", R)

    return aa, Q, maxh, sum(real_roots) / len(real_roots), Bconst, freq_const

def fit_param(rg, aa, Q, fs):
    #order = 3
    order = 6
    def f(t):
        xx = 1/(t-aa)
        a = polyfit(rg, xx, order)
        def ff(x, *p):
            return t - 1/polyval(p, x)
        a = optimize.curve_fit(ff, rg, aa, a)
        a = a[0]
        res = sum((xx-polyval(a,rg))**2)/sum(xx*xx)**2
        return res
    off = optimize.fmin(f, 0.04*fs, disp=False)[0]
    f = 1/(off-aa)
    a = polyfit(rg, f, order)
    def ff(x, *p):
        return off - 1/polyval(p, x)
    a = optimize.curve_fit(ff, rg, aa, a)
    a = a[0]
    a1A = a
    #order = 4
    order = 5
    a = polyfit(rg, Q, order)
    qA = a
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

def make_gain(rg, off, a1A, qA, maxh, z1, Bconst, fs):
    gain = zeros(len(rg))
    for i, freq in enumerate(rg):
        q  = polyval(qA, freq)
        a1 = (off - 1 / polyval(a1A, freq)) / fs
        r = 1 - a1/(2*q)
        A = array((1, -2*r*math.cos(a1), r*r))
        rr = list(roots(A))
        rr.append(z1)
        A = poly(rr)
        w1, h1 = freqz(Bconst, A, worN=15000)
        gain[i] = maxh[i]/max(abs(h1))
    #order = 1
    order = 5
    def ff(t):
        xx = 1/(t-gain)
        a = polyfit(rg, xx, order)
        def f(x, *p):
            return t-1/polyval(p, x)
        a = optimize.curve_fit(f, rg, gain, a)
        a = a[0]
        return sum((xx-polyval(a,rg))**2)
    g_off = optimize.fmin(ff, -0.007, disp = False)
    def f(x, *p):
        return g_off-1/polyval(p, x)
    a = polyfit(rg, 1/(g_off-gain), order)
    a = optimize.curve_fit(f, rg, gain, a)
    a = a[0]
    return gain, g_off, a

def estimate_SR(filt, para, freq_const, impulse):
    # estimate fitted biquad parameter dependency on sample rate
    # returns
    #  0: (z1) mean of the first root
    #  1: polynomial fit for the second root
    #  2: polynomial fit for the third root
    #  3: polynomial fit for B[0]
    lz1 = []
    lz2 = []
    lz3 = []
    lg = []
    ss = linspace(44100, 96000, 10)
    for fs in ss:
        filt.init(fs)
        filt[para] = freq_const
        B, A, h = run_filter(filt, impulse, fs)
        rr = roots(B)
        lz1.append(rr[0])
        lz2.append(rr[1])
        lz3.append(rr[2])
        lg.append(B[0])
    z1 = sum(lz1)/len(lz1)
    z2A = polyfit(ss, lz2, 2)
    z3A = polyfit(ss, lz3, 2)
    gc = polyfit(ss, lg, 2)
    return z1, z2A, z3A, gc

def output_freqz_libcrybaby():
    filt = load_crybaby()
    filt['refvolt'] = 0.1
    para = 'hotpotz'
    name = filt.get_var_attr(para)[0]
    fs = 44100
    filt.init(fs)
    impulse = zeros(10000,dtype=float32)
    impulse[0] = 1
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=20))
    if True:
        aa, Q, maxh, p1, Bconst, freq_const = estimate(rg, filt, para, impulse, fs)
        with open("p.out","wb") as fd:
            pickle.dump((aa,Q,maxh,p1,Bconst,freq_const), fd)
    else:
        with open("p.out","rb") as fd:
            aa, Q, maxh, p1, Bconst, freq_const = pickle.load(fd)
    z1, z2A, z3A, gcA = estimate_SR(filt, para, freq_const, impulse)
    off, a1A, qA = fit_param(rg, aa, Q, fs)
    gain, g_off, gA = make_gain(rg, off, a1A, qA, maxh, p1, Bconst, fs)
    show_param(rg, off, g_off, aa, a1A, Q, qA, gain, gA)
    rg = log10(linspace(*np.power(10,filt.get_range(para)), num=10))
    filt.init(fs)
    for i, freq in enumerate(rg):
        filt[para] = freq
        filt.compute(zeros(10000,dtype=float32))
        w, h = freqz(filt.compute(impulse), worN=15000)

        q  = polyval(qA, freq)
        a1 = (off - 1 / polyval(a1A, freq)) / fs
        g = g_off - 1 / polyval(gA, freq)
        gc = polyval(gcA, fs)

        r = 1 - a1/(2*q)
        A = array((1, -2*r*cos(a1), r*r))
        A = poly(list(roots(A))+[p1])
        B = poly([polyval(z2A,fs),polyval(z3A,fs),z1])
        w1, h1 = freqz(B*g*gc, A, worN=15000)

        semilogx((w*fs/(2*pi))[1:],  20*log10(abs(h[1:])), "b")
        semilogx((w1*fs/(2*pi))[1:], 20*log10(abs(h1[1:])), "r")

    print("theta2pi = (%g - 1000 / (%s)) / SR;" % (off, string_polyval(a1A*1000, "wah")))
    print("Q = %s;" % string_polyval(qA, "wah"))
    print("g = %g - 1 / (%s);" % (g_off, string_polyval(gA, "wah")))
    print("gc = %s;" % string_polyval(gcA, "SR"))
    print("p1 = exp(-1000/(%g*SR));" % (-1000/(fs*log(p1))))
    print("z1 = %g;" % z1)
    print("z2 = %s;" % string_polyval(z2A, "SR"))
    print("z3 = %s;" % string_polyval(z3A, "SR"))

    show()

def compare_dynamics(freq, fs):
    global title
    title("Freq = %g" % freq)

    lfo_freq = 5.0
    block_size = 64
    time = 1
    block_cnt = (time*fs+block_size-1)//block_size
    print(block_cnt)
    samples = block_cnt * block_size

    def sine(freq, div=1):
        return array(sin(2*pi*linspace(0,freq*time,samples // div)),dtype=float32)

    tm = linspace(0,samples/float(fs),samples)
    lfo = 0.5 + sine(lfo_freq,block_size) * 0.5
    signal = sine(freq).reshape(block_cnt,block_size)
    tt = linspace(0,1,samples // 100)

    def sweep(filt, para, clr):
        filt[para] = 0.0
        filt.compute(zeros(10000,float32))
        out = zeros((block_cnt,block_size))
        for i in range(block_cnt):
            filt[para] = lfo[i]
            out[i] = filt.compute(signal[i])
        t = 0.999
        ampl = lfilter([1-t],[1,-t],abs(out.reshape(samples)))
        plot(tm[4000:], 20*log10(ampl[4000:]), clr)

    filt = load_dunwah()
    filt.init(fs)
    para = "wah"

    sweep(filt, para, "r")

    filt = load_crybaby()
    filt.init(fs)
    filt['refvolt'] = 0.1
    para = 'hotpotz'

    sweep(filt, para, "b")

def dynamics_figure(fs):
    subplot(221)
    compare_dynamics(410, fs)
    subplot(222)
    compare_dynamics(500, fs)
    subplot(223)
    compare_dynamics(800, fs)
    subplot(224)
    compare_dynamics(1000, fs)

def compare_freqz(fs):
    plot_figure_dunwah("r", fs)
    plot_figure_libcrybaby("b", fs)

if __name__ == "__main__":
    fs = 44100
    #fs = 48000*2
    try:
        compare_freqz(fs)
        #output_freqz_libcrybaby()
        #dynamics_figure(fs)
        show()
    except KeyboardInterrupt:
        pass
