#ifndef P_FUNCTION_H_
#define P_FUNCTION_H_

#include "DPQFunction.h"

namespace jags {

    /**
     * @short Cumulative distribution function for an R Scalar distribution
     */
    class PFunction : public DPQFunction
    {
    public:
	PFunction(RScalarDist const *dist);
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	double evaluate(std::vector <double const *> const &args)
	    const override;
    };

}

#endif /* P_FUNCTION_H_ */
