#ifndef FUNC_ARCTAN_H_
#define FUNC_ARCTAN_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Inverse tangent function
     * @see Tan
     * <pre>
     * y <- arctan(x)
     * </pre>
     */
    class ArcTan : public ScalarFunction
    {
    public:
	ArcTan ();
	std::string alias() const override;
	double evaluate(std::vector<double const *> const &args) const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_ARCTAN_H_ */
