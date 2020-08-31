#ifndef DMSTATE_H_
#define DMSTATE_H_

#include <distribution/ArrayDist.h>

namespace jags {
namespace msm {

/**
 * Distribution of x in multi-state homogeneous Markov model at time t
 * when state at time 0 was xold and transition intensity matrix is
 * Lambda
 * <pre> 
 * x ~ dmstate(xold, dt, Lambda[,]) 
 * </pre>
 * @short Interval censored transitions in a multistate Markov model
 */
class DMState : public ArrayDist {
public:
    DMState();
  
    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<std::vector<unsigned long> > const &dims)
	const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<std::vector<unsigned long> > const &dims,
		      RNG *rng) const override;
    void support(double *lower, double *upper,
		 std::vector<double const *> const &parameters,
		 std::vector<std::vector<unsigned long> > const &dims)
	const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool checkParameterDim(std::vector<std::vector<unsigned long> > const &dims)
	const override;
    bool checkParameterDiscrete(std::vector<bool> const &mask) const override;
    bool checkParameterValue(std::vector<double const *> const &par,
			     std::vector<std::vector<unsigned long>> const &dim)
	const override;
    std::vector<unsigned long> dim(std::vector<std::vector<unsigned long> >
				   const &dims) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
};

}}

#endif /* DMSTATE_H_ */

