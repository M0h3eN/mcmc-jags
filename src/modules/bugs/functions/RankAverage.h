#ifndef FUNC_RANK_AVERAGE_H_
#define FUNC_RANK_AVERAGE_H_

#include <function/VectorFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short RankAverage function
     *
     * Calculates the sample ranks of the values in a vector using the
     * "average" method for ties. 
     *
     * <pre>
     * y <- rank.average(x[])
     * </pre>
     *
     * @see Order
     */
    class RankAverage : public VectorFunction
    {
    public:
	RankAverage ();
	void evaluate(double *value, 
		      std::vector<double const *> const &args,
		      std::vector<unsigned long> const &lengths) const override;
	unsigned long length(std::vector<unsigned long> const &parlengths,
			    std::vector<double const *> const &parvalues)
	    const override;
    };
    
}}

#endif /* FUNC_RANK_AVERAGE_H_ */
