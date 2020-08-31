#ifndef DPOIS_H_
#define DPOIS_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * <pre>
 * r ~ dpois(lambda)
 * f(r|lambda) = exp(-lambda) * lambda^r / r! ; r = 0, 1 ,...
 * </pre>
 * @short Poisson distribution
 */
class DPois : public RScalarDist {
 public:
  DPois();

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
   * Checks that lambda > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const override;
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;
};

}}

#endif /* DPOIS_H_ */
