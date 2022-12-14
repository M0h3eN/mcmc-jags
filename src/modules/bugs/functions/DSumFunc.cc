#include <config.h>
#include <util/logical.h>
#include <util/dim.h>
#include <util/logical.h>
#include "DSumFunc.h"

using std::vector;

namespace jags {
namespace bugs {

    DSumFunc::DSumFunc()
	: ArrayFunction("dsum", 0)
    {
    }
    
    void DSumFunc::evaluate(double *x,
			    vector<double const *> const &args,
			    vector<vector<unsigned long> > const &dims) const
    {
	unsigned long length = product(dims[0]);
	for (unsigned long i = 0; i < length; ++i) {
	    x[i] = 0;
	    for (unsigned long j = 0; j < args.size(); ++j) {
		x[i] += args[j][i];
	    }
	}
    }

    bool DSumFunc::hasGradient(unsigned long i) const
    {
	return true;
    }
    
    void DSumFunc::gradient(double *grad, vector <double const *> const &args,
			    vector<vector<unsigned long> > const &dims,
			    unsigned long i) const
    {
	if (i >= args.size()) return;
	
	unsigned long P = product(dims[0]);
	for (unsigned long p = 0; p < P; ++p) {
	    grad[p + P * p] += 1;
	}
    }
    
    bool DSumFunc::isDiscreteValued(vector<bool> const &mask) const
    {
	return allTrue(mask);
    }

    bool 
    DSumFunc::checkParameterDim(vector<vector<unsigned long> > const &dims) const
    {
	if (dims.empty()) return false;
	if (isFlat(dims[0])) return false;
	for (unsigned long j = 1; j < dims.size(); ++j) {
	    if (dims[j] != dims[0]) return false;
	}
	return true;
    }

    vector<unsigned long>  
    DSumFunc::dim(vector<vector<unsigned long> > const &dims,
		  vector<double const *> const &) const
    {
	return dims[0];
    }

    bool DSumFunc::isLinear(vector<bool> const &, vector<bool> const &) const
    {
	return true;
    }

    bool DSumFunc::isScale(vector<bool> const &mask, 
			   vector<bool> const &) const
    {
	return allTrue(mask);
    }

}}
