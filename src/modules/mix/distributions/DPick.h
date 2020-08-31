#ifndef DPICK_H_
#define DPICK_H_

#include <distribution/ScalarDist.h>

namespace jags {
    namespace mix {

	class DPick : public ScalarDist {
	  public:
	    DPick();

	    double logDensity(double const x, PDFType type,
			      std::vector<double const *> const &parameters,
			      double const *lower, double const *upper)
		const override;
	    double randomSample(std::vector<double const *> const &parameters,
				double const *lower, double const *upper,
				RNG *rng)
		const override;
	    double l(std::vector<double const *> const &parameters)
		const override;
	    double u(std::vector<double const *> const &parameters)
		const override;
	    bool isSupportFixed(std::vector<bool> const &fixmask)
		const override;
	    bool checkParameterValue(std::vector<double const *> const &par)
		const override;
	    bool isDiscreteValued(std::vector<bool> const &mask)
		const override;
	};
	
    }
}


#endif /* DPICK_H_ */
