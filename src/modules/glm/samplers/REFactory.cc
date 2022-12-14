#include <config.h>

#include "REFactory.h"
#include "RESampler.h"
#include "REMethod.h"

#include "AuxMixPoisson.h"
#include "AuxMixBinomial.h"
#include "NormalLinear.h"
#include "LogisticLinear.h"
#include "BinaryProbit.h"
#include "PolyaGamma.h"
#include "OrderedLogit.h"
#include "OrderedProbit.h"
#include "MNormalLinear.h"
#include "LogNormalLinear.h"

#include <graph/Graph.h>
#include <graph/StochasticNode.h>
#include <graph/DeterministicNode.h>
#include <distribution/Distribution.h>
#include <sampler/Linear.h>
#include <sampler/SingletonGraphView.h>
#include <sampler/GraphView.h>
#include <module/ModuleError.h>

#include <algorithm>
#include <utility>

using std::vector;
using std::string;
using std::list;

namespace jags {
    namespace glm {

	REFactory::REFactory(std::string const &name)
	    : _name(name)
	{}
	
	bool REFactory::checkOutcome(StochasticNode const *snode) const
	{
	    return NormalLinear::canRepresent(snode) ||
		LogisticLinear::canRepresent(snode) || 
		PolyaGamma::canRepresent(snode) ||
		BinaryProbit::canRepresent(snode) ||
		AuxMixPoisson::canRepresent(snode) ||
		AuxMixBinomial::canRepresent(snode) ||
		OrderedLogit::canRepresent(snode) ||
		OrderedProbit::canRepresent(snode) ||
		MNormalLinear::canRepresent(snode) ||
		LogNormalLinear::canRepresent(snode);
	}

	bool REFactory::checkTau(SingletonGraphView const *tau) const
	{
	    if (!tau->deterministicChildren().empty()) {
		return false;
	    }
	    
	    vector<StochasticNode *> const &eps = tau->stochasticChildren();
	    for (unsigned int i = 0; i < eps.size(); ++i) {
		if (isObserved(eps[i])) {
		    return false;
		}
		if (isBounded(eps[i])) {
		    return false; 
		}
		if (eps[i]->distribution()->name() != "dnorm" &&
		    eps[i]->distribution()->name() != "dmnorm") {
		    return false;
		}

		Node const *mu_tau = eps[i]->parents()[1];
		if (mu_tau != tau->node()) {
		    return false;
		}
		if (tau->isDependent(eps[i]->parents()[0])) {
		    return false; //mean parameter depends on snode
		}
	    }
	    
	    return true; //We made it!
	}
	
	
	bool REFactory::checkEps(GraphView const *eps) const
	{
	    vector<StochasticNode *> const &stoch_nodes = 
		eps->stochasticChildren();
	    for (unsigned int i = 0; i < stoch_nodes.size(); ++i) {
		if (isBounded(stoch_nodes[i])) {
		    return false; //Truncated outcome variable
		}
		if (!checkOutcome(stoch_nodes[i])) {
		    return false; //Invalid outcome or link
		}
		//Check that other parameters do not depend on snode	    
		vector<Node const *> const &param = stoch_nodes[i]->parents();
		for (unsigned int j = 1; j < param.size(); ++j) {
		    if (eps->isDependent(param[j])) {
			return false;
		    }
		}
	    }

	    // Check linearity of deterministic descendants
	    if (!checkLinear(eps, false, true))
		return false;

	    return true;
	}

	REFactory::~REFactory()
	{}
    
	Sampler * REFactory::makeSampler(
	    list<StochasticNode*> const &free_nodes, 
	    Graph const &graph) const
	{
	    SingletonGraphView *tau = nullptr;
	    GraphView *eps = nullptr;
	    for (list<StochasticNode*>::const_iterator p = free_nodes.begin();
		 p != free_nodes.end(); ++p)
	    {
		if (canSample(*p)) {
		    tau = new SingletonGraphView(*p, graph);
		    if (checkTau(tau)) {
			eps = new GraphView(tau->stochasticChildren(), graph);
			if (checkEps(eps)) {
			    break;
			}
		    }
		    delete eps; eps = nullptr;
		    delete tau; tau = nullptr;
		}
	    }

	    if (!tau || !eps) {
		return nullptr;
	    }

	    vector<SingletonGraphView *> sub_eps;
	    vector<SingletonGraphView const *> const_sub_eps;
	    for (unsigned int i = 0; i < eps->nodes().size(); ++i) {
		SingletonGraphView *gv =
		    new SingletonGraphView(eps->nodes()[i], graph);
		sub_eps.push_back(gv);
		const_sub_eps.push_back(gv);
	    }

	    unsigned int Nch = nchain(tau);
	    vector<REMethod*> methods(Nch, nullptr);
	    for (unsigned int ch = 0; ch < Nch; ++ch) {
		vector<Outcome *> outcomes;
		vector<StochasticNode *> const &sch = eps->stochasticChildren();
		for (vector<StochasticNode *>::const_iterator p = sch.begin();
		     p != sch.end(); ++p)
		{
		    Outcome *outcome = nullptr;
		    if (NormalLinear::canRepresent(*p)) {
			outcome = new NormalLinear(*p, ch);
		    }
		    else if (LogisticLinear::canRepresent(*p)) {
			outcome = new LogisticLinear(*p, ch);
		    }
		    else if (PolyaGamma::canRepresent(*p)) {
			outcome = new PolyaGamma(*p, ch);
		    }
		    else if (BinaryProbit::canRepresent(*p)) {
			outcome = new BinaryProbit(*p, ch);
		    }
		    else if (AuxMixBinomial::canRepresent(*p)) {
			outcome = new AuxMixBinomial(*p, ch);
		    }
		    else if (AuxMixPoisson::canRepresent(*p)) {
			outcome = new AuxMixPoisson(*p, ch);
		    }
		    else if (OrderedLogit::canRepresent(*p)) {
			outcome = new OrderedLogit(*p, ch);
		    }
		    else if (OrderedProbit::canRepresent(*p)) {
			outcome = new OrderedProbit(*p, ch);
		    }
		    else if (MNormalLinear::canRepresent(*p)) {
			outcome = new MNormalLinear(*p, ch);
		    }
		    else if (LogNormalLinear::canRepresent(*p)) {
			outcome = new LogNormalLinear(*p, ch);
		    }
		    else {
			throwLogicError("Invalid outcome in REFactory");
		    }
		    outcomes.push_back(outcome);
		}

		methods[ch] = newMethod(tau, eps, const_sub_eps, outcomes,ch);
	    }

	    /* Create a single GraphView containing all sampled nodes
	       (from tau and from eps). This is required by the Sampler
	       class. Note that this is a multilevel GraphView.
	    */
	    vector<StochasticNode*> snodes = eps->nodes();
	    snodes.push_back(tau->node());
	    GraphView *view = new GraphView(snodes, graph, true);
		
	    return new RESampler(view, tau, eps, sub_eps, methods, _name);
	}
	
	vector<Sampler*>  
	REFactory::makeSamplers(list<StochasticNode*> const &nodes, 
					   Graph const &graph) const
	{
	    if (Sampler *s = makeSampler(nodes, graph)) {
		return vector<Sampler*>(1, s);
	    }
	    return vector<Sampler*>();
	}


	string REFactory::name() const
	{
	    return _name;
	}
	
    } // namespace glm
} //namespace jags

