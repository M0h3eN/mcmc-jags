#ifndef FUNC_DIVIDE_H_
#define FUNC_DIVIDE_H_

#include "Infix.h"

namespace jags {
namespace base {

/**
 * The Divide function implements the infix operator "/" in the BUGS 
 * language
 * @short Ratio of two scalars
 * <pre>
 * y <- a/b
 * y = a/b for b != 0
 * </pre>
 */
class Divide:public Infix
{
public:
    Divide ();
    double evaluate(std::vector<double const *> const &args) const override;
    bool checkParameterValue (std::vector <double const *> const &args)
	const override;
    bool isScale(std::vector<bool> const &mask,
                 std::vector<bool> const &fix) const override;
    bool isPower(std::vector<bool> const &mask,
                 std::vector<bool> const &fix) const override;
    bool hasGradient(unsigned long i) const override;
    double gradient(std::vector<double const *> const &args,
		    unsigned long i) const override;


};

}}

#endif /* FUNC_DIVIDE_H_ */
