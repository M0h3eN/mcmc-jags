#ifndef FINITE_FACTORY_H_
#define FINITE_FACTORY_H_

#include <sampler/SingletonFactory.h>

namespace jags {
namespace base {

    /**
     * @short Factory object for finite samplers
     */
    class FiniteFactory : public SingletonFactory {
    public:
	bool canSample(StochasticNode *snode, Graph const &graph)
	    const override;
	Sampler *makeSampler(StochasticNode *snode, 
			     Graph const &graph) const override;
	std::string name() const override;
    };

}}

#endif /* FINITE_FACTORY_H_ */
