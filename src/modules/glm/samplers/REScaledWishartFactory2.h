#ifndef RE_SCALED_WISHART_FACTORY2_H_
#define RE_SCALED_WISHART_FACTORY2_H_

#include "REFactory2.h"

namespace jags {
    namespace glm {

	/**
	 * @short Factory for random effects with scaled wishart precision
	 *
	 * @see REScaledWishart2
	 */
	class REScaledWishartFactory2 : public REFactory2
	{
	  public:
	    REScaledWishartFactory2();
	    ~REScaledWishartFactory2() override;
	    bool canSample(StochasticNode *snode) const override;
	    REMethod2 * newMethod(SingletonGraphView const *tau,
				  GLMMethod const *glmmethod) const override;
	};
	
    }
}

#endif /* RE_SCALED_WISHART_FACTORY2_H_ */
