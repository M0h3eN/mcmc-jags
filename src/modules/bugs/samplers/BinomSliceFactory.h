#ifndef BINOM_SLICE_FACTORY_H_
#define BINOM_SLICE_FACTORY_H_

#include <sampler/SingletonFactory.h>
class StochasticNode;
class Graph;

namespace jags {
    namespace bugs {

	/**
	 * @short Factory object for binomial slice samplers
	 */
	class BinomSliceFactory : public SingletonFactory
	{
	  public:
	    bool canSample(StochasticNode *snode, Graph const &graph)
		const override;
	    Sampler *makeSampler(StochasticNode *snode,
				 Graph const &graph) const override;
	    std::string name() const override;
	};

    }
}

#endif /* BINOM_SLICE_FACTORY_H_ */
