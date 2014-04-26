#ifndef ORFANIDIS_EQ_H_
#define ORFANIDIS_EQ_H_

//https://github.com/thedrgreenthumb/orfanidis_eq

#include <math.h>
#include <vector>

namespace orfanidis_eq {

//Eq data types.
typedef double eq_single_t;
typedef double eq_double_t;
//NOTE: the default float type usage
//can have shortage of precision

//Eq types
typedef enum {
    none,
    butterworth,
    chebyshev1,
    chebyshev2
} eq_type;

//Eq errors
typedef enum {
    no_error,
    invalid_input_data_error,
    processing_error
} eq_error_t;

//Constants
static const eq_double_t pi = 3.1415926535897932384626433832795;
static const unsigned int fo_section_order = 4;

//Default gains
static const int max_base_gain_db = 0;
static const int min_base_gain_db = -60;
static const int butterworth_band_gain_db = -3;
static const int chebyshev1_band_base_gain_db = -6;
static const int chebyshev2_band_base_gain_db = -40;
static const int eq_min_max_gain_db = 46;

//Default freq's
static const eq_double_t lowest_grid_center_freq_hz = 31.25;
static const eq_double_t bands_grid_center_freq_hz = 1000;
static const eq_double_t lowest_audio_freq_hz = 20;
static const eq_double_t highest_audio_freq_hz = 20000;

//Eq config constants
static const unsigned int default_eq_band_filters_order = 4; //>2
static const eq_double_t default_sample_freq_hz = 48000;

//Version
static const char* eq_version = "0.01";


//------------ Conversion functions class ------------
class conversions
{
    int db_min_max;
    std::vector<eq_double_t> lin_gains;
	
	int lin_gains_index(eq_double_t x) {
		int int_x = (int)x;
		if((x >= -db_min_max) && (x < db_min_max - 1))
			return db_min_max + int_x;
		
		return db_min_max;		
	}

    conversions(){}

public:

    conversions(int min_max) {
        db_min_max = min_max;
        //Update table (vector elements) for fast conversions
        int step = -min_max;
        while(step <= min_max)
            lin_gains.push_back(db_2_lin(step++));
    }

    inline eq_double_t fast_db_2_lin(eq_double_t x) {
        int int_part = (int)x;
        eq_double_t frac_part = x - int_part;
        return lin_gains[lin_gains_index(int_part)]*(1-frac_part)+(lin_gains[lin_gains_index(int_part + 1)])*frac_part;
    }

	inline eq_double_t fast_lin_2_db(eq_double_t x) {
        if((x >= lin_gains[0]) && (x < lin_gains[lin_gains.size() - 1])) {	
			for (unsigned int i = 0; i < lin_gains.size() - 2; i++)
				if((x >= lin_gains[i]) && (x < lin_gains[i + 1]))
					return lin_gains[i] + (lin_gains[i + 1] - lin_gains[i])*(x - ((int)x)); 
        }

        return 0;
    }

    inline static eq_double_t db_2_lin(eq_double_t x) {
        return pow(10, x/20);
    }

    inline static eq_double_t lin_2_db(eq_double_t x) {
        return 20*log(x);
    }

    inline static eq_double_t rad_2_hz(eq_double_t x, eq_double_t fs) {
        return 2*pi/x*fs;
    }

    inline static eq_double_t hz_2_rad(eq_double_t x, eq_double_t fs) {
        return 2*pi*x/fs;
    }
};

//------------ Band freq's structure ------------
struct band_freqs {
private:
    band_freqs();

public:
    eq_double_t min_freq;
    eq_double_t center_freq;
    eq_double_t max_freq;

    band_freqs(eq_double_t f1, eq_double_t f0, eq_double_t f2):
        min_freq(f1), center_freq(f0), max_freq(f2){}

    ~band_freqs(){}
};

//------------ Frequency grid class ------------
class freq_grid {
private:
    std::vector<band_freqs> freqs_;

public:
    freq_grid(){}
    freq_grid(const freq_grid& fg){this->freqs_ = fg.freqs_;}
    ~freq_grid(){}

