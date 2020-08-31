#ifndef MAT_MULT_H_
#define MAT_MULT_H_

#include <function/ArrayFunction.h>

namespace jags {
namespace bugs {

    class MatMult : public ArrayFunction
    {
    public:
	MatMult();
	void evaluate(double *value, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long>> const &dims) 
	    const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *grad, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims,
		      unsigned long i) const override;
	std::vector<unsigned long> 
	    dim(std::vector<std::vector<unsigned long>> const &dims,
		std::vector<double const *> const &values) const override;
	bool checkParameterDim(std::vector <std::vector<unsigned long>>
			       const &dims) const override;
	bool isScale(std::vector<bool> const &mask, 
		     std::vector<bool> const &fix) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
    };

}}

#endif /* MAT_MULT_H_ */
