#ifndef FUNC_LOGIT_H_
#define FUNC_LOGIT_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Logistic function
     * @see ILogit
     * <pre>
     * y <- logit(p)
     * y = log(p/(1-p)) for 0 < p < 1
     * </pre>
     */
    class Logit:public ScalarFunction
    {
    public:
	Logit();
	double evaluate(std::vector <double const *> const &args)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_LOGIT_H_ */