    eq_error_t set_band(eq_double_t fmin, eq_double_t f0, eq_double_t fmax) {
        freqs_.clear();
        return add_band(fmin, f0, fmax);
    }

    eq_error_t add_band(eq_double_t fmin, eq_double_t f0, eq_double_t fmax) {
        if(fmin < f0 && f0 < fmax)
                freqs_.push_back(band_freqs(fmin, f0, fmax));
            else
                return invalid_input_data_error;
            return no_error;
    }
	
	eq_error_t add_band(eq_double_t f0, eq_double_t df) {
			if(f0 >= df/2)
			{
				eq_double_t fmin = f0 - df/2;
				eq_double_t fmax = f0 + df/2;
                freqs_.push_back(band_freqs(fmin, f0, fmax));
            }
			else
                return invalid_input_data_error;	
            return no_error;
    }

    eq_error_t set_5_bands(eq_double_t center_freq = bands_grid_center_freq_hz) {
        freqs_.clear();
        if(lowest_audio_freq_hz < center_freq &&
                center_freq < highest_audio_freq_hz) {

            //Find lowest center frequency in band
            eq_double_t lowest_center_freq = center_freq;
            while(lowest_center_freq > lowest_grid_center_freq_hz)
                lowest_center_freq/=4.0;
            if(lowest_center_freq < lowest_grid_center_freq_hz)
                lowest_center_freq*=4.0;

            //Calculate freq's
            eq_double_t f0 = lowest_center_freq;
            for(unsigned int i = 0; i < 5 ; i++) {
                freqs_.push_back(band_freqs(f0/2, f0, f0*2));
                f0 *= 4;
            }
        }
        else
            return invalid_input_data_error;
        return no_error;
    }

    eq_error_t set_10_bands(eq_double_t center_freq = bands_grid_center_freq_hz) {
        freqs_.clear();
        if(lowest_audio_freq_hz < center_freq &&
                center_freq < highest_audio_freq_hz) {

            //Find lowest center frequency in band
            eq_double_t lowest_center_freq = center_freq;
            while(lowest_center_freq > lowest_grid_center_freq_hz)
                lowest_center_freq/=2;
            if(lowest_center_freq < lowest_grid_center_freq_hz)
                lowest_center_freq*=2;

            //Calculate freq's
            eq_double_t f0 = lowest_center_freq;
            for(unsigned int i = 0; i < 10; i++) {
                freqs_.push_back(band_freqs(f0/pow(2,0.5), f0, f0*pow(2,0.5)));
                f0 *= 2;
            }
        }
        else
            return invalid_input_data_error;
        return no_error;
    }

    eq_error_t set_20_bands(eq_double_t center_freq = bands_grid_center_freq_hz) {
        freqs_.clear();
        if(lowest_audio_freq_hz < center_freq &&
                center_freq < highest_audio_freq_hz) {

         //Find lowest center frequency in band
            eq_double_t lowest_center_freq = center_freq;
            while(lowest_center_freq > lowest_audio_freq_hz)
                lowest_center_freq/=pow(2,0.5);
            if(lowest_center_freq < lowest_audio_freq_hz)
                lowest_center_freq*=pow(2,0.5);

            //Calculate freq's
            eq_double_t f0 = lowest_center_freq;
            for(unsigned int i = 0; i < 20; i++) {
                freqs_.push_back(band_freqs(f0/pow(2,0.25), f0, f0*pow(2,0.25)));
                f0 *= pow(2,0.5);
            }
        }
        else
            return invalid_input_data_error;
        return no_error;
    }

