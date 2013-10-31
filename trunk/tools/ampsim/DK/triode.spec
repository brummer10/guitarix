load_schema = "triode.sch"
input_signal = 10 * sweep(startfreq=30, stopfreq=20000, timespan=1)
maxerr = 1e-5
spline_order = [[4]]
basegrid = [[256]]
#test_signal = 10 * sine_signal(freq=100)
