#ifndef DSAMPLE_H_
#define DSAMPLE_H_

#include <distribution/VectorDist.h>

struct RNG;

namespace jags {
    namespace bugs {

	/**
	 * <pre> X[] ~ dsample(p[], K) </pre> 
	 *
	 * Sample K elements without replacement using a vector of
	 * probability weights p. Sampled values have indicator
	 * 1. Non-sampled values have indicator 0.
	 *
	 * For sampling with replacement see DMulti.
	 *
	 * @short Sample without replacement
	 */
	class DSample : public VectorDist {
	public:
	    DSample();
	    
	    double logDensity(double const *x, PDFType type, 
			      std::vector<double const *> const &parameters,
			      std::vector<unsigned long> const &lengths)
		const override;
	    void randomSample(double *x,
			      std::vector<double const *> const &parameters,
			      std::vector<unsigned long> const &lengths,
			      RNG *rng) const override;
	    bool checkParameterValue(std::vector<double const *> const &par,
				     std::vector<unsigned long> const &lengths)
		const override;
	    bool checkParameterLength(std::vector<unsigned long> const &lengths)
		const override;
	    bool checkParameterDiscrete(std::vector<bool> const &mask)
		const override;
	    unsigned long length(std::vector<unsigned long> const &lengths)
		const override;
	    void support(double *lower, double *upper,
			 std::vector<double const *> const &parameters,
			 std::vector<unsigned long> const &lengths)
		const override;
	    bool isSupportFixed(std::vector<bool> const &fixmask)
		const override;
	    bool fullRank() const override;
	    bool isDiscreteValued(std::vector<bool> const &mask)
		const override;
	};
    }
}

#endif /* DSAMPLE_H_ */