    eq_error_t set_30_bands(eq_double_t center_freq = bands_grid_center_freq_hz) {
        freqs_.clear();
        if(lowest_audio_freq_hz < center_freq &&
                center_freq < highest_audio_freq_hz) {

            //Find lowest center frequency in band
            eq_double_t lowest_center_freq = center_freq;
            while(lowest_center_freq > lowest_audio_freq_hz)
                lowest_center_freq/=pow(2.0,1.0/3.0);
            if(lowest_center_freq < lowest_audio_freq_hz)
                lowest_center_freq*=pow(2.0,1.0/3.0);

            //Calculate freq's
            eq_double_t f0 = lowest_center_freq;
            for(unsigned int i = 0; i < 30; i++) {
                freqs_.push_back(band_freqs(f0/pow(2.0,1.0/6.0), f0, f0*pow(2.0,1.0/6.0)));
                f0 *= pow(2,1.0/3.0);
            }
        }
        else
            return invalid_input_data_error;
        return no_error;
    }

    unsigned int get_number_of_bands(){return freqs_.size();}
    std::vector<band_freqs> get_freqs(){return freqs_;}
    unsigned int get_freq(unsigned int number) {
        if(number < freqs_.size())
            return freqs_[number].center_freq;
        else
            return 0;
    }

    unsigned int get_rounded_freq(unsigned int number) {
        if(number < freqs_.size()) {
            unsigned int freq = freqs_[number].center_freq;
            if (freq < 100)
                return freq;
            else if(freq >= 100 && freq < 1000) {
                unsigned int rest = freq%10;
                if(rest < 5)
                    return freq - rest;
                else
                    return freq - rest + 10;
            }
            else if(freq >= 1000 && freq < 10000) {
                unsigned int rest = freq%100;
                if(rest < 50)
                    return freq - rest;
                else
                    return freq - rest + 100;
            }
            else if(freq >= 10000) {
                unsigned int rest = freq%1000;
                if(rest < 500)
                    return freq - rest;
                else
                    return freq - rest + 1000;
            }
        }
        return 0;
    }
};

//------------ Forth order sections ------------
class fo_section {
protected:
eq_single_t b0; eq_single_t b1; eq_single_t b2; eq_single_t b3; eq_single_t b4;
eq_single_t a0; eq_single_t a1; eq_single_t a2; eq_single_t a3; eq_single_t a4;

eq_single_t numBuf[fo_section_order];
eq_single_t denumBuf[fo_section_order];

inline eq_single_t df1_fo_process(eq_single_t in) {
        eq_single_t out = 0;
        out+= b0*in;
        out+= (b1*numBuf[0] - denumBuf[0]*a1);
        out+= (b2*numBuf[1] - denumBuf[1]*a2);
        out+= (b3*numBuf[2] - denumBuf[2]*a3);
        out+= (b4*numBuf[3] - denumBuf[3]*a4);

        numBuf[3] = numBuf[2];
        numBuf[2] = numBuf[1];
        numBuf[1] = numBuf[0];
        *numBuf = in;

        denumBuf[3] = denumBuf[2];
        denumBuf[2] = denumBuf[1];
        denumBuf[1] = denumBuf[0];
        *denumBuf = out;

        return(out);
    }

public:
    fo_section() {
        b0 = 0; b1 = 0; b2 = 0; b3 = 0; b4 = 0;
        a0 = 1; a1 = 0; a2 = 0; a3 = 0; a4 = 0;

        for(unsigned int i = 0; i < fo_section_order; i++) {
            numBuf[i] = 0;
            denumBuf[i] = 0;
        }
    }

    virtual ~fo_section(){}

    eq_single_t process(eq_single_t in) {
        return df1_fo_process(in);
    }

