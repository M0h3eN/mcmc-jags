#ifndef FUNC_PROD_H_
#define FUNC_PROD_H_

#include <function/ScalarVectorFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Product of an array
     * Sum calculates the product of all arguments
     * @see Sum
     * <pre>
     * y <- prod(x1[], x2[], ...)
     * </pre>
     */
    class Prod : public ScalarVectorFunction
    {
    public:
	Prod ();
	double scalarEval(std::vector <double const *> const &args,
			  std::vector<unsigned long> const &lengths)
	    const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *x, std::vector <double const *> const &args,
		      std::vector<unsigned long> const &lengths,
		      unsigned long i) const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
    };

}}

#endif /* FUNC_PROD_H_ */
