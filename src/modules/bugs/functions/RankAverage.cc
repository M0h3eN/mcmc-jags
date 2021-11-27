#include <config.h>
#include <util/dim.h>
#include "RankAverage.h"

#include <algorithm>

using std::vector;
using std::stable_sort;

static inline bool lt_doubleptr (double const *arg1, double const *arg2) {
  return *arg1 < *arg2;
}

namespace jags {
namespace bugs {

    RankAverage::RankAverage ()
	: VectorFunction ("rank.average", 1)
    {
    }

    void RankAverage::evaluate(double *value,
			       vector<double const *> const &args,
			       vector<unsigned long> const &lengths) const
    {
	unsigned long N = lengths[0];

	//Create a vector of pointers to the elements of arg and sort it
	vector<double const*> argptrs(N);
	for (unsigned long i = 0; i < N; ++i) {
	    argptrs[i] = args[0] + i;
	}
	stable_sort(argptrs.begin(), argptrs.end(), lt_doubleptr);

	unsigned long i = 0;
	while (i < N) {
	    // Look for tied values
	    unsigned long j = i;
	    while (++j < N) {
		if (*argptrs[j] > *argptrs[i])
		    break; // No more ties
	    }
	    // Average rank over tied values
	    double rank = (1.0 + i + j)/2.0;
	    // Set tied values to the average rank
	    for (unsigned long k = i; k < j; k++) {
		value[argptrs[k] - args[0]] = rank;
	    }
	    i = j;
	}
    }

    unsigned long RankAverage::length (vector<unsigned long> const &lengths,
				       vector<double const *> const &) const
    {
	return lengths[0];
    }

}}