    virtual fo_section get() {
        return *this;
    }
};

class butterworth_fo_section : public fo_section {
public:
    butterworth_fo_section(eq_double_t beta,
                           eq_double_t s, eq_double_t g, eq_double_t g0,
                           eq_double_t D, eq_double_t c0) {
        b0 = (g*g*beta*beta + 2*g*g0*s*beta + g0*g0)/D;
        b1 = -4*c0*(g0*g0 + g*g0*s*beta)/D;
        b2 = 2*(g0*g0*(1 + 2*c0*c0) - g*g*beta*beta)/D;
        b3 = -4*c0*(g0*g0 - g*g0*s*beta)/D;
        b4 = (g*g*beta*beta - 2*g*g0*s*beta + g0*g0)/D;

        a0 = 1;
        a1 = -4*c0*(1 + s*beta)/D;
        a2 = 2*(1 + 2*c0*c0 - beta*beta)/D;
        a3 = -4*c0*(1 - s*beta)/D;
        a4 = (beta*beta - 2*s*beta + 1)/D;
    }

    fo_section get() {return *this;}
};

class chebyshev_type1_fo_section : public fo_section {
public:
    chebyshev_type1_fo_section(eq_double_t a,
                               eq_double_t c, eq_double_t tetta_b,
                               eq_double_t g0, eq_double_t s, eq_double_t b,
                               eq_double_t D, eq_double_t c0) {
        b0 = ((b*b + g0*g0*c*c)*tetta_b*tetta_b + 2*g0*b*s*tetta_b + g0*g0)/D;
        b1 = -4*c0*(g0*g0 + g0*b*s*tetta_b)/D;
        b2 = 2*(g0*g0*(1 + 2*c0*c0) - (b*b + g0*g0*c*c)*tetta_b*tetta_b)/D;
        b3 = -4*c0*(g0*g0 - g0*b*s*tetta_b)/D;
        b4 = ((b*b + g0*g0*c*c)*tetta_b*tetta_b - 2*g0*b*s*tetta_b + g0*g0)/D;

        a0 = 1;
        a1 = -4*c0*(1 + a*s*tetta_b)/D;
        a2 = 2*(1 + 2*c0*c0 - (a*a + c*c)*tetta_b*tetta_b)/D;
        a3 = -4*c0*(1 - a*s*tetta_b)/D;
        a4 = ((a*a + c*c)*tetta_b*tetta_b - 2*a*s*tetta_b + 1)/D;
    }

    fo_section get() {return *this;}
};

class chebyshev_type2_fo_section : public fo_section {
public:
    chebyshev_type2_fo_section(eq_double_t a,
                               eq_double_t c, eq_double_t tetta_b,
                               eq_double_t g, eq_double_t s, eq_double_t b,
                               eq_double_t D, eq_double_t c0) {
        b0 = (g*g*tetta_b*tetta_b + 2*g*b*s*tetta_b + b*b + g*g*c*c)/D;
        b1 = -4*c0*(b*b + g*g*c*c + g*b*s*tetta_b)/D;
        b2 = 2*((b*b + g*g*c*c)*(1 + 2*c0*c0) - g*g*tetta_b*tetta_b)/D;
        b3 = -4*c0*(b*b + g*g*c*c - g*b*s*tetta_b)/D;
        b4 = (g*g*tetta_b*tetta_b - 2*g*b*s*tetta_b + b*b + g*g*c*c)/D;

        a0 = 1;
        a1 = -4*c0*(a*a + c*c + a*s*tetta_b)/D;
        a2 = 2*((a*a + c*c)*(1 + 2*c0*c0) - tetta_b*tetta_b)/D;
        a3 = -4*c0*(a*a + c*c - a*s*tetta_b)/D;
        a4 = (tetta_b*tetta_b - 2*a*s*tetta_b + a*a + c*c)/D;
    }

    fo_section get() {return *this;}
};

//------------ Bandpass filters ------------
class bp_filter {
public:
    bp_filter(){}
    virtual ~bp_filter(){}

    virtual eq_single_t process(eq_single_t in) = 0;
};

class dummy_bp_filter : public bp_filter {
public:
    dummy_bp_filter(){}
    ~dummy_bp_filter(){}

    eq_single_t process(eq_single_t in){return in;}
};

class butterworth_bp_filter : public bp_filter {
private:
    std::vector<fo_section> sections_;

