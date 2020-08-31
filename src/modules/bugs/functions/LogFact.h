#ifndef FUNC_LOGFACT_H_
#define FUNC_LOGFACT_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Log factorial function
     * @see LogGamma
     * <pre>
     * y <- logfact(x)
     * y = x! 
     *   = log(gamma(x + 1)) for x > -1
     * </pre>
     */
    class LogFact : public ScalarFunction
    {
    public:
	LogFact ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_LOGFACT_H_ */
