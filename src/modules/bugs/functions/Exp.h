#ifndef FUNC_EXP_H_
#define FUNC_EXP_H_

#include <function/LinkFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Exponential function
     * @see Log
     * <pre>
     * y <- exp(x)
     * </pre>
     */
    class Exp: public LinkFunction
    {
    public:
	Exp ();
	double inverseLink(double eta) const override;
	double link(double mu) const override;
	double grad(double eta) const override;
    };

}}

#endif /* FUNC_EXP_H_ */
