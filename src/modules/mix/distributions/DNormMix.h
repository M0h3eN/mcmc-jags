#ifndef DNORM_MIX_H_
#define DNORM_MIX_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace mix {

/**
 * @short Mixture of normal distribution
 * <pre>
 * x ~ dnorm(mu, tau, pi)
 * </pre>
 * The parameters mu, tau, pi are conforming vectors or arrays. Each
 * element corresponds to a component of the mixture. If all parameters
 * are vectors then component i is normal with mean mu[i], tau[i] and 
 * probability of selection pi[i]/sum(pi).
 *
 * Note that the parameter pi is redundant: the likelihood depends
 * only on pi/sum(pi).
 */
    class DNormMix : public VectorDist {
    public:
	DNormMix();
	
	double logDensity(double const *x, PDFType type,
			  std::vector<double const *> const &parameters,
			  std::vector<unsigned long> const &lengths)
	    const override;
	void randomSample(double *x,
			  std::vector<double const *> const &parameters,
			  std::vector<unsigned long> const &lengths,
			  RNG *rng) const override;
	void support(double *lower, double *upper,
		     std::vector<double const *> const &parameters,
		     std::vector<unsigned long> const &lengths) const override;
	bool isSupportFixed(std::vector<bool> const &fixmask) const override;
	bool checkParameterLength(std::vector<unsigned long> const &lengths)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &parameters,
				 std::vector<unsigned long> const &lengths) 
	    const override;
	unsigned long length(std::vector<unsigned long> const &parlengths)
	    const override;
    };

}}


#endif /* DNORM_MIX_H_ */
