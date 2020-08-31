#ifndef DCHISQ_H_
#define DCHISQ_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Chi square distribution
 * <pre>
 * x ~ dchisq(k)
 * f(x|k) = 2^(-k/2) * x^(k/2 - 1) * exp(-x/2) / gamma(x/2); k > 0
 * </pre>
 */
class DChisqr : public RScalarDist {
 public:
  DChisqr();

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
   * Checks that k > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  std::string alias() const override;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;
};

}}

#endif /* DCHISQ_H_ */
