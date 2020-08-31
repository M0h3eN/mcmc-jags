#ifndef RE_SCALED_GAMMA_FACTORY_H_
#define RE_SCALED_GAMMA_FACTORY_H_

#include "REFactory.h"

namespace jags {
    namespace glm {

	/**
	 * @short Factory for random effects with scaled gamma precision
	 *
	 * @see REScaledGamma
	 */
	class REScaledGammaFactory : public REFactory
	{
	  public:
	    REScaledGammaFactory();
	    ~REScaledGammaFactory() override;
	    bool canSample(StochasticNode *snode) const override;
	    REMethod * newMethod(SingletonGraphView const *tau,
				 GraphView const *eps,
				 std::vector<SingletonGraphView const *> const & veps,
				 std::vector<Outcome*> const &outcomes,
				 unsigned int chain) const override;
	};
	
    }
}

#endif /* RE_SCALED_GAMMA_FACTORY_H_ */
