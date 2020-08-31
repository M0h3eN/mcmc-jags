#ifndef FUNC_LOGGAM_H_
#define FUNC_LOGGAM_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Log gamma function
     * <pre>
     * y <- loggam(x)
     * y = log(gamma(x)) for x > 0
     * </pre>
     */
    class LogGam:public ScalarFunction
    {
    public:
	LogGam ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_LOGGAM_H_ */
