#ifndef DORDERED_H_
#define DORDERED_H_

#include <distribution/VectorDist.h>

namespace jags {
    namespace glm {

	/**
	 * @short Base class for ordered categorical distributions
	 */
	class DOrdered : public VectorDist {
	private:
	    double density(double x, double mu, double const *cut,
			   unsigned long ncut, bool give_log)  const;
	public:
	    DOrdered(std::string const &name);
	    
	    double logDensity(double const *x,
			      PDFType type,
			      std::vector<double const *> const &parameters,
			      std::vector<unsigned long> const &lengths)
		const override;
	    void randomSample(double *x,
			      std::vector<double const *> const &parameters,
			      std::vector<unsigned long> const &lengths,
			      RNG *rng)  const override;
	    bool checkParameterValue(std::vector<double const*> const &par,
				     std::vector<unsigned long> const &lengths)
		 const override;
	    void support(double *lower, double *upper,
			 std::vector<double const *> const &parameters,
			 std::vector<unsigned long> const &lengths)
		const override;
	    bool isSupportFixed(std::vector<bool> const &fixmask)
		const override;
	    bool isDiscreteValued(std::vector<bool> const &mask) const override;
	    bool checkParameterLength(std::vector<unsigned long> const &lengths)
		 const override;
	    unsigned long length(std::vector<unsigned long> const &lengths)
		const override;
	    double KL(std::vector<double const *> const &par0,
		      std::vector<double const *> const &par1,
		      std::vector<unsigned long> const &lengths) const override;
	    virtual double r(double mu, RNG *rng) const = 0;
	    virtual double p(double x, double mu, bool lower, bool give_log)
		const = 0;
	};

    }
}

#endif /* DORDERED_H_ */
