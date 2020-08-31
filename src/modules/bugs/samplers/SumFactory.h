#ifndef SUM_FACTORY_H_
#define SUM_FACTORY_H_

#include <sampler/SamplerFactory.h>

namespace jags {
    namespace bugs {

	/**
	 * @short Factory object for discrete sum samplers
	 */
	class SumFactory : public SamplerFactory
	{
	  public:
	    std::vector<Sampler*>
		makeSamplers(std::list<StochasticNode*> const &nodes, 
			     Graph const &graph) const override;
	    std::string name() const override;
	};
	
    }
}

#endif /* SUM_FACTORY_H_ */
