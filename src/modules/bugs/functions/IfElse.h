#ifndef IF_ELSE_H_
#define IF_ELSE_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

/**
 * The ifelse function returns either a or b depending on whether the 
 * value of x is zero or not
 * 
 * @short Conditional selection 
 * <pre>
 * y <- ifelse(x,a,b)
 * y = a if x != 0 
 * y = b if x == 0
 * </pre>
 */
class IfElse : public ScalarFunction
{
public:
    IfElse ();
    double evaluate(std::vector<double const *> const &args) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    bool isAdditive(std::vector<bool> const &mask, 
		    std::vector<bool> const &fixed) const override;
    bool isScale(std::vector<bool> const &mask, 
		 std::vector<bool> const &fixed) const override;
    bool isLinear(std::vector<bool> const &mask, 
		  std::vector<bool> const &fixed) const override;
};

}}

#endif /* IF_ELSE_H_ */
