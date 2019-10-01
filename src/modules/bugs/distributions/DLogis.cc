#include <config.h>
#include "DLogis.h"

#include <JRmath.h>

using std::vector;

#define MU(par) (*par[0])
#define SCALE(par) (1 / *par[1])
#define TAU(par) (*par[1])

namespace jags {
namespace bugs {

DLogis::DLogis()
    : RScalarDist("dlogis", 2, DIST_UNBOUNDED)
{}

bool DLogis::checkParameterValue (vector<double const *> const &par) const
{
    return (TAU(par) > 0);
}

double 
DLogis::d(double x, PDFType,
vector<double const *> const &par, bool give_log) const
{
    return dlogis(x, MU(par), SCALE(par), give_log);
}

double 
DLogis::p(double q, vector<double const *> const &par, bool lower, 
	  bool give_log) const
{
    return plogis(q, MU(par), SCALE(par), lower, give_log);
}

double 
DLogis::q(double p, vector<double const *> const &par, bool lower, bool log_p)
    const
{
    return qlogis(p, MU(par), SCALE(par), lower, log_p);
}

double 
DLogis::r(vector<double const *> const &par, RNG *rng) const
{
    double ans = rlogis(MU(par), SCALE(par), rng);
    return ans;
}

    bool DLogis::hasScore(unsigned long i) const
    {
	return true;
    }
    
    double DLogis::score(double x, vector<double const *> const &par,
			 unsigned long i) const
    {
	double mu = MU(par);
	double tau = TAU(par);
	
	double y = 2 * plogis(x, mu, 1/tau, true, false) - 1;

	if (i == 0) {
	    return tau * y;
	}
	else if (i == 1) {
	    return 1/tau - (x - mu) * y;
	}
	else {
	    return 0;
	}
    }

}}
