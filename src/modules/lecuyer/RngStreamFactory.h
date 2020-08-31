#ifndef RNG_STREAM_FACTORY_H_
#define RNG_STREAM_FACTORY_H_

#include <rng/RNGFactory.h>
#include "RngStream.h"

namespace jags {
namespace lecuyer {
    
/**
 * @short Factory object for Lecuyer RNG Stream
 */
    class RngStreamFactory : public RNGFactory
    {
	double Bg[6], Ig[6];
	std::vector<RNG*> _rngvec;
    public:
	RngStreamFactory();
	~RngStreamFactory() override;
	void setSeed(unsigned int seed) override;
	void nextStream();
	void nextSubstream();
	std::vector<RNG *> makeRNGs(unsigned int n) override;
	RNG * makeRNG(std::string const &name) override;
	std::string name() const override;
    };

}}

#endif /* RNG_STREAM_FACTORY_H_ */
