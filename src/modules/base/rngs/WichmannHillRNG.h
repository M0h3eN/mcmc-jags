#ifndef WICHMANN_HILL_RNG_H_
#define WICHMANN_HILL_RNG_H_

#include <rng/RmathRNG.h>

namespace jags {
namespace base {

    class WichmannHillRNG : public RmathRNG
    {
	unsigned int I[3];
	void fixupSeeds();
    public:
	WichmannHillRNG(unsigned int seed, NormKind norm_kind);
	double uniform() override;
	void init(unsigned int seed) override;
	bool setState(std::vector<int> const &state) override;
	void getState(std::vector<int> &state) const override;
    };

}}

#endif /* WICHMANN_HILL_RNG_H_ */
