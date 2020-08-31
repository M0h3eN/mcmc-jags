#ifndef ARRAY_LOG_DENSITY_H_
#define ARRAY_LOG_DENSITY_H_

#include <function/ArrayFunction.h>

namespace jags {
    
    class ArrayDist;

    /**
     * @short Log density function for an array-valued Distribution
     */
    class ArrayLogDensity : public ArrayFunction
    {
	ArrayDist const *_dist;
    public:
	ArrayLogDensity(ArrayDist const *dist);
	std::vector<unsigned long> dim(
	    std::vector<std::vector<unsigned long> > const &dims,
	    std::vector<double const *> const &values) const override;
	bool checkParameterDim(
	    std::vector<std::vector<unsigned long> > const &dims)
	    const override;
	bool checkParameterValue(
	    std::vector<double const *> const &args,
	    std::vector<std::vector<unsigned long> > const &dims)
	    const override;
	void evaluate(
	    double *value,
	    std::vector <double const *> const &args,
	    std::vector<std::vector<unsigned long> > const &dims)
	    const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *grad, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims,
		      unsigned long i) const override;

    };

}

#endif /* ARRAY_LOG_DENSITY_H_ */
