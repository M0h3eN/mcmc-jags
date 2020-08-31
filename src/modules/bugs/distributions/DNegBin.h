#ifndef DNEGBIN_H_
#define DNEGBIN_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * <pre>
 * x ~ dnegbin(p, r)
 * f(x|p,r) = ((x+r-1)!/(x!*(r-1)!)) * p^r * (1-p)^x
 * </pre>
 * @short Negative Binomial distribution
 */
class DNegBin : public RScalarDist {
 public:
  DNegBin();
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
   * Checks that p lies in the interval (0,1) and r > 0
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

#endif /* DNEGBIN_H_ */
