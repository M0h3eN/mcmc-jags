#ifndef FUNC_COS_H_
#define FUNC_COS_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Cosine function
     * @see Sin
     * <pre>
     * y <- cos(x)
     * </pre>
     */
    class Cos : public ScalarFunction
    {
    public:
	Cos ();
	double evaluate(std::vector<double const *> const &args) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_COS_H_ */
