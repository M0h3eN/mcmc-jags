#ifndef FUNC_MULTIPLY_H_
#define FUNC_MULTIPLY_H_

#include "Infix.h"

namespace jags {
namespace base {

    /**
     * @short Product of two scalars 
     * 
     * The Multiply function implements the infix operator "*" in the
     * BUGS language.  The expression a * b * c is evaluated in a single 
     * function call.
     */
    class Multiply: public Infix
    {
    public:
	Multiply ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
	bool isScale(std::vector<bool> const &mask,
		     std::vector<bool> const &fixmask) const override;
	bool isPower(std::vector<bool> const &mask, 
		     std::vector<bool> const &fix) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;

    };
    
}}

#endif /* FUNC_MULTIPLY_H_ */
