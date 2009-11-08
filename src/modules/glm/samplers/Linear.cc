#include <config.h>

#include "Linear.h"
#include <graph/StochasticNode.h>
#include <sampler/Updater.h>

using std::vector;
using std::string;

namespace glm {

    Linear::Linear(Updater const *updater, 
		   vector<Updater const *> const &sub_updaters,
		   unsigned int chain, bool gibbs)
	: GLMMethod(updater, sub_updaters, chain, false), _gibbs(gibbs)
    {
    }

    double Linear::getMean(unsigned int i) const
    {
	return _updater->stochasticChildren()[i]->parents()[0]->value(_chain)[0];
    }
    
    double 
    Linear::getPrecision(unsigned int i) const 
    {
	return _updater->stochasticChildren()[i]->parents()[1]->value(_chain)[0];
    }

    double Linear::getValue(unsigned int i) const 
    {
	return _updater->stochasticChildren()[i]->value(_chain)[0];
    }
    
    string Linear::name() const
    {
	if (_gibbs)
	    return "LinearGibbs";
	else
	    return "Linear";
    }

    void Linear::initAuxiliary(RNG *rng) 
    {
	return; //Nothing to do
    }

    void Linear::updateAuxiliary(double *b, csn *N, RNG *rng)
    {
	return; //Nothing to do
    }

    void Linear::update(RNG *rng)
    {
	if (_gibbs) 
	    updateLMGibbs(rng, 1);
	else
	    updateLM(rng);
    }
}