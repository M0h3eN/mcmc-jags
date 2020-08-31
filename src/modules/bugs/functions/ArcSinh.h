#ifndef FUNC_ARCSINH_H_
#define FUNC_ARCSINH_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Inverse hyperbolic sine function
     * @see sinh
     * <pre>
     * y <- arcsinh(x)
     * </pre>
     */
    class ArcSinh : public ScalarFunction
    {
    public:
	ArcSinh ();
	std::string alias() const override;
	double evaluate(std::vector<double const *> const &args) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_ARCSINH_H_ */
