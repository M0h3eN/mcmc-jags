#ifndef FUNC_TAN_H_
#define FUNC_TAN_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Tangent function
     * @see sin
     * <pre>
     * y <- tan(x)
     * </pre>
     */
    class Tan : public ScalarFunction
    {
    public:
	Tan ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_TAN_H_ */
