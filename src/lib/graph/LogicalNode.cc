#include <config.h>
#include <graph/LogicalNode.h>
#include <function/FuncError.h>
#include <function/Function.h>
#include <graph/GraphMarks.h>
#include <graph/Graph.h>
#include <util/dim.h>

#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::set;
using std::logic_error;
using std::floor;

namespace jags {

static vector<vector<double const *> > 
mkParams(vector<Node const*> const &parents, unsigned int nchain)
{
    vector<vector<double const *> > ans(nchain);
    for (unsigned int n = 0; n < nchain; ++n) {
	ans[n].reserve(parents.size());
	for (unsigned long j = 0; j < parents.size(); ++j) {
	    ans[n].push_back(parents[j]->value(n));
	}
	
    }
    return ans;
}

    void LogicalNode::initializeFixed()
    {
	if (!isFixed()) return;

	/* Code for initializing fixed value LogicalNodes. It cannot
	   be included in the constructor as it uses the virtual
	   function deterministicSample. So we call this utility
	   function from the constructor of each child class
	   (ScalarLogicalNode, VectorLogicalNode, ArrayLogicalNode) */
	
	for (unsigned int ch = 0; ch < _nchain; ++ch) {
	    deterministicSample(ch);
	}
	
	/* Reset the _discrete flag based on the *value* of the
	   node. This is more accurate than Function#isDiscreteValued
	   which may give false negatives for fixed nodes (e.g.  2^N
	   is discrete for integer N >= 0, but not for N < 0). */

	_discrete = true;
	double const *val = value(0);
	for (unsigned long i = 0; i < _length; ++i) {
	    if (val[i] != floor(val[i])) {
		_discrete = false;
		break;
	    }
	}
	
    }

LogicalNode::LogicalNode(vector<unsigned long> const &dim,
			 unsigned int nchain,
			 vector<Node const *> const &parameters,
			 Function const *function)
    : DeterministicNode(dim, nchain, parameters),
      _func(function), _discrete(false), 
      _parameters(mkParams(parameters, nchain))
{
    if (!checkNPar(function, parameters.size())) {
	throw FuncError(function, "Incorrect number of arguments");
    }
    vector<bool> mask(parents().size());
    for (unsigned long j = 0; j < parents().size(); ++j) {
        mask[j] = parents()[j]->isDiscreteValued();
    }
    if (!_func->checkParameterDiscrete(mask)) {
	throw FuncError(function, "Failed check for discrete-valued arguments");
    }
    _discrete = _func->isDiscreteValued(mask);
}

string LogicalNode::deparse(vector<string> const &parents) const
{
    string name = "(";
    name.append(_func->deparse(parents));
    name.append(")");
	      
    return name;
}

bool LogicalNode::isClosed(set<Node const *> const &ancestors, 
			   ClosedFuncClass fc, bool fixed) const
{
    vector<Node const *> const &par = parents();

    vector<bool> mask(par.size());
    vector<bool> fixed_mask;
    unsigned long nmask = 0;
    for (unsigned long i = 0; i < par.size(); ++i) {
	mask[i] = ancestors.count(par[i]);
	if (mask[i]) {
	    ++nmask;
	}
	if (fixed) {
	    fixed_mask.push_back(par[i]->isFixed());
	}
    }

    if (nmask == 0) {
        throw logic_error("Invalid mask in LogicalNode::isClosed");
    }

    bool isclosed = false;
    
    switch(fc) {
    case DNODE_ADDITIVE:
	isclosed = _func->isAdditive(mask, fixed_mask);
	break;
    case DNODE_LINEAR:
	isclosed =  _func->isLinear(mask, fixed_mask);
        break;
    case DNODE_SCALE:
	isclosed = _func->isScale(mask, fixed_mask);
	break;
    case DNODE_SCALE_MIX:
        isclosed = (nmask == 1) && _func->isScale(mask, fixed_mask);
	break;
    case DNODE_POWER:
	isclosed =  _func->isPower(mask, fixed_mask);
        break;
    }

    return isclosed;
}
    
    bool LogicalNode::isDiscreteValued() const
    {
	return _discrete;
    }

    bool LogicalNode::hasGradient(Node const *arg) const
    {
	auto par = parents();
	for (unsigned int i = 0; i < par.size(); ++i) {
	    if (par[i] == arg) {
		if (!_func->hasGradient(i)) return false;
	    }
	}
	return true;
    }

} //namespace jags
