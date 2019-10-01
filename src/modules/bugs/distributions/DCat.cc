#include <config.h>
#include "DCat.h"
#include <rng/RNG.h>
#include <util/dim.h>
#include <util/nainf.h>
#include <module/ModuleError.h>

#include <cfloat>
#include <algorithm>
#include <cmath>
#include <numeric>

#include <JRmath.h>

using std::min;
using std::max;
using std::vector;
using std::max_element;
using std::accumulate;
using std::fill;

#define PROB(par) (par[0])
#define NCAT(lengths) (lengths[0])

namespace jags {
namespace bugs {

DCat::DCat()
    : VectorDist("dcat", 1) 
{}

bool DCat::isDiscreteValued(vector<bool> const &) const
{
    return true;
}

bool DCat::checkParameterValue(vector<double const *> const &par,
			       vector<unsigned long> const &lengths) const
{
    bool nz = false;
    for (unsigned long i = 0; i < NCAT(lengths); i++) {
	if (PROB(par)[i] < 0.0) {
	    return false; 
	}
	if (PROB(par)[i] > 0.0) {
	    nz = true; //at least one non-zero probability
	}
    }
    return nz;
}

double DCat::logDensity(double const *x, PDFType type,
			vector<double const *> const &par,
			vector<unsigned long> const &lengths) const
{
    unsigned long y = static_cast<unsigned long>(*x);
    if (y < 1 || y > NCAT(lengths)) {
	return JAGS_NEGINF;
    }
    
    if (type == PDF_PRIOR) {
	//No need to calculate the normalizing constant
	return log(PROB(par)[y-1]);
    }
    else {
	//Need to normalize the log density
	double sump = 0.0;
	for (unsigned long i = 0; i < NCAT(lengths); i++) {
	    sump += PROB(par)[i];
	}
	return log(PROB(par)[y-1]) - log(sump);
    }
}

void DCat::randomSample(double *x,
			vector<double const *> const &par,
			vector<unsigned long> const &lengths,
			RNG *rng) const
{
    double sump = 0;
    unsigned long i = 0;

    for ( ; i < NCAT(lengths); ++i) {
	sump += PROB(par)[i];
    }
    double p = sump * rng->uniform();    

    for ( ; i > 1; --i) {
	sump -= PROB(par)[i-1];
	if (sump <= p) 
            break;
    }
    *x  = i;
}

    void DCat::randomSample(double *x, vector<bool> const &observed, 
			    vector<double const *> const &par,
			    vector<unsigned long> const &lengths,
			    RNG *rng) const
    {
	if (!observed[0]) {
	    randomSample(x, par, lengths, rng);
	}
    }
    
void DCat::support(double *lower, double *upper,
	           vector<double const *> const &,
	           vector<unsigned long> const &lengths) const
{
    *lower = 1;
    *upper = NCAT(lengths);
}

bool DCat::isSupportFixed(vector<bool> const &) const
{
    return true;
}

bool DCat::checkParameterLength(vector<unsigned long> const &lengths) const
{
    return NCAT(lengths) > 0;
}

unsigned long DCat::length(vector<unsigned long> const &) const
{
    return 1;
}

    double DCat::KL(vector<double const *> const &par0,
		    vector<double const *> const &par1,
		    vector<unsigned long> const &lengths) const
    {
	double psum0 = 0, psum1 = 0, y = 0;
	for (unsigned long i = 0; i < NCAT(lengths); ++i) {
	    double p0 = PROB(par0)[i];
	    double p1 = PROB(par1)[i];
	    if (p0 == 0) {
		psum1 += p1;
	    }
	    else if (p1 == 0) {
		return JAGS_POSINF;
	    }
	    else {
		y += p0 * (log(p0) - log(p1));
		psum0 += p0;
		psum1 += p1;
	    }
	}
	y /= psum0;
	y -= (log(psum0) - log(psum1));
	return y;
    }

    bool DCat::hasScore(unsigned long i) const
    {
	true;
    }
    
    void DCat::score(double *s, double const *x,
		     vector<double const *> const &par,
		     vector<unsigned long> const &lengths,
		     unsigned long i) const
    {
	double const *prob = PROB(par);
	unsigned long N = NCAT(lengths);
	
	double S = accumulate(prob, prob + N, 0.0);
	fill(s, s+N, -1/S);

	unsigned long y = static_cast<unsigned long>(*x) - 1;
	s[y] += 1/prob[y];
    }


}}
