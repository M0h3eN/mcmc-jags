#ifndef DINTERVAL_H_
#define DINTERVAL_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace bugs {

/**
 * @short Interval censored distribution
 * <pre>
 * i ~ dinterval(t, cutpoints[])
 * f(i|t) = 1 if t < cutpoints[i] and t >= cutpoints[i-1]
 *        = 0 otherwise
 * </pre>
 */
class DInterval : public VectorDist {
public:
    DInterval();
  
    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths,
		      RNG *rng) const override;
    /**
     * Checks that cutpoints are in ascending order
     */
    bool checkParameterValue(std::vector<double const *> const &parameters,
			     std::vector<unsigned long> const &lengths)
	const override;
    bool checkParameterLength(std::vector<unsigned long> const &lengths)
	const override;
    void support(double *lower, double *upper, 
		 std::vector<double const *> const &parameters,
		 std::vector<unsigned long> const &lengths) const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool fullRank() const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    unsigned long length(std::vector<unsigned long> const &params)
	const override;
    double KL(std::vector<double const *> const &par0,
	      std::vector<double const *> const &par1,
	      std::vector<unsigned long> const &lengths) const override;
};

}}

#endif /* DINTERVAL_H_ */
