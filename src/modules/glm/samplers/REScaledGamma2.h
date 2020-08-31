#ifndef RE_SCALED_GAMMA2_H_
#define RE_SCALED_GAMMA2_H_

#include "REMethod2.h"

namespace jags {
    namespace glm {

	/**
	 * @short Random effects sampler for scaled gamma precision
	 */
	class REScaledGamma2 : public REMethod2 {
	    double _sigma;
	  public:
	    REScaledGamma2(SingletonGraphView const *tau,
			   GLMMethod const *glmmethod);
	    void updateTau(RNG *rng) override;
	    void updateSigma(RNG *rng) override;
	    bool isAdaptive() const override;
	    void adaptOff() override;
	    bool checkAdaptation() const override;
	};

    }
}

#endif /* RE_SCALED_GAMMA2_H_ */
