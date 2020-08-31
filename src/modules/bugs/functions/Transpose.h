#ifndef TRANSPOSE_H_
#define TRANSPOSE_H_

#include <function/ArrayFunction.h>

namespace jags {
namespace bugs {

    class Transpose : public ArrayFunction
    {
    public:
	Transpose();
	void evaluate(double *value, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims) 
	    const override;
	std::vector<unsigned long> 
	    dim(std::vector<std::vector<unsigned long> > const &dims,
		std::vector<double const *> const &values) const override;
	bool checkParameterDim(std::vector<std::vector<unsigned long> > const &dims) const override;
	bool isAdditive(std::vector<bool> const &mask,
			std::vector<bool> const &isfixed) const override;
	bool isScale(std::vector<bool> const &mask,
		     std::vector<bool> const &isfixed) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *value, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims,
		      unsigned long i) const override;
	
    };

}}

#endif /* TRANSPOSE_H_ */
