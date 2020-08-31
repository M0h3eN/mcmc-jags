#ifndef REAL_SLICER_H_
#define REAL_SLICER_H_

#include <sampler/Slicer.h>

namespace jags {

    class StochasticNode;
    class SingletonGraphView;

namespace base {

/**
 * Slice sampler for real-valued distributions
 */
    class RealSlicer : public Slicer 
    {
	SingletonGraphView const *_gv;
	unsigned int _chain;
    public:
	/**
	 * Constructor for Slice Sampler
	 * @param gv GraphView containing node to sample
	 * @param chain Index number of chain to sample (starting from zero)
	 * @param width Initial width of slice
	 * @param maxwidth Maximal width of slice as a multiple of the width
	 * parameter
	 */
	RealSlicer(SingletonGraphView const *gv, unsigned int chain,
		   double width = 1, unsigned int maxwidth = 10);
	double value() const override;
	void setValue(double value) override;
	void getLimits(double *lower, double *upper) const override;
	void update(RNG *rng) override;
	static bool canSample(StochasticNode const *node);
	double logDensity() const override;
    };

}}

#endif /* REAL_SLICER_H_ */

