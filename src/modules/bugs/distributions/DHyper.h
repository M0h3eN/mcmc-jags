#ifndef DHYPER_H_
#define DHYPER_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * @short Hypergeometric distribution
 * <pre>
 * R ~ dhyper(n1,n2,m1,psi)
 * </pre>
 */
class DHyper : public RScalarDist {
 public:
  DHyper();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, 
	   bool give_log) const override;
  double p(double x, std::vector<double const *> const &parameters, bool lower,
	   bool give_log) const override;
  double q(double p, std::vector<double const *> const &parameters, bool lower,
	   bool log_p) const override;
  double r(std::vector<double const *> const &parameters, RNG *rng)
      const override;
  double l(std::vector<double const *> const &parameters) const override;
  double u(std::vector<double const *> const &parameters) const override;
  /**
   * Checks that n1, n2, m1 are discrete
   */
  bool checkParameterDiscrete (std::vector<bool> const &mask) const override;
  bool checkParameterValue(std::vector<double const*> const &parameters)
      const override;
  bool isSupportFixed(std::vector<bool> const &fixmask) const override;
  bool canBound() const override;
  double KL(std::vector<double const *> const &par1,
	    std::vector<double const *> const &par2) const override;
  bool hasScore(unsigned long i) const override;    
  double score(double x, std::vector<double const *> const &pars,
	       unsigned long i) const override;
};

}}

#endif /* DHYPER_H_ */
