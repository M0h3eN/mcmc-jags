#include <config.h>
#include <graph/StochasticNode.h>
//temporarily required
#include <graph/DeterministicNode.h>
#include <graph/NodeError.h>
#include <distribution/Distribution.h>
#include "RealSliceSampler.h"

#include <cmath>
#include <cfloat>

using std::vector;

RealSliceSampler::RealSliceSampler(StochasticNode *node, Graph const &graph,
                                   unsigned int chain,
				   double width, long maxwidth)
  : Slicer(vector<StochasticNode*>(1,node), graph, chain, width, maxwidth)
{
}

bool 
RealSliceSampler::canSample(StochasticNode const *node, Graph const &graph)
{
  if (node->distribution()->isDiscreteValued() || node->length() != 1)
     return false;

  if (node->distribution()->isDeterministic())
     return false; 

  return true;
}

double RealSliceSampler::value()
{
  return *nodes().front()->value(chain());
}
 
void RealSliceSampler::setValue(double value)
{
  nodes().front()->setValue(&value, 1, chain());
  vector<DeterministicNode*> const &dc = deterministicChildren();
  for (vector<DeterministicNode*>::const_iterator i(dc.begin()); 
       i != dc.end(); ++i) 
    {
      (*i)->deterministicSample(chain());
    }
}

void RealSliceSampler::getLimits(double *lower, double *upper)
{
  StochasticNode const *snode = nodes().front();
  snode->distribution()->support(lower, upper, 1, snode->parameters(chain()),
                                      snode->parameterDims());
}

void RealSliceSampler::update(RNG *rng)
{
  updateStep(rng);
}
