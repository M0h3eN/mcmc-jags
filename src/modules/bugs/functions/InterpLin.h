#ifndef FUNC_INTERP_LIN_H_
#define FUNC_INTERP_LIN_H_

#include <function/ScalarVectorFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Linear interpolation function
     * <pre>
     * y <- interp.lin(e,v1,v2)
     * </pre>
     */
    class InterpLin : public ScalarVectorFunction
    {
    public:
	InterpLin ();
	double scalarEval(std::vector<double const *> const &args,
			  std::vector<unsigned long> const &lengths)
	    const override;
	bool checkParameterLength(std::vector<unsigned long> const &len)
	    const override;
	bool checkParameterValue(std::vector <double const *> const &args,
				 std::vector <unsigned long> const &lengths)
	    const override;
    };

}}

#endif /* FUNC_INTERP_LIN_H_ */
