#include <map>
#include <string>

struct Var {
    const char *id;
    const char *name;
    float *var;
    float val;
    float low;
    float up;
    Var(const char *_id, const char *_name, float *_var, float _val, float _low, float _up)
	: id(_id), name(_name), var(_var), val(_val), low(_low), up(_up) {}
};

class VarMap: public std::map<std::string,Var*> {
public:
    VarMap() {}
    ~VarMap();
};

typedef VarMap::iterator variter;

VarMap::~VarMap() {
    for (variter i = begin(); i != end(); ++i) {
	delete i->second;
    }
}

class ParamRegImpl: public ParamReg {
private:
    static VarMap *vars;
    static float *registerVar_(const char* id, const char* name, const char* tp,
			       const char* tooltip, float* var, float val,
			       float low, float up, float step);
    static void registerBoolVar_(const char* id, const char* name, const char* tp,
				 const char* tooltip, bool* var, bool val);
    static void registerNonMidiVar_(const char * id, bool*var, bool preset);
    static void registerEnumVar_(const char *id, const char* name, const char* tp,
				 const char* tooltip, const value_pair* values, float *var, float val,
				 float low, float up, float step);
    static void registerIEnumVar_(const char *id, const char* name, const char* tp,
				  const char* tooltip, const value_pair* values, int *var, int val);
    static void registerUEnumVar_(const char *id, const char* name, const char* tp,
				  const char* tooltip, const value_pair* values,
				  unsigned int *var, unsigned int std);
public:
    ParamRegImpl(VarMap *vars, PluginDef *p);
    ~ParamRegImpl();
};

VarMap *ParamRegImpl::vars = 0;

ParamRegImpl::ParamRegImpl(VarMap *v, PluginDef *p)
    : ParamReg() {
    vars = v;
    plugin = p;
    registerVar = registerVar_;
    registerBoolVar = registerBoolVar_;
    registerNonMidiVar = registerNonMidiVar_;
    registerEnumVar = registerEnumVar_;
    registerIEnumVar = registerIEnumVar_;
    registerUEnumVar = registerUEnumVar_;
}

ParamRegImpl::~ParamRegImpl() {
}

float *ParamRegImpl::registerVar_(const char* id, const char* name, const char* tp,
				  const char* tooltip, float* var, float val,
				  float low, float up, float step) {
    vars->insert(std::pair<std::string,Var*>(id, new Var(id,name,var,val,low,up)));
    return var;
}

void ParamRegImpl::registerBoolVar_(const char* id, const char* name, const char* tp,
				    const char* tooltip, bool* var, bool val) {}
void ParamRegImpl::registerNonMidiVar_(const char * id, bool*var, bool preset) {}
void ParamRegImpl::registerEnumVar_(const char *id, const char* name, const char* tp,
				   const char* tooltip, const value_pair* values, float *var, float val,
				   float low, float up, float step) {}
void ParamRegImpl::registerIEnumVar_(const char *id, const char* name, const char* tp,
				   const char* tooltip, const value_pair* values, int *var, int val) {}
void ParamRegImpl::registerUEnumVar_(const char *id, const char* name, const char* tp,
				     const char* tooltip, const value_pair* values,
				     unsigned int *var, unsigned int std) {}
