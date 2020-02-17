#include <map>
#include <string>

struct Var {
    const char *id;
    const char *name;
    float *var;
    int *ivar;
    bool *bvar;
    float val;
    float low;
    float up;
    const value_pair *values;
    Var(const char *_id, const char *_name, float *_var, float _val, float _low, float _up, const value_pair *_values)
	: id(_id), name(_name), var(_var), ivar(0), val(_val), low(_low), up(_up), values(_values) { *var = val; }
    Var(const char *_id, const char *_name, int *_ivar, int _val, int _low, int _up, const value_pair *_values)
	: id(_id), name(_name), var(0), ivar(_ivar), val(_val), low(_low), up(_up), values(_values) { *ivar = _val; }
    Var(const char *_id, const char *_name, bool *_bvar, int _val)
	: id(_id), name(_name), var(0), bvar(_bvar), val(_val), low(0), up(1), values(0) { *bvar = _val; }
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
    static float *registerFloatVar_(const char* id, const char* name, const char* tp,
				    const char* tooltip, float* var, float val,
				    float low, float up, float step, const value_pair* values);
    static int *registerIntVar_(const char* id, const char* name, const char* tp,
				const char* tooltip, int* var, int val,
				int low, int up, const value_pair* values);
    static bool *registerBoolVar_(const char* id, const char* name, const char* tp,
				  const char* tooltip, bool* var, bool val);
public:
    ParamRegImpl(VarMap *vars, PluginDef *p);
    ~ParamRegImpl();
};

VarMap *ParamRegImpl::vars = 0;

ParamRegImpl::ParamRegImpl(VarMap *v, PluginDef *p)
    : ParamReg() {
    vars = v;
    plugin = p;
    registerFloatVar = registerFloatVar_;
    registerIntVar = registerIntVar_;
    registerBoolVar = registerBoolVar_;
}

ParamRegImpl::~ParamRegImpl() {
}

float *ParamRegImpl::registerFloatVar_(const char* id, const char* name, const char* tp,
				       const char* tooltip, float* var, float val,
				       float low, float up, float step, const value_pair* values) {
    if (values) {
	int up = -1;
	for (const value_pair* p = values; p->value_id; ++p, ++up);
	low = 0;
    }
    vars->insert(std::pair<std::string,Var*>(id, new Var(id,name,var,val,low,up,values)));
    return var;
}

int *ParamRegImpl::registerIntVar_(const char *id, const char* name, const char* tp,
				   const char* tooltip, int *var, int val,
				   int low, int up, const value_pair* values) {
    if (values) {
	int up = -1;
	for (const value_pair* p = values; p->value_id; ++p, ++up);
	low = 0;
    }
    vars->insert(std::pair<std::string,Var*>(id, new Var(id,name,var,val,low,up,values)));
    return var;
}

bool *ParamRegImpl::registerBoolVar_(const char* id, const char* name, const char* tp,
				     const char* tooltip, bool* var, bool val) {
    vars->insert(std::pair<std::string,Var*>(id, new Var(id,name,var,val)));
    return var;
}

bool compare_plugin_version(PluginDef *p) {
   return p->version == PLUGINDEF_VERSION;
}
