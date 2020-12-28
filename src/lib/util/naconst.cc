#include <config.h>
#include <util/nainf.h>

#include <cmath>
#include <limits>

using std::numeric_limits;
using std::isfinite;
using std::isnan;

#ifdef WORDS_BIGENDIAN
static const int hw = 0;
static const int lw = 1;
#else  /* !WORDS_BIGENDIAN */
static const int hw = 1;
static const int lw = 0;
#endif /* WORDS_BIGENDIAN */

/* 
   Missing value JAGS_NA is borrowed from the R project, where NA is
   defined to be a particular quite NaN
*/
   
typedef union
{
    double value;
    unsigned int word[2];
} ieee_double;

static double jags_NAValue()
{
    volatile ieee_double x;
    x.word[hw] = 0x7ff00000;
    x.word[lw] = 1954;
    return x.value;
}

const double JAGS_NA = jags_NAValue();
const double JAGS_NAN = numeric_limits<double>::quiet_NaN();
const double JAGS_POSINF = numeric_limits<double>::infinity();
const double JAGS_NEGINF = -numeric_limits<double>::infinity();

int jags_isna(double x)
{
    if (isnan(x)) {
        ieee_double y;
        y.value = x;
        return (y.word[lw] == 1954);
    }
    return 0;
}
