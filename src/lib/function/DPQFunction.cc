#include <config.h>
#include <function/DPQFunction.h>
#include <distribution/RScalarDist.h>

using std::vector;
using std::string;

namespace jags {

    DPQFunction::DPQFunction(string const &name, RScalarDist const *dist) 
	: ScalarFunction(name, dist->npar() + 1), _dist(dist)
    {}
    
    RScalarDist const *DPQFunction::dist() const
    {
	return _dist;
    }

    bool
    DPQFunction::checkDistParDiscrete(vector<bool> const &mask) const
    {
	vector<bool> parmask(mask.begin()+1, mask.end());
	
	return _dist->checkParameterDiscrete(parmask);
    }

    bool
    DPQFunction::checkDistParValue(vector<double const *> const &args) const
    {
	vector<double const *> param(args.begin()+1, args.end());
	
	return _dist->checkParameterValue(param);
    }

}