    butterworth_bp_filter(){}
public:
    butterworth_bp_filter(unsigned int N,
            eq_double_t w0, eq_double_t wb,
            eq_double_t G, eq_double_t Gb, eq_double_t G0) {
        //Get number of analog sections
        unsigned int r = N%2;
        unsigned int L = (N - r)/2;

        //Convert gains to linear scale
        G = conversions::db_2_lin(G);
        Gb = conversions::db_2_lin(Gb);
        G0 = conversions::db_2_lin(G0);

        eq_double_t epsilon = pow(((eq_double_t)(G*G - Gb*Gb))/(Gb*Gb - G0*G0),0.5);
        eq_double_t g = pow(((eq_double_t)G),1.0/((eq_double_t)N));
        eq_double_t g0 = pow(((eq_double_t)G0),1.0/((eq_double_t)N));
        eq_double_t beta = pow(((eq_double_t)epsilon), -1.0/((eq_double_t)N))*tan(wb/2.0);

        eq_double_t c0 = cos(w0);
        if (w0 == 0) c0 = 1;
        if (w0 == pi/2) c0=0;
        if (w0 == pi) c0 =- 1;

        //Calculate every section
        for(unsigned int i = 1; i <= L; i++) {
            eq_double_t ui = (2.0*i-1)/N;
            eq_double_t si = sin(pi*ui/2.0);

            eq_double_t Di = beta*beta + 2*si*beta + 1;

            sections_.push_back(butterworth_fo_section(beta, si, g, g0, Di, c0));
        }
    }

    ~butterworth_bp_filter(){}

    virtual eq_single_t process(eq_single_t in) {
        eq_single_t p0 = in;
        eq_single_t p1 = 0;
        //Process FO sections in serial connection
        for(unsigned int i = 0; i < sections_.size(); i++) {
            p1 = sections_[i].process(p0);
            p0 = p1;
        }

        return p1;
    }
};

class chebyshev_type1_bp_filter : public bp_filter {
private:
    std::vector<fo_section> sections_;

    chebyshev_type1_bp_filter(){}
public:
    chebyshev_type1_bp_filter(unsigned int N,
            eq_double_t w0, eq_double_t wb,
            eq_double_t G, eq_double_t Gb, eq_double_t G0) {
        //Get number of analog sections
        unsigned int r = N%2;
        unsigned int L = (N - r)/2;

        //Convert gains to linear scale
        G = conversions::db_2_lin(G);
        Gb = conversions::db_2_lin(Gb);
        G0 = conversions::db_2_lin(G0);

        eq_double_t epsilon = pow((eq_double_t)(G*G - Gb*Gb)/(Gb*Gb - G0*G0),0.5);
        eq_double_t g0 = pow((eq_double_t)(G0),1.0/N);
        eq_double_t alfa = pow(1.0/epsilon + pow(1 + pow(epsilon,-2.0),0.5),1.0/N);
        eq_double_t beta = pow(G/epsilon + Gb*pow(1 + pow(epsilon,-2.0),0.5),1.0/N);
        eq_double_t a = 0.5*(alfa - 1.0/alfa);
        eq_double_t b = 0.5*(beta - g0*g0*(1/beta));
        eq_double_t tetta_b = tan(wb/2);

        eq_double_t c0 = cos(w0);
        if (w0 == 0) c0 = 1;
        if (w0 == pi/2) c0=0;
        if (w0 == pi) c0 =- 1;

        //Calculate every section
        for(unsigned int i = 1; i <= L; i++) {
            eq_double_t ui = (2.0*i-1.0)/N;
            eq_double_t ci = cos(pi*ui/2.0);
            eq_double_t si = sin(pi*ui/2.0);

            eq_double_t Di = (a*a + ci*ci)*tetta_b*tetta_b + 2.0*a*si*tetta_b + 1;
            sections_.push_back(chebyshev_type1_fo_section(a, ci, tetta_b, g0, si, b, Di, c0));
        }
    }


    ~chebyshev_type1_bp_filter(){}

