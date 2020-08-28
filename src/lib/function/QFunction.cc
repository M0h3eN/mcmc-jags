#include <config.h>
#include <function/QFunction.h>
#include <distribution/RScalarDist.h>

using std::vector;
using std::string;

namespace jags {

    QFunction::QFunction(RScalarDist const *dist)
	: DPQFunction(string("q") + dist->name().substr(1), dist)
    {}
    
    double QFunction::evaluate(vector<double const *> const &args) const
    {
	double x = *args[0];
	vector<double const *> param(args.begin() + 1, args.end());
	
	return dist()->q(x, param, true, false);
    }

    bool QFunction::checkParameterValue(vector<double const*> const &args) const
    {
	if (*args[0] < 0 || *args[0] > 1) return false;

	return checkDistParValue(args);
    }

    bool QFunction::checkParameterDiscrete(vector<bool> const &mask) const
    {
	return checkDistParDiscrete(mask);
    }
    
}
