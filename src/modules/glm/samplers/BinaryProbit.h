#ifndef BINARY_PROBIT_H_
#define BINARY_PROBIT_H_

#include <config.h>

#include "Outcome.h"
#include <graph/StochasticNode.h>

namespace jags {

class StochasticNode;

namespace glm {

    class BinaryProbit : public Outcome
    {
	double const &_y;
	double _z;
      public:
	BinaryProbit(StochasticNode const *snode, unsigned int chain);
	double value() const override;
	double precision() const override;
	void update(RNG *rng) override;
	void update(double mean, double var, RNG *rng) override;
	bool fixedA() const override;
	static bool canRepresent(StochasticNode const *snode);
    };

}}

#endif /* BINARY_PROBIT_H_ */
