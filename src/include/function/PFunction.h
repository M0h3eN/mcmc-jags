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
	bool checkParameterDiscrete(std::vector<bool> const &args)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	double evaluate(std::vector <double const *> const &args)
	    const override;
	bool hasGradient(unsigned long i) const override;
	double gradient(std::vector<double const *> const &args,
			unsigned long i) const override;
    };

}

#endif /* P_FUNCTION_H_ */