    eq_single_t process(eq_single_t in) {
        eq_single_t p0 = in;
        eq_single_t p1 = 0;
        //Process FO sections in serial connection
        for(unsigned int i = 0; i < sections_.size(); i++) {
            p1 = sections_[i].process(p0);
            p0 = p1;
        }

        return p1;
    }
};

class chebyshev_type2_bp_filter : public bp_filter {
private:
    std::vector<fo_section> sections_;

    chebyshev_type2_bp_filter(){}
public:
    chebyshev_type2_bp_filter(unsigned int N,
            eq_double_t w0, eq_double_t wb,
            eq_double_t G, eq_double_t Gb, eq_double_t G0) {
        //Get number of analog sections
        unsigned int r = N%2;
        unsigned int L = (N - r)/2;

        //Convert gains to linear scale
        G = conversions::db_2_lin(G);
        Gb = conversions::db_2_lin(Gb);
        G0 = conversions::db_2_lin(G0);

        eq_double_t epsilon = pow((eq_double_t)((G*G - Gb*Gb)/(Gb*Gb - G0*G0)),0.5);
        eq_double_t g = pow((eq_double_t)(G),1.0/N);
        eq_double_t eu = pow(epsilon + sqrt(1 + epsilon*epsilon), 1.0/N);
        eq_double_t ew = pow(G0*epsilon + Gb*sqrt(1 + epsilon*epsilon), 1.0/N);
        eq_double_t a = (eu - 1.0/eu)/2.0;
        eq_double_t b = (ew - g*g/ew)/2.0;
        eq_double_t tetta_b = tan(wb/2);

        eq_double_t c0 = cos(w0);
        if (w0 == 0) c0 = 1;
        if (w0 == pi/2) c0=0;
        if (w0 == pi) c0 =- 1;

        //Calculate every section
        for(unsigned int i = 1; i <= L; i++) {
            eq_double_t ui = (2.0*i-1.0)/N;
            eq_double_t ci = cos(pi*ui/2.0);
            eq_double_t si = sin(pi*ui/2.0);
            eq_double_t Di = tetta_b*tetta_b + 2*a*si*tetta_b + a*a + ci*ci;

            sections_.push_back(chebyshev_type2_fo_section(a, ci, tetta_b, g, si, b, Di, c0));
        }
    }

    ~chebyshev_type2_bp_filter(){}

    eq_single_t process(eq_single_t in) {
        eq_single_t p0 = in;
        eq_single_t p1 = 0;

        //Process FO sections in serial connection
        for(unsigned int i = 0; i < sections_.size(); i++) {
            p1 = sections_[i].process(p0);
            p0 = p1;
        }

        return p1;
    }
};

// ------------ eq ------------
class eq {
private:
    conversions conv;
    eq_double_t sampling_frequency_;
    freq_grid freq_grid_;
    std::vector<eq_single_t> band_gains_;
    std::vector<bp_filter*> filters_;
    eq_type current_eq_type_;

    eq():conv(eq_min_max_gain_db){}
    eq(const eq&):conv(eq_min_max_gain_db){}

    const char *get_eq_text(eq_type type) {
        switch(type) {
            case none:
                return "not initialized";
            case butterworth:
                return "butterworth";
            case chebyshev1:
                return "chebyshev1";
            case chebyshev2:
                return "chebyshev2";
            default:
                return "none";
        }
    }

    void cleanup_filters_array() {
        for(unsigned int j = 0; j < get_number_of_bands(); j++)
            delete filters_[j];
    }

public:
    eq(freq_grid &fg, eq_type eq_t = none) : conv(eq_min_max_gain_db) {
        sampling_frequency_ = default_sample_freq_hz;
        freq_grid_ = fg;
        current_eq_type_ = eq_t;

        //Initialize filters array using fake objects
        for(unsigned int j = 0; j < get_number_of_bands(); j++) {
            bp_filter* flt = new dummy_bp_filter;
            filters_.push_back(flt);
        }

        if(eq_t != none)
            set_eq(freq_grid_, eq_t);
}
    ~eq(){cleanup_filters_array();}

