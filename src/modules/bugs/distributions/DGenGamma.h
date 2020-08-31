#ifndef DGEN_GAMMA_H_
#define DGEN_GAMMA_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Generalizedgamma distribution
 * <pre>
 * X ~ dgen.gamma(r, mu, beta)
 * f(x|r,mu) = beta * mu^(beta*r) * x^(beta*r - 1) * exp(-(mu * x)^beta) / gamma(r)
 * </pre>
 */
class DGenGamma : public RScalarDist {
 public:
  DGenGamma();
  std::string alias() const override;
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
   * Checks that r > 0, mu > 0, beta > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  double KL(std::vector<double const *> const &par1,
	    std::vector<double const *> const &par2) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &pars,
	       unsigned long i) const override;
};

}}

#endif /* DGEN_GAMMA_H_ */
