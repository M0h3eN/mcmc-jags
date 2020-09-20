#include <config.h>
#include "Length.h"

using std::vector;

namespace jags {
    namespace base {

	Length::Length ()
	    : ScalarVectorFunction("length", 1)
	{
	}
	
	double Length::scalarEval(vector<double const *> const &args,
				  vector<unsigned long> const &lengths) const
	{
	    return lengths[0];
	}
	
	bool Length::isDiscreteValued(vector<bool> const &) const
	{
	    return true;
	}
	
    }
}
