#ifndef RE_GAMMA2_H_
#define RE_GAMMA2_H_

#include "REMethod2.h"
#include "REGammaSlicer2.h"

namespace jags {
    namespace glm {

	/**
	 * @short Random effects sampler for gamma precision
	 */
	class REGamma2 : public REMethod2 {
	    REGammaSlicer2 _slicer;
	  public:
	    REGamma2(SingletonGraphView const *tau,
		     GLMMethod const *glmmethod);
	    void updateTau(RNG *rng) override;
	    void updateSigma(RNG *rng) override;
	    bool isAdaptive() const override;
	    void adaptOff() override;
	    bool checkAdaptation() const override;
	};

    }
}

#endif /* RE_GAMMA2_H_ */
