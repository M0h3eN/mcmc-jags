#include <config.h>

#include "NRow.h"
#include <util/dim.h>
#include <util/integer.h>

using std::vector;

namespace jags {
namespace base {

    NRow::NRow()
	: ArrayFunction("nrow", 1)
    {
    }
    
    void 
    NRow::evaluate (double *value, vector<double const *> const &,
		   vector<vector<unsigned long>> const &dims) const
    {
	value[0] = dims[0][0];
    }
    
    vector<unsigned long> 
    NRow::dim (vector<vector<unsigned long>> const &dims,
	      vector<double const *> const &) const
    {
	return vector<unsigned long>(1, 1);
    }
    
    bool 
    NRow::checkParameterDim (vector<vector<unsigned long>> const &dims) const
    {
	return dims[0].size() == 2;
    }
    
    bool NRow::isDiscreteValued(vector<bool> const &mask) const
    {
	return true;
    }
}}
