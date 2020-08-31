#ifndef FUNC_POW_H_
#define FUNC_POW_H_

#include "Infix.h"

namespace jags {
namespace base {
    
/**
 * @short Power function using infix notation
 * If y <- x^z and x is negative, then z must be an integer
 */
class Pow : public Infix
{
public:
    Pow ();
    std::string alias() const override;
    double evaluate(std::vector<double const *> const &args) const override;
    bool checkParameterValue(std::vector<double const*> const &args)
	const override;
    bool isPower(std::vector<bool> const &mask, 
		 std::vector<bool> const &fix) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;

};

}}

#endif /* FUNC_POW_H_ */
