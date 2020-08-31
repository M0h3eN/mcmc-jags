#ifndef T_LINEAR_H_
#define T_LINEAR_H_

#include <config.h>
#include "Outcome.h"

#include <graph/StochasticNode.h>

namespace jags {

    class StochasticNode;
    
    namespace glm {

	class TLinear : public Outcome
	{
	    double const &_value;
	    double const &_mean;
	    double const &_precision;
	    double const &_df;
	    double _lambda;
	  public:
	    TLinear(StochasticNode const *snode, unsigned int chain);
	    double value() const override;
	    double precision() const override;
	    void update(RNG *rng) override;
	    static bool canRepresent(StochasticNode const *snode);
	};

    }
}

#endif /* T_LINEAR_H_ */
