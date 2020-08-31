#ifndef DRW1_H_
#define DRW1_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace bugs {

/**
 * @short First order random walk
 *
 * <pre>
 * y[] ~ drw1(tau, x[])
 * </pre>
 */
class DRW1 : public VectorDist {
public:
    DRW1();
    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths,
		      RNG *rng) const override;
    unsigned long length(std::vector<unsigned long> const &lengths)
	const override;
    bool checkParameterLength(std::vector<unsigned long> const &lengths)
	const override;
    bool checkParameterValue(std::vector<double const *> const &parameters,
			     std::vector<unsigned long> const &lengths)
	const override;
    void support(double *lower, double *upper,
		 std::vector<double const *> const &parameters,
		 std::vector<unsigned long> const &lengths) const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool fullRank() const override;
};

}}

#endif /* DRW1_H_ */
