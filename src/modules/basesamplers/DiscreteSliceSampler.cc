#include <config.h>
#include <graph/StochasticNode.h>
//fixme: temporarily needed
#include <graph/DeterministicNode.h>
#include <graph/NodeError.h>
#include <distribution/Distribution.h>

#include "DiscreteSliceSampler.h"

#include <cmath>
#include <cfloat>

using std::floor;
using std::vector;

DiscreteSliceSampler::DiscreteSliceSampler(StochasticNode *node, 
					   Graph const &graph,
                                           unsigned int chain,
					   double width, long ndoubles)
  : Slicer(vector<StochasticNode*>(1, node), graph, chain, width, ndoubles), 
    _x(*node->value(chain))
{
}

bool DiscreteSliceSampler::canSample(StochasticNode const *node,
				     Graph const &graph)
{
  if (!node->distribution()->isDiscreteValued() ||
	  node->length() != 1)
     return false;

  if (node->distribution()->isDeterministic())
        return false;

  return true;
}

void DiscreteSliceSampler::setValue(double x)
{
  _x = x;
  nodes().front()->setValue(&_x, 1, chain());
  vector<DeterministicNode*> const &dc = deterministicChildren();
  for (vector<DeterministicNode*>::const_iterator i(dc.begin()); 
       i != dc.end(); ++i) 
    {
      (*i)->deterministicSample(chain());
    }
}
  
double DiscreteSliceSampler::value()
{
  return _x;
}

void DiscreteSliceSampler::getLimits(double *lower, double *upper)
{
  StochasticNode const *snode = nodes().front();
  snode->distribution()->support(lower, upper, 1, snode->parameters(chain()),
		  	       snode->parameterDims());
}

void DiscreteSliceSampler::update(RNG *rng)
{
  updateDouble(rng);
}
