#ifndef ORDERED_PROBIT_H_
#define ORDERED_PROBIT_H_

#include <config.h>

#include "Outcome.h"
#include <graph/StochasticNode.h>

namespace jags {

class StochasticNode;

namespace glm {

    /*
     * @short Ordered categorical outcome with probit link
     *
     * Outcome for ordered logistic regression models, based on Holmes
     * C and Held L (2006).  Bayesian Auxiliary Variables Models for
     * Binary and Multinomial Regression, Bayesian Analysis,
     * 1:148-168.
     *
     * The categorical outcome is represented in terms of a latent normal
     * normals
     */
    class OrderedProbit : public Outcome
    {
	double const &_y;
	double const *_cuts;
	const unsigned long _ncut;
	double _z;
      public:
	OrderedProbit(StochasticNode const *snode, unsigned int chain);
	double value() const override;
	double precision() const override;
	void update(RNG *rng) override;
	void update(double mean, double var, RNG *rng) override;
	static bool canRepresent(StochasticNode const *snode);
    };

}}

#endif /* ORDERED_PROBIT_H_ */
