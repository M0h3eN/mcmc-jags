#ifndef DCAT_H_
#define DCAT_H_

#include <distribution/VectorDist.h>

namespace jags {
namespace bugs {

/**
 * @short Categorical distribution
 * <pre>
 * R ~ dcat(p[])
 * f(r|p[]) = p[r] ; r in 1:length(p)
 * </pre>
 */
class DCat : public VectorDist {
public:
    DCat();

    double logDensity(double const *x, PDFType type,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths,
		      RNG *rng) const override;
    //FIXME: Not really required
    void randomSample(double *x, std::vector<bool> const &observed,
		      std::vector<double const *> const &parameters,
		      std::vector<unsigned long> const &lengths,
		      RNG *rng) const override;

    /**
     * Checks that all elements of p are positive
     */
    bool checkParameterValue(std::vector<double const*> const &parameters,
			     std::vector<unsigned long> const &lengths)
	const override;
    void support(double *lower, double *upper,
		 std::vector<double const *> const &parameters,
		 std::vector<unsigned long> const &lengths) const override;
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    bool checkParameterLength(std::vector<unsigned long> const &lengths)
	const override;
    unsigned long length(std::vector<unsigned long> const &lengths)
	const override;
    double KL(std::vector<double const *> const &par0,
	      std::vector<double const *> const &par1,
	      std::vector<unsigned long> const &lengths) const override;
    bool hasScore(unsigned long i) const override;
    void score(double *s, double const *x,
	       std::vector<double const *> const &parameters,
	       std::vector<unsigned long> const &lengths,
	       unsigned long i) const override;
};

}}

#endif /* DCAT_H_ */
