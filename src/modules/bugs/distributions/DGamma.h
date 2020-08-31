#ifndef DGAMMA_H_
#define DGAMMA_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short gamma distribution
 * <pre>
 * X ~ dgamma(r, mu)
 * f(x|r,mu) = mu^r * x^(r - 1) * exp(-mu * x)
 * </pre>
 */
class DGamma : public RScalarDist {
 public:
  DGamma();

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
   * Checks that r > 0, mu > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &pars,
	       unsigned long i) const override;
};

}}

#endif /* DGAMMA_H_ */
