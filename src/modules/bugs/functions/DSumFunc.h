#ifndef DSUM_FUNC_H_
#define DSUM_FUNC_H_

#include <function/ArrayFunction.h>

namespace jags {
namespace bugs {
    
    /**
     * @short Sum of two discrete random variables
     */
    class DSumFunc : public ArrayFunction {
    public:
	DSumFunc();
	void evaluate(double *x,
		      std::vector <double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims) 
	    const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *x, std::vector <double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims,
		      unsigned long i) const override;
	bool checkParameterDim(std::vector<std::vector<unsigned long> > const 
			       &dims) const override;
	std::vector<unsigned long> 
	    dim(std::vector <std::vector<unsigned long> > const &dims,
		std::vector<double const *> const &values) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
	bool isLinear(std::vector<bool> const &mask, 
		      std::vector<bool> const &fixed) const override;
	bool isScale(std::vector<bool> const &mask, 
		     std::vector<bool> const &fixed) const override;
    };
    
}}

#endif /* DSUM_FUNC_H_ */
