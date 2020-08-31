#ifndef SAMPLER_FACTORY_H_
#define SAMPLER_FACTORY_H_

#include <vector>
#include <list>
#include <string>

#include <util/Factory.h>

namespace jags {

class Sampler;
class StochasticNode;
class Graph;

/**
 * @short Factory for Sampler objects
 */
class SamplerFactory : public Factory
{
public:
    ~SamplerFactory() override = default;
    /**
     * Finds nodes in the list of stochastic nodes that can be sampled
     * within the given graph, and returns a vector of newly allocated
     * samplers for them.  If no sampler can be created, an empty
     * vector is returned.
     */
    virtual std::vector<Sampler*> 
	makeSamplers(std::list<StochasticNode*> const &nodes, 
		     Graph const &graph) const = 0;
};

} /* namespace jags */

#endif /* SAMPLER_FACTORY_H_ */
