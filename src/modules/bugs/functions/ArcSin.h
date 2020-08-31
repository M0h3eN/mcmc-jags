#ifndef FUNC_ARCSIN_H_
#define FUNC_ARCSIN_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Inverse sine function
     * @see Sin
     * <pre>
     * y <- arcsin(x)
     * </pre>
     */
    class ArcSin : public ScalarFunction
    {
    public:
	ArcSin ();
	std::string alias() const override;
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_ARCSIN_H_ */
