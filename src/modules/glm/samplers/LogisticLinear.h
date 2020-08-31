#ifndef LOGISTIC_LINEAR_H_
#define LOGISTIC_LINEAR_H_

#include <config.h>
#include "Outcome.h"

#include <graph/StochasticNode.h>

namespace jags {

    class StochasticNode;
    
    namespace glm {

	class LogisticLinear : public Outcome
	{
	    double const &_value;
	    double const &_mean;
	    double const &_precision;
	    double _lambda;
	  public:
	    LogisticLinear(StochasticNode const *snode, unsigned int chain);
	    double value() const override;
	    double precision() const override;
	    void update(RNG *rng) override;
	    static bool canRepresent(StochasticNode const *snode);
	};

    }
}

#endif /* LOGISTIC_LINEAR_H_ */
