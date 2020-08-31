#ifndef REP_H_
#define REP_H_

#include <function/VectorFunction.h>

namespace jags {
    namespace bugs {

    /**
     * @short Replicate elements of a vector
     *
     * <pre>
     * y <- rep(x, times)
     * </pre>
     *
     */
    class Rep : public VectorFunction
    {
    public:
	Rep();
	void evaluate(double *value, 
		      std::vector <double const *> const &values,
		      std::vector <unsigned long> const &lengths)
	    const override;
	unsigned long length(std::vector <unsigned long> const &lengths,
			    std::vector <double const *> const &values)
	    const override;
	bool checkParameterLength(std::vector<unsigned long> const &args)
	    const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
	bool checkParameterDiscrete(std::vector<bool> const &mask)
	    const override;
	bool checkParameterFixed(std::vector<bool> const &mask) const override;
	bool checkParameterValue(std::vector<double const *> const &args,
				 std::vector<unsigned long> const &lens)
	    const override;
    };

    } /* namespace bugs */
} /* namespace jags */

#endif /* REP_H_ */
