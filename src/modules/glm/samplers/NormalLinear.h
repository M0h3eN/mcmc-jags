#ifndef NORMAL_LINEAR_H_
#define NORMAL_LINEAR_H_

#include <config.h>
#include "Outcome.h"

#include <graph/StochasticNode.h>

namespace jags {

class StochasticNode;

namespace glm {

    class NormalLinear : public Outcome
    {
	double const &_value;
	double const &_precision;
      public:
	NormalLinear(StochasticNode const *snode, unsigned int chain);
	double value() const override;
	double precision() const override;
	static bool canRepresent(StochasticNode const *snode);
	bool fixedb() const override;
	bool fixedA() const override;
    };

}}

#endif /* NORMAL_LINEAR_H_ */
