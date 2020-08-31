#ifndef FUNC_NEG_H_
#define FUNC_NEG_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace base {

/**
 * @short Unary minus operator
 * UnaryMinus implements the prefix operator "-"
 * y <- -x
 */
class Neg : public ScalarFunction
{
public:
    Neg ();
    double evaluate(std::vector<double const *> const &args) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    bool isScale(std::vector<bool> const &mask, 
		 std::vector<bool> const &fix) const override;
    std::string deparse(std::vector<std::string> const &par) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;

};

}}

#endif /* FUNC_NEG_H_ */
