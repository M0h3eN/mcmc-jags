#ifndef DET_H_
#define DET_H_

#include <function/ArrayFunction.h>

namespace jags {
namespace bugs {

    /**
     * @short Determinant 
     * Det calculates the determinant of a square matrix using the QR
     * decomposition.
     * <pre>
     * y <- det(x)
     * y = |x| for x an n x n matrix
     * </pre>
     */
    class Det : public ArrayFunction
    {
    public:
	Det ();
	void evaluate(double *x, std::vector<double const *> const &args,
		      std::vector<std::vector<unsigned long> > const &dims) 
	    const override;
	bool checkParameterDim(std::vector<std::vector<unsigned long>>
			       const &dims) const override;
	std::vector<unsigned long>
	    dim(std::vector<std::vector<unsigned long> > const &dims,
		std::vector<double const *> const &values) const override;
    };

}}

#endif /* DET_H_ */
