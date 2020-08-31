#ifndef FUNC_MEAN_H_
#define FUNC_MEAN_H_

#include <function/ScalarVectorFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Mean function
     * Mean calculates the mean of the elements of an array
     * @see SD
     * <pre>
     * y <- mean(x[])
     * </pre>
     */
    class Mean : public ScalarVectorFunction
    {
    public:
	Mean ();
	double scalarEval(std::vector<double const *> const &args,
			  std::vector<unsigned long> const &lengths)
	    const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *grad,
		      std::vector<double const *> const &args,
		      std::vector<unsigned long> const &lengths,
		      unsigned long i) const override;
	bool isScale(std::vector<bool> const &mask,
		     std::vector<bool> const &fix) const override;
    };

}}

#endif /* FUNC_MEAN_H_ */
