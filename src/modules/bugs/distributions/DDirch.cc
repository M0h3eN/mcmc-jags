#include <config.h>
#include "DDirch.h"
#include <util/dim.h>
#include <util/nainf.h>

#include <cmath>
#include <limits>

#include <JRmath.h>
#include <rng/RNG.h>

using std::vector;
using std::string;
using std::numeric_limits;

#define ALPHA(par) (par[0])
#define LENGTH(len) (len[0])

/* The Dirichlet distribution is extended to allow zero shape parameters.
   These represent structural zeros: when x ~ ddirch(alpha) is forward
   sampled, x[i] = 0 when alpha[i] = 0. To avoid trapping states in the
   model, structural zeros are only allowed when the alpha parameter
   is fixed.
*/

namespace jags {
namespace bugs {

DDirch::DDirch()
  : VectorDist("ddirch", 1) 
{}

string DDirch::alias() const
{
    return "ddirich";
}

unsigned long DDirch::length(vector<unsigned long> const &len) const
{
    return LENGTH(len);
}

bool DDirch::checkParameterLength(vector<unsigned long> const &len) const
{
    return LENGTH(len) > 1;
}

bool
DDirch::checkParameterValue(vector<double const *> const &par,
                            vector<unsigned long> const &len) const
{
    double const *alpha = ALPHA(par);
    unsigned long length = LENGTH(len);

    bool has_nonzero_alpha = false;
    for (unsigned long i = 0; i < length; i++) {
	if (alpha[i] < 0) {
	    return false;
	}
	if (alpha[i] > 0) {
	  has_nonzero_alpha = true;
	}
    }
    return has_nonzero_alpha;
}

double DDirch::logDensity(double const *x, PDFType type,
			  vector<double const *> const &par,
			  vector<unsigned long> const &len) const
{
    double const *alpha = ALPHA(par);
    unsigned long length = LENGTH(len);
    
    double loglik = 0.0;
    for (unsigned long i = 0; i < length; i++) {
	if (alpha[i] == 0) {
	    if (x[i] > 0)
		return JAGS_NEGINF;
	}
	else {
	    loglik += (alpha[i] - 1) * log(x[i]);
	}
    }

    if (type != PDF_PRIOR) {
	//Need to calculate normalizing constant
	double alphasum = 0.0;
	for (unsigned long i = 0; i < length; i++) {
	    if (alpha[i] != 0) {
		loglik -= lgammafn(alpha[i]);
		alphasum += alpha[i];
	    }
	}
	loglik += lgammafn(alphasum);
    }

    return loglik;
}

void DDirch::randomSample(double *x,
                          vector<double const *> const &par,
                          vector<unsigned long> const &len,
			  RNG *rng) const
{
    double const *alpha = ALPHA(par);
    unsigned long length = LENGTH(len);
    
    /* Generate independent gamma random variables, then normalize
       to create Dirichlet distribution.
    */
    double sumx = 0.0;
    for (unsigned long i = 0; i < length; i++) {
	x[i] = (alpha[i]==0) ? 0 : rgamma(alpha[i], 1, rng);
	sumx += x[i];
    }
    for (unsigned long j = 0; j < length; j++) {
	x[j] /= sumx;
    }
}

    void DDirch::randomSample(double *x, vector<bool> const &observed,
			      vector<double const *> const &par,
			      vector<unsigned long> const &len,
			      RNG *rng) const
    {
	double const *alpha = ALPHA(par);
	unsigned long length = LENGTH(len);

	//Find sum constraint given observed elements
	double S = 1.0;
	for (unsigned long i = 0; i < observed.size(); ++i) {
	    if (observed[i]) {
		S -= x[i];
	    }
	}
	if (S < 0) S = 0.0;
	
	// Generate independent gamma random variables, then normalize
	double sumx = 0.0;
	for (unsigned long i = 0; i < length; i++) {
	    if (!observed[i]) {
		x[i] = (alpha[i]==0) ? 0 : rgamma(alpha[i], 1, rng);
		sumx += x[i];
	    }
	}
	
	for (unsigned long j = 0; j < length; j++) {
	    if (!observed[j]) {
		x[j] *= S/sumx;
	    }
	}
    }

void DDirch::support(double *lower, double *upper,
		vector<double const *> const &par,
		vector<unsigned long> const &len) const
{
    unsigned long length = LENGTH(len);
    for (unsigned long i = 0; i < length; ++i) {
	lower[i] = 0;
	if (ALPHA(par)[i] == 0)
	    upper[i] = 0;
	else
	    upper[i] = JAGS_POSINF;
    }
}

bool DDirch::isSupportFixed(vector<bool> const &fixmask) const
{
    return fixmask[0];
}

    bool DDirch::fullRank() const
    {
	return false;
    }

double DDirch::KL(vector<double const *> const &par0,
		  vector<double const *> const &par1,
		  vector<unsigned long> const &len) const
{
    //Generalization of the Kullback-Leibler divergence for the beta
    //distribution. We also have to take care of structural zeros as
    //in DCat

    unsigned long N = LENGTH(len);

    double S0 = 0, S1 = 0, y = 0;
    for (unsigned long i = 0; i < N; ++i) {
	double a1 = ALPHA(par0)[i];
	double a2 = ALPHA(par1)[i];

	if (a1 == 0) {
	    S1 += a2;
	}
	else if (a2 == 0) {
	    return JAGS_POSINF;
	}
	else {
	    y += (a1 - a2) * digamma(a1) + lgammafn(a2) - lgammafn(a1);
	    S0 += a1;
	    S1 += a2;
	}
    }
    y -= (S0 - S1) * digamma(S0) + lgammafn(S1) - lgammafn(S0);

    return y;
}

    bool DDirch::hasScore(unsigned long i) const
    {
	return i == 0;
    }
    
    void DDirch::score(double *score, double const *x,
		       vector<double const *> const &par,
		       vector<unsigned long> const &len,
		       unsigned long i) const
    {
	if (i != 0) return;
	
	double const *alpha = ALPHA(par);
	unsigned long length = LENGTH(len);
    
	for (unsigned long j = 0; j < length; j++) {
	    if (alpha[j] > 0) {
		score[j] += log(x[j]);
	    }
	    else if (x[j] > 0) {
		score[j] = numeric_limits<double>::quiet_NaN();
	    }
	}

	double alphasum = 0.0;
	for (unsigned long j = 0; j < length; j++) {
	    if (alpha[j] != 0) {
		score[j] -= digamma(alpha[j]);
		alphasum += alpha[j];
	    }
	}
	for (unsigned long j = 0; j < length; j++) {
	     score[j] += digamma(alphasum);
	}
    }

}}
