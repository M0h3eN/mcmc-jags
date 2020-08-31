#ifndef FUNC_ICLOGLOG_H_
#define FUNC_ICLOGLOG_H_

#include <function/LinkFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short inverse complementary log log link
     * @see CLogLog
     * <pre>
     * cloglog(y) <- a + b*x
     * y <- icloglog(a + b*x)
     * </pre>
     */
    class ICLogLog : public LinkFunction
    {
    public:
	ICLogLog ();
	double inverseLink(double eta) const override;
	double link(double mu) const override;
	double grad(double eta) const override;
    };

}}

#endif /* FUNC_ICLOGLOG_H_ */
