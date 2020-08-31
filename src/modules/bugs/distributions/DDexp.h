#ifndef DDEXP_H_
#define DDEXP_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Double exponential distribution
 * <pre>
 * x ~ ddexp(mu,tau)
 * f(x|mu,tau) = (tau/2) * exp(-tau * abs(x-mu))
 * </pre>
 */
class DDexp : public RScalarDist {
public:
  DDexp();
  
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
  double KL(std::vector<double const *> const &par1,
	    std::vector<double const *> const &par2) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;
};

}}

#endif /* DDEXP_H_ */
