#ifndef SUM_DIST_H_
#define SUM_DIST_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace bugs {

/**
 * @short Sum of 2 or more random variables
 */
class SumDist : public VectorDist {
public:
    SumDist();

    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths,
		      RNG *rng) const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    bool fullRank() const override;
    bool checkParameterValue(std::vector<double const *> const &params,
			     std::vector<unsigned long> const &lengths)
	const override;
    bool checkParameterLength(std::vector<unsigned long> const &lengths)
	const override;
    bool checkParameterDiscrete(std::vector<bool> const &mask) const override;
    void support(double *lower, double *upper, 
		 std::vector<double const *> const &parameters,
		 std::vector<unsigned long> const &lengths) const override;
    unsigned long length(std::vector <unsigned long> const &lengths)
	const override;
};

}}

#endif /* SUM_DIST_H_ */
