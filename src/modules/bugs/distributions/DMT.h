#ifndef DMT_H_
#define DMT_H_

#include <distribution/ArrayDist.h>

namespace jags {
namespace bugs {

/**
 * @short Multivariate t distribution
 * <pre>
 * x[] ~ dmt(mu[], T[,], k)
 * </pre>
 */
class DMT: public ArrayDist {
public:
  DMT();

  double logDensity(double const *x, PDFType type,
		    std::vector<double const *> const &parameters,
		    std::vector<std::vector<unsigned long> > const &dims)
      const override;
  void randomSample(double *x,
		    std::vector<double const *> const &parameters,
		    std::vector<std::vector<unsigned long> > const &dims,
		    RNG *rng) const override;
  /**
   * Checks that mu is a vector, T is a square matrix and the sizes of
   * mu and T conform.
   */
  bool checkParameterDim(std::vector<std::vector<unsigned long> > const &dims) 
      const override;
  /**
   * Checks that T is symmetric and that k >= 2. Note that there is
   * currently NO CHECK that T is positive definite.
   */
  bool checkParameterValue(std::vector<double const *> const &parameters,
                           std::vector<std::vector<unsigned long> > const &dims)
      const override;
  std::vector<unsigned long> 
      dim(std::vector<std::vector<unsigned long> > const &dims) const override;
  void support(double *lower, double *upper,
	       std::vector<double const *> const &parameters,
               std::vector<std::vector<unsigned long> > const &dims)
      const override;
  bool isSupportFixed(std::vector<bool> const &fixmask) const override;
  void score(double *s, double const *x,
	     std::vector<double const *> const &parameters,
	     std::vector<std::vector<unsigned long>> const &dims, 
	     unsigned long i) const override;
};

}}

#endif /* DMT_H_ */
