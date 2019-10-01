#ifndef DGAMPOIS_H_
#define DGAMPOIS_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace bugs {

/**
 * <pre>
 * x ~ dgampois(m, s)
 * f(x|m,s) = ((x+s-1)!/(x!*(s-1)!)) * ( s/(s+m) )^s * (1- s/(s+m))^x
 * </pre>
 * 
 * This is equivalent to the negative binomial distribution dnegbin(p,
 * s) where p = s/(s+m). The dgampois distribution has mean m and
 * variance m*(s+m)/s. It can be derived as Gamma mixture of Poisson
 * random variables where the gamma mixture variable has a mean of m
 * and a rate of s. As s tends to infinity the dgampois distribution
 * converges to a Poisson distribution with mean m.
 *
 * @short Gamma-Poisson compound distribution
 */
class DGamPois : public RScalarDist {
 public:
  DGamPois();
  double d(double x, PDFType type,
	   std::vector<double const *> const &parameters, 
	   bool give_log) const;
  double p(double q, std::vector<double const *> const &parameters, bool lower,
	   bool give_log) const;
  double q(double p, std::vector<double const *> const &parameters, bool lower,
	   bool log_p) const;
  double r(std::vector<double const *> const &parameters, RNG *rng) const;
  /**
   * Checks that p lies in the interval (0,1) and r > 0
   */
  bool checkParameterValue(std::vector<double const *> const &parameters) const;
  double KL(std::vector<double const *> const &par0,
	    std::vector<double const *> const &par1) const;
    bool hasScore(unsigned long i) const;
    double score(double x, std::vector<double const *> const &parameters,
		 unsigned long i) const;
    
};

}}

#endif /* DGAMPOIS_H_ */
