#ifndef VECTOR_LOG_DENSITY_H_
#define VECTOR_LOG_DENSITY_H_

#include <function/VectorFunction.h>

namespace jags {
    
    class VectorDist;

    /**
     * @short Log density function for a vector-valued Distribution
     */
    class VectorLogDensity : public VectorFunction
    {
	VectorDist const *_dist;
    public:
	VectorLogDensity(VectorDist const *dist);
	unsigned long length(std::vector<unsigned long> const &lengths,
			    std::vector<double const *> const &values)
	    const override;
	bool checkParameterLength(std::vector<unsigned long> const &lens)
	    const override;
	bool checkParameterValue(std::vector<double const *> const &args,
				 std::vector<unsigned long> const &lens)
	    const override;
	void evaluate(double *value,
		      std::vector <double const *> const &args,
		      std::vector<unsigned long> const &lens) const override;
	bool hasGradient(unsigned long i) const override;
	void gradient(double *grad, std::vector<double const *> const &args,
		      std::vector<unsigned long> const &lengths,
		      unsigned long i) const override;
    };

}

#endif /* VECTOR_LOG_DENSITY_H_ */
