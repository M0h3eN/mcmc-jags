#ifndef Q_FUNCTION_H_
#define Q_FUNCTION_H_

#include "DPQFunction.h"

namespace jags {

    /**
     * @short Quantile function for an R Scalar Distribution
     */
    class QFunction : public DPQFunction
    {
    public:
	QFunction(RScalarDist const *dist);
	bool checkParameterDiscrete(std::vector<bool> const &mask)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &args)
	    const override;
	double evaluate(std::vector <double const *> const &args)
	    const override;
    };

}

#endif /* Q_FUNCTION_H_ */
