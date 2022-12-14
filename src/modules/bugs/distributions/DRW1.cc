#include <config.h>
#include "DRW1.h"
#include <util/dim.h>
#include <util/nainf.h>

#include <cmath>

#include <JRmath.h>
#include <rng/RNG.h>

using std::vector;
using std::string;
using std::abs;

#define TAU(par) (*par[0])
#define XCOORDS(par) (par[1])

namespace jags {
    namespace bugs {

	DRW1::DRW1()
	    : VectorDist("drw1", 2) 
	{}

	unsigned long DRW1::length(vector<unsigned long> const &len) const
	{
	    return len[1];
	}

	bool DRW1::checkParameterLength(vector<unsigned long> const &len) const
	{
	    return len[0] == 1 && len[1] > 1;
	}

	bool
	DRW1::checkParameterValue(vector<double const *> const &par,
				  vector<unsigned long> const &len) const
	{
	    unsigned long N = length(len);
	    double const *xcoords = XCOORDS(par);
	    double tau = TAU(par);

	    //Only regular random walks are supported
	    for (unsigned long i = 1; i < N; ++i) {
		double delta = xcoords[i] - xcoords[i-1];
		if (abs(delta - 1) > 1.0E-6) return false;
	    }

	    if (tau < 0) return false;

	    return true;
	}

	double DRW1::logDensity(double const *x,
				PDFType ,
				vector<double const *> const &par,
				vector<unsigned long> const &len) const
	{
	    double tau = TAU(par);
	    double sigma = 1/sqrt(tau);
	    
	    double loglik = 0.0;
	    unsigned long N = length(len);
	    for (unsigned long i = 1; i < N; i++) {
		loglik += dnorm(x[i] - x[i-1], 0, sigma, true);
	    }
	    return loglik;
	}

	void DRW1::randomSample(double *x,
				vector<double const *> const &par,
				vector<unsigned long> const &len,
				RNG *rng) const
	{
	    double tau = TAU(par);
	    double sigma = 1/sqrt(tau);
	    unsigned long N = length(len);
	    
	    double S = 0.0;
	    x[0] = 0;
	    for (unsigned long i = 1; i < N; i++) {
		x[i] = x[i-1] + rnorm(0, sigma, rng);
		S += x[i];
	    }
	    S /= N;
	    for (unsigned long i = 0; i < N; i++) {
		x[i] -= S;
	    }
	}

	/*
	void DRW1::randomSample(double *x, vector<bool> const &observed,
				vector<double const *> const &par,
				vector<unsigned long> const &len,
				RNG *rng) const
	{
	    double tau = TAU(par);
	    double sigma = 1/sqrt(tau);
	    unsigned long N = length(len);

	    if (allFalse(observed)) {
		randomSample(x, par, len, rng);
	    }
	    
	    //Left region
	    unsigned long l = 0;
	    if (!observed[0]) {
		while (l < N && !observed[l]) ++l;
		for (unsigned long i = l; i > 0; --i) {
		    x[i-1] = x[i] + sigma * rng->rnormal();
		}
	    }

	    //right region
	    unsigned long r = N-1;
	    if (!observed[N-1]) {
		while (r >= l && !observed[r]) --r;
		for (unsigned long i = r; r < N-1; ++r) {
		    x[i+1] = x[i] + sigma * rng->normal();
		}
	    }

	    //middle region
	    while (l < r) {
		unsigned long m = l + 1;
		while (m <= r) {
		    if (observed[m++]) break;
		}
		midsample(l, m, x, sigma);
	    }
	    
	    unsigned long l = 0, r = 0;
	    while (!observed[r]) {
		++r;
	    }
	    if (
	    double tau = TAU(par);
	    double sigma = 1/sqrt(tau);
	    unsigned long N = length(len);
	    
	    double S = 0.0;
	    x[0] = 0;
	    for (unsigned long i = 1; i < N; i++) {
		x[i] = x[i-1] + rnorm(0, sigma, rng);
		S += x[i];
	    }
	    S /= N;
	    for (unsigned long i = 0; i < N; i++) {
		x[i] -= S;
	    }
	}
	*/
	
	void DRW1::support(double *lower, double *upper,
			   vector<double const *> const &,
			   vector<unsigned long> const &len) const
	{
	    unsigned long N = length(len);
	    for (unsigned long i = 0; i < N; ++i) {
		lower[i] = JAGS_NEGINF;
		upper[i] = JAGS_POSINF;
	    }
	}

	bool DRW1::isSupportFixed(vector<bool> const &) const
	{
	    return true;
	}

	bool DRW1::fullRank() const
	{
	    return false;
	}

    }
}
