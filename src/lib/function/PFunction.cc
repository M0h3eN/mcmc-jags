#include <config.h>
#include <function/PFunction.h>
#include <distribution/RScalarDist.h>

using std::vector;
using std::string;

namespace jags {

    PFunction::PFunction(RScalarDist const *dist)
	: DPQFunction(string("p") + dist->name().substr(1), dist)
    {}
    
    double PFunction::evaluate(vector<double const *> const &args) const
    {
	double x = *args[0];
	vector<double const *> param(args.begin() + 1, args.end());

	return dist()->p(x, param, true, false);
    }

    bool PFunction::checkParameterDiscrete(vector<bool> const &mask) const
    {
	if (dist()->isDiscreteValued() && !mask[0]) {
	    return false;
	}
	
	return checkDistParDiscrete(mask);
    }
    
    bool 
    PFunction::checkParameterValue(vector<double const *> const &args) const
    {
	return checkDistParValue(args);
    }

    bool PFunction::hasGradient(unsigned long i) const
    {
	return i == 0 && !dist()->isDiscreteValued();
    }

    double PFunction::gradient(vector<double const *> const &args,
			       unsigned long i) const
    {
	if (i != 0) return 0;
	
	double x = *args[0];
	vector<double const *> param(args.begin() + 1, args.end());
	
	return dist()->d(x, PDF_FULL, param, false);
    }
}
