#include <config.h>
#include <distribution/RScalarDist.h>
#include <function/DFunction.h>

using std::vector;
using std::string;

namespace jags {

    DFunction::DFunction(RScalarDist const *dist)
	: DPQFunction(dist->name(), dist)
    {}
    
    double DFunction::evaluate(vector<double const *> const &args) const
    {
	double x = *args[0];
	vector<double const *> param(args.begin() + 1, args.end());
	
	return dist()->d(x, PDF_FULL, param, false);
    }

    bool 
    DFunction::checkParameterDiscrete(vector<bool> const &mask) const
    {
	if (dist()->isDiscreteValued() && !mask[0]) {
	    return false;
	}
	
	return checkDistParDiscrete(mask);
    }
    
    bool 
    DFunction::checkParameterValue(vector<double const *> const &args) const
    {
	return checkDistParValue(args);
    }

}
