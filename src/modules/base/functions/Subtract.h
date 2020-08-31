#ifndef FUNC_SUBTRACT_H_
#define FUNC_SUBTRACT_H_

#include "Infix.h"

namespace jags {
namespace base {

/**
 * @short Difference of two scalars 
 * 
 * The Subtract function implements the infix operator "-" in the
 * BUGS language.  
 * <pre>
 * y <- x - z
 * </pre>
 */
class Subtract : public Infix 
{ 
public:
    Subtract ();
    double evaluate(std::vector<double const *> const &args) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    bool isAdditive(std::vector<bool> const &mask, 
		    std::vector<bool> const &fix) const override;
    bool isScale(std::vector<bool> const &mask, 
		 std::vector<bool> const &fix) const override;
    bool isLinear(std::vector<bool> const &mask, 
		  std::vector<bool> const &fix) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;

};

}}

#endif /* FUNC_SUBTRACT_H_ */
