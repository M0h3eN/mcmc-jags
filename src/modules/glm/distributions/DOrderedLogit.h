#ifndef DORDERED_LOGIT_H_
#define DORDERED_LOGIT_H_

#include "DOrdered.h"

namespace jags {
    namespace glm {
	
	class DOrderedLogit : public DOrdered
	{
	public:
	    DOrderedLogit();
	    double r(double mu, RNG *rng) const override;
	    double p(double x, double mu, bool lower, bool give_log)
		const override;
	};

    }
}

#endif /* DORDERED_LOGIT_H_ */

	    
    
