#include <config.h>
#include "Tanh.h"

#include <cmath>

using std::vector;
using std::tanh;

namespace jags {
namespace bugs {

    Tanh::Tanh ()
	: ScalarFunction ("tanh", 1)
    {
    }

    double Tanh::evaluate(vector<double const *> const &args) const
    {
	return tanh(*args[0]);
    }

    bool Tanh::hasGradient(unsigned long i) const
    {
	return i == 0;
    }
    
    double Tanh::gradient(vector<double const *> const &args,
			  unsigned long i) const
    {
	double y = cosh(*args[0]);
	return 1/(y*y);
    }

}}
