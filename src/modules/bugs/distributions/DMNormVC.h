#ifndef DMNORM_VC_H_
#define DMNORM_VC_H_

#include <distribution/ArrayDist.h>

namespace jags {

struct RNG;

namespace bugs {

/**
 * @short Multivariate normal distribution with mean-variance parameterization
 * <pre>
 * x[] ~ dmnorm.vcov(mu[], T[,])
 * f(x | mu, T) = exp(-1/2 * (x-mu) %*% inverse(T) %*% t(x-mu)) / sqrt(det(T))
 * </pre>
 */
class DMNormVC : public ArrayDist {
public:
  DMNormVC();

  double logDensity(double const *x, PDFType type,
		    std::vector<double const *> const &parameters,
		    std::vector<std::vector<unsigned long> > const &dims) const override;
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
   * Checks that T is symmetric. Note that there is currently NO CHECK
   * that T is positive definite.
   */
  bool checkParameterValue(std::vector<double const *> const &parameters,
                           std::vector<std::vector<unsigned long> > const &dims) 
      const override;
  std::vector<unsigned long> 
      dim(std::vector<std::vector<unsigned long> > const &dims) const override;
  /**
   * Convenience random sampler function 
   *
   * @param x  Array that will hold the result
   *
   * @param mu Array of mean values. A null pointer may be given, and in
   * this case a mean of zero is used.
   *
   * @param tau Either the precision matrix or the variance-covariance
   * matrix.  Only the lower triangle is used.
   * 
   * @param prec Logical flag. If true then tau represents the
   * precision matrix (the parameterization used in the bugs language).
   * If false then tau represents the variance-covariance matrix.
   *
   * @param nrow length of x and mu; number of rows of the square matrix tau
   *
   * @param rng Random number generator
   */
  static void randomsample(double *x, double const *mu, double const *tau,
			   bool prec, int nrow, RNG *rng);
  void support(double *lower, double *upper,
	       std::vector<double const *> const &parameters,
               std::vector<std::vector<unsigned long> > const &dims)
      const override;
  bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    /*
  static void randomsample(double *x, double const *mu, double const *Sigma,
			   unsigned long nrow,
			   std::vector<bool> const &observed,
			   unsigned long nobs,
			   RNG *rng);
    */
  bool hasScore(unsigned long i) const override;
  void score(double *s, double const *x,
	     std::vector<double const *> const &parameters,
	     std::vector<std::vector<unsigned long>> const &dims, 
	     unsigned long i) const override;
};

}}

#endif /* DMNORM_VC_H_ */
