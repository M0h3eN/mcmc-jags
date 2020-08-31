#ifndef RE_GAMMA_FACTORY_H_
#define RE_GAMMA_FACTORY_H_

#include "REFactory.h"

namespace jags {
    namespace glm {

	/**
	 * @short Factory for random effects with gamma precision
	 *
	 * @see REGamma
	 */
	class REGammaFactory : public REFactory
	{
	  public:
	    REGammaFactory();
	    ~REGammaFactory() override;
	    bool canSample(StochasticNode *snode) const override;
	    REMethod * newMethod(SingletonGraphView const *tau,
				 GraphView const *eps,
				 std::vector<SingletonGraphView const *> const & veps,
				 std::vector<Outcome*> const &outcomes,
				 unsigned int chain) const override;
	};
	
    }
}

#endif /* RE_GAMMA_FACTORY_H_ */
