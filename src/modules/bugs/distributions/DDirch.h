#ifndef DDIRCH_H_
#define DDIRCH_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace bugs {

/**
 * @short Dirichlet distribution
 *
 * Zero shape parameters are allowed.  These represent structural
 * zeros: when x ~ ddirch(alpha) is forward sampled, x[i] = 0 when
 * alpha[i] = 0. 
 *
 * <pre>
 * p[] ~ ddirch(alpha[])
 * f(p | alpha) = C * prod(p^(alpha-1))
 * </pre>
 */
class DDirch : public VectorDist {
public:
    DDirch();
    std::string alias() const override;
    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths, RNG *rng)
	const override;
    void randomSample(double *x, std::vector<bool> const &observed,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths, RNG *rng)
	const override;
    unsigned long length(std::vector<unsigned long> const &lengths)
	const override;
    /**
     * Checks that alpha is a vector of length at least 2
     */
    bool checkParameterLength(std::vector<unsigned long> const &lengths)
	const override;
    /**
     * Checks that each element of alpha is >= 0.
     *
     * Structural zeros are allowed in the Dirichlet distribution.
     * These are represented by the elements of alpha that are set to
     * zero.  This is permitted only if alpha is fixed and there is at
     * least one non-zero element of alpha.
     */
    bool checkParameterValue(std::vector<double const *> const &parameters,
			     std::vector<unsigned long> const &lengths)
	const override;
    void support(double *lower, double *upper,
		 std::vector<double const *> const &parameters,
		 std::vector<unsigned long> const &lengths) const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool fullRank() const override;
    double KL(std::vector<double const *> const &par0,
	      std::vector<double const *> const &par1,
	      std::vector<unsigned long> const &len) const override;
    bool hasScore(unsigned long i) const override;
    void score(double *score, double const *x,
	       std::vector<double const *> const &par,
	       std::vector<unsigned long> const &len,
	       unsigned long i) const override;

};

}}

#endif /* DDIRCH_H_ */
