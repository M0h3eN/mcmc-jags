#ifndef FUNC_ARCCOS_H_
#define FUNC_ARCCOS_H_

#include <function/ScalarFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Inverse cosine function
     * @see Cos
     * <pre>
     * y <- arccos(x)
     * </pre>
     */
    class ArcCos : public ScalarFunction
    {
    public:
	ArcCos ();
	std::string alias() const override;
	double evaluate(std::vector<double const *> const &args) const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}}

#endif /* FUNC_ARCCOS_H_ */
