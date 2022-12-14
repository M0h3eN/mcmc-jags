#ifndef DF_H_
#define DF_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * F distribution on n1, n2 degrees of freedom
 * <pre>
 * f(x| n1, n2) = Gamma((n1 + n2)/2) / (Gamma(n1/2) Gamma(n2/2))       
 *                (n1/n2)^(n1/2) x^(n1/2 - 1)                  
 *                (1 + (n1/n2) x)^-(n1 + n2)/2   
 * </pre>
 * @short F distribution
 */
class DF : public RScalarDist {
 public:
  DF();

  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, 
	   bool log) const override;
  double p(double x, std::vector<double const *> const &parameters, bool lower,
	   bool log) const override;
  double q(double x, std::vector<double const *> const &parameters, bool lower,
	   bool log) const override;
  double r(std::vector<double const *> const &parameters, RNG *rng)
      const override;
  /**
   * Check that tau > 0 and n1 > 0 and n2 > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters)
      const override;
  bool hasScore(unsigned long i) const override;
  double score(double x, std::vector<double const *> const &par,
	       unsigned long i) const override;
};

}}

#endif /* DF_H_ */
