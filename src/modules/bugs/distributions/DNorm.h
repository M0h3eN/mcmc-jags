#ifndef DNORM_H_
#define DNORM_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * <pre>
 * x ~ dnorm(mu, tau)
 * f(x | mu, tau) = sqrt(tau) * exp(-tau * (x - mu)^2/2)
 * </pre>
 * @short Normal distribution
 */
class DNorm : public RScalarDist {
 public:
  DNorm();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, 
	   bool give_log) const override;
  double p(double q, std::vector<double const *> const &parameters, bool lower,
	   bool give_log) const override;
  double q(double p, std::vector<double const *> const &parameters, bool lower,
	   bool log_p) const override;
  double r(std::vector<double const *> const &parameters, RNG *rng)
      const override;
  /**
   * Checks that tau > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  /**
   * Exploits the capacity to sample truncted normal distributions
   * that is built into the JAGS library, overloading the generic
   * functionality of RScalarDist.
   */
  double randomSample(std::vector<double const *> const &par,
		      double const *lower, double const *upper,
		      RNG *rng) const override;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;    
};

}}

#endif /* DNORM_H_ */
