#ifndef FUNC_PROBIT_H_
#define FUNC_PROBIT_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Normal quantile function
     * @see Phi
     * <pre>
     * y <- probit(p)
     * Prob(Y < y) = p for Y ~ N(0,1); 0 < p < 1
     * </pre>
     */
    class Probit : public ScalarFunction
    {
    public:
	Probit ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_PROBIT_H_ */
