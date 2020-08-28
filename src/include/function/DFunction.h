#ifndef D_FUNCTION_H_
#define D_FUNCTION_H_

#include "DPQFunction.h"

namespace jags {

    /**
     * @short Density function for an R Scalar Distribution
     */
    class DFunction : public DPQFunction
    {
    public:
	DFunction(RScalarDist const *dist);
	bool checkParameterDiscrete(std::vector<bool> const &mask)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	double evaluate(std::vector <double const *> const &args)
	    const override;
    };

}

#endif /* D_FUNCTION_H_ */
