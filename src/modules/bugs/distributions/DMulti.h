#ifndef DMULTI_H_
#define DMULTI_H_

#include <distribution/VectorDist.h>

struct RNG;

namespace jags {
namespace bugs {

/**
 * <pre>
 * X[] ~ dmulti(p[], N)
 * f(x | p, N) = prod (p^x) ; sum(x) = N
 * </pre>
 * @short Multinomial distribution
 */
class DMulti : public VectorDist {
public:
  DMulti();

  double logDensity(double const *x, PDFType tpye, 
		    std::vector<double const *> const &parameters,
		    std::vector<unsigned long> const &lengths) const override;
  void randomSample(double *x,
		    std::vector<double const *> const &parameters,
		    std::vector<unsigned long> const &lengths,
		    RNG *rng) const override;
  void randomSample(double *x, std::vector<bool> const &observed,
		    std::vector<double const *> const &parameters,
		    std::vector<unsigned long> const &lengths,
		    RNG *rng) const override;
   /**
   * Checks that elements of p lie in range (0,1) and 
   * and sum to 1. Checks that N >= 1
   */
  bool checkParameterValue(std::vector<double const *> const &parameters,
                           std::vector<unsigned long> const &lengths)
      const override;
  /** Checks that N is a scalar */
  bool checkParameterLength(std::vector<unsigned long> const &lengths)
      const override;
  /** Checks that N is discrete-valued */
  bool checkParameterDiscrete(std::vector<bool> const &mask) const override;
  unsigned long length(std::vector<unsigned long> const &dim) const override;
  void support(double *lower, double *upper,
	       std::vector<double const *> const &parameters,
	       std::vector<unsigned long> const &lengths) const override;
  bool isSupportFixed(std::vector<bool> const &fixmask) const override;
  bool fullRank() const override;    
  bool isDiscreteValued(std::vector<bool> const &mask) const override;
  double KL(std::vector<double const *> const &par1,
	    std::vector<double const *> const &par2,
	    std::vector<unsigned long> const &lengths) const override;
  std::string alias() const override;
  bool hasScore(unsigned long i) const override;
  void score(double *s, double const *x,
	     std::vector<double const *> const &parameters,
	     std::vector<unsigned long> const &lengths,
	     unsigned long i) const override;
};

}}

#endif /* DMULTI_H_ */
