#include <config.h>

#include "Dim.h"
#include <util/dim.h>
#include <util/integer.h>

using std::vector;

namespace jags {
namespace base {

    Dim::Dim()
	: ArrayFunction("dim", 1)
    {
    }
    
    void 
    Dim::evaluate (double *value, vector<double const *> const &,
		   vector<vector<unsigned long>> const &dims) const
    {
	copy(dims[0].begin(), dims[0].end(), value);
    }
    
    vector<unsigned long> 
    Dim::dim (vector<vector<unsigned long>> const &dims,
	      vector<double const *> const &) const
    {
	vector<unsigned long> ans(1, dims.size());
	return ans;
    }
    
    bool 
    Dim::checkParameterDim (vector<vector<unsigned long>> const &dims) const
    {
	return true;
    }
    
    bool Dim::isDiscreteValued(vector<bool> const &mask) const
    {
	return true;
    }
}}
