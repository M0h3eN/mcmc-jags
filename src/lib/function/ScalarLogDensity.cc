#include <config.h>
#include <distribution/ScalarDist.h>
#include <function/ScalarLogDensity.h>

using std::vector;
using std::string;

namespace jags {

    ScalarLogDensity::ScalarLogDensity(ScalarDist const *dist)
	: ScalarFunction(string("logdensity.") + dist->name().substr(1), 
			 dist->npar() + 1),
	  _dist(dist)
    {}
    
    double ScalarLogDensity::evaluate(vector<double const *> const &args) const
    {
	vector<double const *> param(args.begin()+1, args.end());
	return _dist->logDensity(*args[0], PDF_FULL, param, nullptr, nullptr);
    }

    bool
    ScalarLogDensity::checkParameterDiscrete(vector<bool> const &mask) const
    {
	vector<bool> distmask(mask.begin()+1, mask.end());
	
	if (_dist->isDiscreteValued(distmask) && !mask[0]) {
	    return false;
	}
	return _dist->checkParameterDiscrete(distmask);
    }

    bool 
    ScalarLogDensity::checkParameterValue(vector<double const *> const &args) 
	const
    {
	vector<double const *> param(args.begin()+1, args.end());
	return _dist->checkParameterValue(param);
    }

    bool ScalarLogDensity::hasGradient(unsigned long i) const
    {
	return i > 0 && i < _dist->hasScore(i-1);
    }

    double ScalarLogDensity::gradient(vector<double const *> const &args,
				      unsigned long i) const
    {
	double x = *args[0];
	vector<double const *> params(args.begin()+1, args.end());
	
	return _dist->score(x, params, i - 1);
    }
    
}
