#include <config.h>
#include <util/logical.h>
#include "Neg.h"

#include <cmath>

using std::vector;
using std::string;

namespace jags {
namespace base {

Neg::Neg () : ScalarFunction ("NEG", 1)
{
}

double Neg::evaluate(vector<double const*> const &args) const
{
    return -args[0][0];
}

bool Neg::isDiscreteValued(vector<bool> const &mask) const
{
  return mask[0];
}

bool Neg::isScale(vector<bool> const &, vector<bool> const &) const
{
    return true;
}

string Neg::deparse(vector<string> const &par) const
{
    return string("-") + par[0];
}

    bool Neg::hasGradient(unsigned long i) const
    {
	return i == 0;
    }
    
    double Neg::gradient(vector<double const*> const &args,
			 unsigned long) const
    {
	return -1;
    }
}}
