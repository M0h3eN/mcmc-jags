#ifndef MUTABLE_SAMPLER_H_
#define MUTABLE_SAMPLER_H_

#include <sampler/Sampler.h>

namespace jags {

    struct RNG;
    class MutableSampleMethod;

    /**
     * @short Samples multiple chains in parallel 
     *
     * A vector of MutableSampleMethod objects is used to update each
     * chain in parallel.
     */
    class MutableSampler : public Sampler
    {
	std::vector<MutableSampleMethod*> _methods;
	const std::string _name;
      public:
	/**
	 * Constructor.
	 *
	 * @param gv View of the sample graph, passed directly to the
	 * parent class Sampler, which takes ownership of it
	 *
	 * @param methods Vector of pointers to MutableSampleMethod
	 * objects, of length equal to the number of chains.  These
	 * must be dynamically allocated, as the
	 * MutableSampler will take ownership of them, and
	 * will delete them when its destructor is called
	 *
	 * @param name The name of the sampler, which will be returned
	 * by the member function name.
	 */
	MutableSampler(GraphView *gv, 
		       std::vector<MutableSampleMethod*> const &methods,
		       std::string const &name);
	~MutableSampler() override;
	void update(unsigned int chain, RNG * rng) override;
	bool isAdaptive() const override;
	void adaptOff() override;
	bool checkAdaptation() const override;
	/**
	 * Returns the name of the sampler, as given to the constructor
	 */
	std::string name() const override;
    };

} /* namespace jags */

#endif /* MUTABLE_SAMPLER_H_ */
