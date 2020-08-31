#ifndef DIRICHLET_FACTORY_H_
#define DIRICHLET_FACTORY_H_

#include "Dirichlet.h"

#include <sampler/SingletonFactory.h>

namespace jags {
namespace bugs {

/**
 * @short Factory object for multivariate normal samplers
 */
class DirichletFactory : public SingletonFactory
{
public:
    bool canSample(StochasticNode *snode, Graph const &graph) const override;
    Sampler *makeSampler(StochasticNode *snode, Graph const &graph)
	const override;
    std::string name() const override;
};

}}

#endif /* DIRICHLET_FACTORY_H_ */
