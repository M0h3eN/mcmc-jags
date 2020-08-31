#ifndef BINOM_SLICER_H_
#define BINOM_SLICER_H_

#include <sampler/Slicer.h>

namespace jags {

    class StochasticNode;
    class SingletonGraphView;
    class Graph;
    
namespace bugs {

/**
 * Slice sampler for real-valued distributions
 */
    class BinomSlicer : public Slicer 
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
	BinomSlicer(SingletonGraphView const *gv, unsigned int chain,
		    double width = 1, unsigned int maxwidth = 10);
	double value() const override;
	void setValue(double value) override;
	void getLimits(double *lower, double *upper) const override;
	void update(RNG *rng) override;
	static bool canSample(StochasticNode *node, Graph const &graph);
	double logDensity() const override;
    };

}}

#endif /* BINOM_SLICER_H_ */

