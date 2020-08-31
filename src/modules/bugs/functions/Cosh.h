#ifndef FUNC_COSH_H_
#define FUNC_COSH_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Hyperbolic cosine function
     * @see sinh
     * <pre>
     * y <- cosh(x)
     * </pre>
     */
    class Cosh : public ScalarFunction
    {
    public:
	Cosh ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_COSH_H_ */
