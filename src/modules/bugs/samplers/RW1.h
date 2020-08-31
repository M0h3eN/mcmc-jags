#ifndef RW1_METROPOLIS_H_
#define RW1_METROPOLIS_H_

#include <sampler/Metropolis.h>
#include <sampler/StepAdapter.h>

namespace jags {

    class SingletonGraphView;

    namespace bugs {

	class RW1 : public Metropolis
	{
	    SingletonGraphView const *_gv;
	    unsigned int _chain;
	    StepAdapter _step_adapter;
	    double _pmean;
	    unsigned int _niter;
	  public:
	    RW1(SingletonGraphView const *gv, unsigned int chain);
	    ~RW1() override;
	    void rescale(double p) override;
	    void update(RNG *rng) override;
	    bool checkAdaptation() const override;
	    void getValue(std::vector<double> &value) const override;
	    void setValue(std::vector<double> const &value) override;
	};
    }
}

#endif /* RW1_METROPOLIS_H_ */
