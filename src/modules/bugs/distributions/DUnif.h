#ifndef DUNIF_H_
#define DUNIF_H_

#include <distribution/ScalarDist.h>

namespace jags {
namespace bugs {

/**
 * <pre>
 * x ~ dunif(a, b)
 * f(x|a,b) = 1/(a - b) ; a <= x <= b
 * </pre>
 * @short Uniform distribution
 */
class DUnif : public ScalarDist {
  public:
    DUnif();
    double logDensity(double x, PDFType type,
		      std::vector<double const *> const &parameters,
		      double const *lower, double const *upper) const override;
    double randomSample(std::vector<double const *> const &parameters,
			double const *lower, double const *upper,
			RNG *rng) const override;
    double l(std::vector<double const*> const &parameters) const override;
    double u(std::vector<double const*> const &parameters) const override;
    /** 
     * Checks that a < b
     */
    bool checkParameterValue(std::vector<double const *> const &parameters)
	const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    double KL(std::vector<double const *> const &par0,
	      std::vector<double const *> const &par1) const override;
};

}}

#endif /* DUNIF_H_ */
