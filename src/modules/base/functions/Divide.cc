#include <config.h>
#include "Divide.h"

using std::vector;

namespace jags {
namespace base {

    Divide::Divide () : Infix ("/")
    {
    }

    double Divide::evaluate(vector <double const *> const &args) const
    {
	return *args[0] / *args[1];
    }

    bool Divide::hasGradient(unsigned long i) const
    {
	return true;
    }
    
    double Divide::gradient(vector<double const *> const &args,
			    unsigned long i) const
    {
	double x = *args[0];
	double y = *args[1];

	if (i == 0) {
	    return 1/y;
	}
	else {
	    //i == 1
	    return -x/(y*y);
	}
    }
    
    bool Divide::checkParameterValue(vector<double const*> const &args) const
    {
	return *args[1] != 0;
    }

    bool 
    Divide::isScale(vector<bool> const &mask, vector<bool> const &fix) const
    {
	if (mask[1])
	    return false; //No reciprocal terms

	return fix.empty() || fix[1];
    }

    bool 
    Divide::isPower(vector<bool> const &, vector<bool> const &) const
    {
	return true;
    }
	
}}
