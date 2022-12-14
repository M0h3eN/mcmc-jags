#include <config.h>
#include <distribution/Distribution.h>
#include <util/dim.h>

using std::vector;
using std::string;

namespace jags {

Distribution::Distribution(string const &name, unsigned long npar)
    : _name(name), _npar(npar)
{
}

Distribution::~Distribution()
{
}

string const &Distribution::name() const
{
  return _name;
}

string Distribution::alias() const
{
    return "";
}

unsigned long Distribution::npar () const
{
  return _npar;
}

bool Distribution::isLocationParameter(unsigned int) const
{
    return false;
}

bool Distribution::isScaleParameter(unsigned int) const
{
    return false;
}

bool Distribution::isDiscreteValued(vector<bool> const &) const
{
    return false;
}

bool Distribution::canBound() const
{
    return false;
}

bool Distribution::checkParameterDiscrete(vector<bool> const &) const
{
    return true;
}

    bool Distribution::fullRank() const
    {
	return true;
    }

    bool Distribution::hasScore(unsigned long) const
    {
	return false;
    }
    
} //namespace jags
