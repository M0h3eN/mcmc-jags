#ifndef R_SCALAR_DIST_H_
#define R_SCALAR_DIST_H_

#include <distribution/ScalarDist.h>

namespace jags {

struct RNG;

/**
 * @short Scalar Distribution using R math library infrastructure.
 *
 * A subclass of RScalarDist has to implement the d,p,q, and r virtual
 * member functions. These are based on the d-p-q-r functions provided
 * by libRmath.
 *
 * The JAGS versions of most (but not all) scalar distributions extend
 * the distribution families in libRmath by allowing the distribution
 * to be bounded.
 */
class RScalarDist : public ScalarDist
{
    const bool _discrete;
    double calPlower(double, std::vector<double const *> const &) const;
    double calPupper(double, std::vector<double const *> const &) const;
public:
    /**
     * Constructor
     *
     * @param name BUGS language name of distribution
     *
     * @param npar Number of parameters, excluding upper and lower bound
     *
     * @param support Support of distribution
     *
     * @param discrete Boolean flag indicating whether the distribution is
     *        discrete valued.
     */
    RScalarDist(std::string const &name, unsigned int npar, Support support,
		bool discrete=false);
    double logDensity(double x, PDFType type,
		      std::vector<double const *> const &parameters,
		      double const *lower, double const *upper) const override;
    double randomSample(std::vector<double const *> const &parameters,
			double const *lower, double const *upper,
			RNG *rng) const override;
    /**
     * Density function, ignoring bounds
     * @param x value at which to evaluate the density
     * @param type Type of density calculation required.
     * @param parameters Array of parameters
     * @param give_log Indicates whether to return log density. 
     */
    virtual double d(double x, PDFType type,
		     std::vector<double const *> const &parameters, 
		     bool give_log) const = 0;
    /**
     * Distribution function, ignoring bounds
     * @param x quantile at which to evaluate the distribution function
     * @param parameters Array of parameters
     * @param lower If true, return value is P[X <= x]. Otherwise
     * P[X > x]
     * @param give_log Indicates whether to return log probabability
     */
    virtual double p(double x, std::vector<double const *> const &parameters, 
		     bool lower, bool give_log) const = 0;
    /**
     * Quantile function, ignoring bounds
     * @param p probability for which to evaluate quantile
     * @param parameters Array of parameters
     * @param log_p Indicates whether p is given as log(p). 
     */
    virtual double q(double p, std::vector<double const *> const &parameters, 
		     bool lower, bool log_p) const = 0;
    /**
     * Random number generation, ignoring bounds
     * @param parameters Array of parameters
     */
    virtual double 
	r(std::vector<double const *> const &parameters, RNG *rng) const = 0;
    /**
     * All RScalarDist distributions can be bounded
     */
    bool canBound() const override;
    /**
     * RScalarDist distributions are defined to have support on the
     * integers or on the real line by the constructor. The result of
     * isDiscreteValued does not depend on the argument mask. Hence
     * this function may be called with a default empty mask.
     */
    bool isDiscreteValued(std::vector<bool> const &mask=std::vector<bool>())
	const override;
};

    /**
     * Convenience function that calculates x * log(0) as the limit of
     * x * log(p) as p tends to zero.  This is required for calculation
     * of some density functions.
     *
     * @param x coefficient of log(0)
     * @param give_log logical flag. If true then the limit of x*log(p)
     * is returned, otherwise the limit of p^x.
     */
    double xlog0(double x, bool give_log);

}

#endif /* SCALAR_DIST_RMATH_H_ */

