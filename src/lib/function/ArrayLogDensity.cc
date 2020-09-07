#include <config.h>
#include <distribution/ArrayDist.h>
#include <function/ArrayLogDensity.h>
#include <util/dim.h>

using std::vector;
using std::string;

namespace jags {

    ArrayLogDensity::ArrayLogDensity(ArrayDist const *dist)
	: ArrayFunction(string("logdensity.") + dist->name().substr(1), 
			 dist->npar() + 1),
	  _dist(dist)
    {}
    
    vector<unsigned long> ArrayLogDensity::dim(
	vector<vector<unsigned long> > const &,
	vector<double const *> const &) const
    {
	return vector<unsigned long>(1, 1);
    }

    void ArrayLogDensity::evaluate(
	double *value,
	vector<double const *> const &args,
	vector<vector<unsigned long> > const &dims) const
    {
	unsigned long npar = _dist->npar();

	vector<double const *> dargs(npar);
	vector<vector<unsigned long> > ddims(npar);
	for (unsigned long i = 0; i < npar; ++i) {
	    dargs[i] = args[i+1];
	    ddims[i] = dims[i+1];
	}

	value[0] = _dist->logDensity(args[0], PDF_FULL, dargs, ddims);
    }

    

    bool
    ArrayLogDensity::checkParameterDim(vector<vector<unsigned long> > const &dim)
	const
    {
	unsigned long npar = _dist->npar();

	vector<vector<unsigned long> > ddim(npar);
	for (unsigned long i = 0; i < npar; ++i) {
	    ddim[i] = dim[i+1];
	}

	if (!_dist->checkParameterDim(ddim)) return false;
	if (dim[0] != _dist->dim(ddim)) return false;

	return true;
    }

    bool
    ArrayLogDensity::checkParameterDiscrete(vector<bool> const &mask) const
    {
	vector<bool> distmask(mask.begin()+1, mask.end());
	
	if (_dist->isDiscreteValued(distmask) && !mask[0]) {
	    return false;
	}
	return _dist->checkParameterDiscrete(distmask);
    }

    bool 
    ArrayLogDensity::checkParameterValue(vector<double const *> const &args,
					 vector<vector<unsigned long>> const &dims) 
	const
    {
	vector<double const *> dargs(args.begin()+1, args.end());
	vector<vector<unsigned long>> ddims(dims.begin()+1, dims.end());
	return _dist->checkParameterValue(dargs, ddims);
    }
    
    bool ArrayLogDensity::hasGradient(unsigned long i) const
    {
	return i > 0 && i < _dist->hasScore(i-1);
    }

    void ArrayLogDensity::gradient(double *grad, vector<double const *> const &args,
				   vector<vector<unsigned long>> const &dims,
				   unsigned long i) const
    {
	double const *x = args[0];

	vector<double const *> pars(args.begin()+1, args.end());	
	vector<vector<unsigned long>> pardims(dims.begin()+1, dims.end());
	
	return _dist->score(grad, x, pars, pardims, i-1);
    }

}
