#ifndef SUPER_DUPER_RNG_H_
#define SUPER_DUPER_RNG_H_

#include <rng/RmathRNG.h>

namespace jags {
namespace base {

    class SuperDuperRNG : public RmathRNG
    {
	unsigned int I[2];
	void fixupSeeds();
    public:
	SuperDuperRNG(unsigned int seed, NormKind norm_kind);
	double uniform() override;
	void init(unsigned int seed) override;
	bool setState(std::vector<int> const &state) override;
	void getState(std::vector<int> &state) const override;
    };

}}

#endif /* SUPER_DUPER_RNG_H_ */
