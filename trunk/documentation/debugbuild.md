<!-- -*- mode: markdown; mode: flyspell; ispell-local-dictionary: "american" -*- -->
\page debugbuild Guitarix debug build

Use "./waf configure --debug" to enable debugging code. If you want to
use gdb you might want to set --cxxflags-debug='-O1 -g'.

Some environment variables are recognized in the debug build:

### GUITARIX_MEASURE (Measurement of DSP processing times)

Time measurement is switched on by defining the environment variable
GUITARIX_MEASURE. When setting its value to 1 results are more
verbose. Results are printed each second on stdout. On intel
architecture it also prints warnings when denormals are encountered
during processing.

For better controlled measurements you can disable frequency scaling
and set cpu affinity:

$ sudo cpufreq-set -d 800MHz -u 800MHz # or whatever your cpu supports
$ GUITARIX_MEASURE=1 taskset -c 1 guitarix

### GUITARIX_MODULE_DEBUG (list of effect plugins)

The full list of effect plugins is output, then the list of active
plugins after each change.

### GUITARIX_TRACE (parameter changes sent to server)

Only when starting Guitarix as user interface client: Output all
parameter changes sent to the server (changes marked with (blocked)
are originated by the server and not reflected back). When set to a
value (other than empty string), print only changes for that parameter
id.
