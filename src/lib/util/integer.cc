#include <config.h>

#include <util/integer.h>

//#include <stdexcept>
#include <cmath>
#include <cfloat>
#include <climits>
//#include <string>

using std::fabs;
using std::sqrt;
using std::round;

/*
  Numerical tolerance for values close to an integer. Following R
  we use the square root of the machine precision.
*/
static const double eps = sqrt(DBL_EPSILON);

/* 
   Largest integer that can be represented exactly in a 64-bit
   double. 1 bit for the sign and 11 bits for the exponent leaves 52
   bits for the fraction.  Hence up to 2^53-1 can be represented
   exactly and 2^53 is even so there is no loss of precision from the
   missing last bit.
*/
static const unsigned long JAGS_BIGINT = 9007199254740992UL;

namespace jags {

    int asInteger(double fval)
    {
	if (fval < INT_MIN) {
	    return INT_MIN;
	}
	else if (fval > INT_MAX) {
	    return INT_MAX;
	}
	else {
	    return static_cast<int>(round(fval));
	}
    }

    bool checkInteger(double fval)
    {
	return fabs(fval - round(fval)) < eps;
    }
    
    unsigned long asULong(double fval)
    {
	if (fval < 0) {
	    return 0UL;
	}
	else if (fval > JAGS_BIGINT) {
	    return JAGS_BIGINT;
	}
	else {
	    return static_cast<unsigned long>(round(fval));
	}
    }
    
}
