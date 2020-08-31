#ifndef MNORMAL_FACTORY_H_
#define MNORMAL_FACTORY_H_

#include "MNormal.h"

#include <sampler/SingletonFactory.h>

namespace jags {
namespace bugs {

/**
 * @short Factory object for multivariate normal samplers
 */
class MNormalFactory : public SingletonFactory
{
public:
    bool canSample(StochasticNode *snode, Graph const &graph) const override;
    Sampler *makeSampler(StochasticNode *snode, Graph const &graph)
	const override;
    std::string name() const override;
};

}}

#endif /* MNORMAL_FACTORY_H_ */
