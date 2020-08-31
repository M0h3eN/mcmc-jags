#ifndef M_NORMAL_LINEAR_H_
#define M_NORMAL_LINEAR_H_

#include <config.h>
#include "Outcome.h"

#include <graph/StochasticNode.h>

namespace jags {

class StochasticNode;

namespace glm {

    class MNormalLinear : public Outcome
    {
	double const *_value;
	double const *_mean;
	double const *_precision;
      public:
	MNormalLinear(StochasticNode const *snode, unsigned int chain);
	double value() const override;
	double precision() const override;
	double const *vvalue() const override;
	double const *vmean() const override;
	double const *vprecision() const override;
	static bool canRepresent(StochasticNode const *snode);
    };

}}

#endif /* M_NORMAL_LINEAR_H_ */
