#ifndef FUNC_NCOL_H_
#define FUNC_NCOL_H_

#include <function/ArrayFunction.h>

namespace jags {
namespace base {

    class NCol : public ArrayFunction
    {
    public:
	NCol();
	void evaluate(double *value, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long>> const &dims) 
	    const override;
	std::vector<unsigned long> 
	    dim(std::vector<std::vector<unsigned long>> const &dims,
		std::vector<double const *> const &values) const override;
	bool checkParameterDim(std::vector <std::vector<unsigned long>>
			       const &dims) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
    };

}}

#endif /* FUNC_NCOL_H_ */
