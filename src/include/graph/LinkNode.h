#ifndef LINK_NODE_H_
#define LINK_NODE_H_

#include <graph/LogicalNode.h>
#include <vector>

namespace jags {

class LinkFunction;

/**
 * @short Scalar Node representing link function from a GLM 
 */
class LinkNode : public LogicalNode {
    LinkFunction const * const _func;
public:
    /**
     * A link node is defined by an inverse link function and a single
     * parent node, which must be scalar
     */
    LinkNode(LinkFunction const *func, unsigned int nchain,
	     std::vector<Node const *> const &parents);
    /**
     * Calculates the value of the node based on the parameters. 
     */
    void deterministicSample(unsigned int chain) override;
    /**
     * Returns true. An inverse link function should accept every
     * value in the range [-Inf, Inf].
     */
    bool checkParentValues(unsigned int chain) const override;
    /**
     * Returns the linear predictor
     */
    double eta(unsigned int chain) const;
    /**
     * Returns the gradient of the inverse link function
     * @see LinkFunction#grad
     */
    double grad(unsigned int chain) const;
    /**
     * Returns the name of the link function
     */
    std::string const &linkName() const;
    //DeterministicNode *clone(std::vector<Node const *> const &parents) const;
    bool hasGradient(Node const *arg) const override;
    void gradient(double *grad, Node const *arg, unsigned int chain)
	const override;
};

} /* namespace jags */

#endif /* LINK_NODE_H_ */
