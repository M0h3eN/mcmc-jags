#ifndef FUNC_LOG_H_
#define FUNC_LOG_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Log function
     * @see Exp
     * <pre>
     * y <- log(x)
     * y = log(x) for x > 0
     * </pre>
     */
    class Log : public ScalarFunction
    {
    public:
	Log ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_LOG_H_ */
