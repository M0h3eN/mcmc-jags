#include <config.h>
#include "Sum.h"
#include <util/logical.h>

using std::vector;

namespace jags {
namespace bugs {

    Sum::Sum () : ScalarVectorFunction("sum", 0)
    {
    }

    double Sum::scalarEval(vector <double const *> const &args,
			   vector<unsigned long> const &lengths) const
    {
	double value = 0;
	for (unsigned long j = 0; j < args.size(); ++j) {
	    for (unsigned long i = 0; i < lengths[j]; ++i) {
		value += args[j][i];
	    }
	}
	return value;
    }

    bool Sum::hasGradient(unsigned long i) const
    {
	return true;
    }
    
    void Sum::gradient(double *grad, vector<double const *> const &args,
		       vector<unsigned long> const &lengths,
		       unsigned long i) const
    {
	if (i >= args.size()) return;
	
	for (unsigned long j = 0; j < lengths[i]; ++j) {
	    grad[j] += 1.0;
	}
    }
    
    bool Sum::isDiscreteValued(vector<bool> const &mask) const
    {
	return allTrue(mask);
    }

    bool
    Sum::isAdditive(vector<bool> const &mask, vector<bool> const &fixed) const
    {
	//Only one argument may be additive. 
	bool found = false;
	for (unsigned long i = 0; i < mask.size(); ++i) {
	    if (mask[i]) {
		if (found) return false;
		else found = true;
	    }
	    if (!fixed.empty() && !fixed[i]) {
		return false;
	    }
	}
	return found;
    }
    
    bool Sum::isScale(vector<bool> const &mask, vector<bool> const &) const
    {
	return allTrue(mask);
    }

    bool Sum::isLinear(vector<bool> const &, vector<bool> const &) const
    {
	return true;
    }

}}
