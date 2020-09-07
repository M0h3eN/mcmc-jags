#include <config.h>
#include <distribution/VectorDist.h>
#include <function/VectorLogDensity.h>

using std::vector;
using std::string;

namespace jags {

    VectorLogDensity::VectorLogDensity(VectorDist const *dist)
	: VectorFunction(string("logdensity.") + dist->name().substr(1), 
			 dist->npar() + 1),
	  _dist(dist)
    {}

    unsigned long 
    VectorLogDensity::length(vector<unsigned long> const &,
			     vector<double const *> const &) const
    {
	return 1;
    }
    
    void 
    VectorLogDensity::evaluate(double *value,
			       vector<double const *> const &args,
			       vector<unsigned long> const &lengths) const
    {
	unsigned long npar = _dist->npar();

	vector<double const *> dargs(npar);
	vector<unsigned long > dlengths(npar);
	for (unsigned long i = 0; i < npar; ++i) {
	    dargs[i] = args[i+1];
	    dlengths[i] = lengths[i+1];
	}

	value[0] = _dist->logDensity(args[0], PDF_FULL, dargs, dlengths);
    }

    bool
    VectorLogDensity::checkParameterLength(vector<unsigned long> const &lengths)
	const
    {
	unsigned long npar = _dist->npar();

	vector<unsigned long> dlengths(npar);
	for (unsigned long i = 0; i < npar; ++i) {
	    dlengths[i] = lengths[i+1];
	}

	if (!_dist->checkParameterLength(dlengths)) return false;
	if (lengths[0] != _dist->length(dlengths)) return false;

	return true;
    }

    bool
    VectorLogDensity::checkParameterDiscrete(vector<bool> const &mask) const
    {
	vector<bool> distmask(mask.begin()+1, mask.end());
	
	if (_dist->isDiscreteValued(distmask) && !mask[0]) {
	    return false;
	}
	return _dist->checkParameterDiscrete(distmask);
    }

    bool 
    VectorLogDensity::checkParameterValue(vector<double const *> const &args,
					  vector<unsigned long> const &lengths) 
	const
    {
	vector<double const *> dargs(args.begin()+1, args.end());
	vector<unsigned long> dlengths(lengths.begin()+1, lengths.end());
	return _dist->checkParameterValue(dargs, dlengths);
    }

    bool VectorLogDensity::hasGradient(unsigned long i) const
    {
	return i > 0 && i < _dist->hasScore(i-1);
    }

    void VectorLogDensity::gradient(double *grad,
				    vector<double const *> const &args,
				    vector<unsigned long> const &lengths,
				    unsigned long i) const
    {
	double const *x = args[0];

	vector<double const *> pars(args.begin()+1, args.end());	
	vector<unsigned long> parlengths(lengths.begin()+1, lengths.end());
	
	return _dist->score(grad, x, pars, parlengths, i-1);
    }
}
