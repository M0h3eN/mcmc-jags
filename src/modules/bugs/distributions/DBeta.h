#ifndef DBETA_H_
#define DBETA_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Beta distribution
 * <pre>
 * P ~ dbeta(a, b)
 * f(p|a,b) = C(a,b) * p^(a -1) * (1 - p)^(b - 1) ; 0 < p < 1
 * </pre>
 */
class DBeta : public RScalarDist {
 public:
  DBeta();

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
   * Checks that a > 0, b > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters) const override;
  double KL(std::vector<double const *> const &par1, 
	    std::vector<double const *> const &par2) const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &parameters,
	       unsigned long i) const override;
};

}}

#endif /* DBETA_H_ */