    eq_error_t set_eq(freq_grid& fg, eq_type eqt) {
        band_gains_.clear();
        cleanup_filters_array();
        filters_.clear();

        freq_grid_ = fg;

        for(unsigned int i = 0; i < freq_grid_.get_number_of_bands(); i++) {

            eq_double_t wb = conversions::hz_2_rad(
                    freq_grid_.get_freqs()[i].max_freq - freq_grid_.get_freqs()[i].min_freq,
                    sampling_frequency_);

            eq_double_t w0 = conversions::hz_2_rad(
                    freq_grid_.get_freqs()[i].center_freq,
                    sampling_frequency_);

            switch(eqt) {
                case (butterworth): {
                    butterworth_bp_filter* bf = new butterworth_bp_filter(
                            default_eq_band_filters_order,
                            w0,
                            wb,
                            max_base_gain_db,
                            butterworth_band_gain_db,
                            min_base_gain_db
                            );

                    filters_.push_back(bf);
                    break;
                }

                case (chebyshev1): {
                    chebyshev_type1_bp_filter* cf1 = new chebyshev_type1_bp_filter(
                            default_eq_band_filters_order,
                            w0,
                            wb,
                            max_base_gain_db,
                            chebyshev1_band_base_gain_db,
                            min_base_gain_db
                            );

                    filters_.push_back(cf1);
                    break;
                }

                case (chebyshev2): {
                    chebyshev_type2_bp_filter* cf2 = new chebyshev_type2_bp_filter(
                            default_eq_band_filters_order,
                            w0,
                            wb,
                            max_base_gain_db,
                            chebyshev2_band_base_gain_db,
                            min_base_gain_db
                            );

                    filters_.push_back(cf2);
                    break;
                }

                default:
                    current_eq_type_ = none;
                    return invalid_input_data_error;

            }
            band_gains_.push_back(max_base_gain_db);
        }

        current_eq_type_ = eqt;
        return no_error;
    }

    eq_error_t set_eq(eq_type eqt)
    {
        return set_eq(freq_grid_, eqt);
    }

    eq_error_t set_sample_rate(eq_double_t sr) {
        eq_error_t err = no_error;
        sampling_frequency_ = sr;
        err = set_eq(freq_grid_, current_eq_type_);

        return err;
    }

    void change_params(std::vector<eq_single_t> band_gains) {
        band_gains_ = band_gains;
    }

    void change_band_param(unsigned int band_number, eq_single_t band_gain) {
        if(band_number < get_number_of_bands())
            band_gains_[band_number] = band_gain;
    }

    void change_band_param_db(unsigned int band_number, eq_single_t band_gain) {
        if(band_number < get_number_of_bands())
            band_gains_[band_number] = conv.fast_db_2_lin(band_gain);
    }
	
	eq_error_t sbs_process_band(unsigned int band_number, eq_single_t *in, eq_single_t *out) {
        if(band_number < get_number_of_bands())
            *out = band_gains_[band_number]*filters_[band_number]->process(*in);
		else
			return invalid_input_data_error;

        return no_error;
	}

     eq_error_t sbs_process(eq_single_t *in, eq_single_t *out) {
		eq_error_t err = no_error;
		eq_single_t acc_out = 0;		
        for(unsigned int j = 0; j < get_number_of_bands(); j++)
		{
			eq_single_t band_out = 0;
            err = sbs_process_band(j, in, &band_out);
			acc_out += band_out;
		}
		*out = acc_out;

        return err;
    }

    eq_type get_eq_type(){return current_eq_type_;}
    const char* get_string_eq_type(){return get_eq_text(current_eq_type_);}
    unsigned int get_number_of_bands(){return freq_grid_.get_number_of_bands();}
    const char* get_version(){return eq_version;}
};

} //namespace orfanidis_eq
#endif //ORFANIDIS_EQ_H_
