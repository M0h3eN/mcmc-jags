#ifndef FUNC_ADD_H_
#define FUNC_ADD_H_

#include "Infix.h"

namespace jags {
namespace base {

/**
 * The Add function implements the infix operator "+" in the BUGS language.
 * The expression a + b + c is evaluated in a single function call.
 * @short Sum of scalars
 * <pre>
 * y <- a + b
 * </pre>
 */
class Add : public Infix
{
public:
    Add ();
    double evaluate(std::vector<double const *>const &args) const override;
    bool isDiscreteValued(std::vector<bool> const &flags) const override;
    bool isAdditive(std::vector<bool> const &mask,
		    std::vector<bool> const &fixmask) const override;
    bool isLinear(std::vector<bool> const &mask,
		  std::vector<bool> const &fixmask) const override;
    bool isScale(std::vector<bool> const &mask,
		 std::vector<bool> const &fixmask) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;

};

}}

#endif /* FUNC_ADD_H_ */
