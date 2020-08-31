#ifndef SCALED_GAMMA_FACTORY_H_
#define SCALED_GAMMA_FACTORY_H_

#include <sampler/SingletonFactory.h>

namespace jags {
    namespace glm {

	/**
	 * @short Factory for scaled precision parameters 
	 *
	 * @see ScaledGamma
	 */
	class ScaledGammaFactory : public SingletonFactory
	{
	  public:
	    ~ScaledGammaFactory() override;
	    bool canSample(StochasticNode *snode, Graph const &graph)
		const override;
	    Sampler *makeSampler(StochasticNode *snode, Graph const &g)
		const override;
	    std::string name() const override;
	};
	
    }
}

#endif /* SCALED_GAMMA_FACTORY_H_ */
