#ifndef RE_GAMMA_SLICER_H_
#define RE_GAMMA_SLICER_H_

#include <sampler/Slicer.h>

namespace jags {
    namespace glm {

	class REGamma;

	class REGammaSlicer : public Slicer
	{
	    REGamma const *_regamma;
	    double const *_shape;
	    double const *_rate;
	    double _sigma, _sigma0;
	  public:
	    REGammaSlicer(REGamma const *regamma,
			  double const *shape, double const *rate,
			  double sigma);
	    double value() const override;
	    void setValue(double x) override;
	    void getLimits(double *lower, double *upper) const override;
	    double logDensity() const override;
	    void setSigma(double x);
	    void update(RNG *rng) override;
	};
	
    }
}

#endif /* RE_GAMMA_SLICER_H_ */
