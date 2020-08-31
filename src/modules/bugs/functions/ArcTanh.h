#ifndef FUNC_ARCTANH_H_
#define FUNC_ARCTANH_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Inverse hyperbolic tangent function
     * @see tanh
     * <pre>
     * y <- arctanh(x)
     * </pre>
     */
    class ArcTanh : public ScalarFunction
    {
    public:
	ArcTanh ();
	std::string alias() const override;
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_ARCTANH_H_ */
