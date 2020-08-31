#ifndef DEXP_H_
#define DEXP_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Exponential distribution
 * <pre>
 *  x ~ dexp(lambda)
 *  f(x | lambda) = lambda * exp(-lambda * x) ; x >= 0
 * </pre>
 */
class DExp : public RScalarDist {
 public:
  DExp();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, bool give_log)
      const override;
  double p(double q, std::vector<double const *> const &parameters, bool lower,
	   bool give_log) const override;
  double q(double p, std::vector<double const *> const &parameters, bool lower,
	   bool log_p) const override;
  double r(std::vector<double const *> const &parameters, RNG *rng)
      const override;
  /**
   * Checks that lambda > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const override;
  bool hasScore(unsigned long i) const override;    
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;
};

}}

#endif /* DEXP_H_ */
