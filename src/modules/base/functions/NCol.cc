#include <config.h>

#include "NCol.h"
#include <util/dim.h>
#include <util/integer.h>

using std::vector;

namespace jags {
namespace base {

    NCol::NCol()
	: ArrayFunction("ncol", 1)
    {
    }
    
    void 
    NCol::evaluate (double *value, vector<double const *> const &,
		    vector<vector<unsigned long>> const &dims) const
    {
	value[0] = dims[0][1];
    }
    
    vector<unsigned long> 
    NCol::dim (vector<vector<unsigned long>> const &dims,
	      vector<double const *> const &) const
    {
	return vector<unsigned long>(1, 1);
    }
    
    bool 
    NCol::checkParameterDim (vector<vector<unsigned long>> const &dims) const
    {
	return dims[0].size() == 2;
    }
    
    bool NCol::isDiscreteValued(vector<bool> const &mask) const
    {
	return true;
    }
}}
