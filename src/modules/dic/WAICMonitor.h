#ifndef WAIC_MONITOR_H_
#define WAIC_MONITOR_H_

#include <model/Monitor.h>

#include <vector>

namespace jags {

    class StochasticNode;
    struct RNG;
    
    namespace dic {

	class WAICMonitor : public Monitor {
	    std::vector<StochasticNode const *> _snodes;
	    unsigned int _nchain;
	    std::vector<std::vector<double> > _mlik;
	    std::vector<std::vector<double> > _vlik;
	    std::vector<double> _values;
	    unsigned int _n;

	public:
	    WAICMonitor(std::vector<StochasticNode const *> const &snodes);
	    ~WAICMonitor() override;
	    std::vector<unsigned long> dim() const override;
	    std::vector<double> const &value(unsigned int chain) const override;
	    bool poolChains() const override;
	    bool poolIterations() const override;
	    void update() override;
	};

    }
}

#endif /* WAIC_MONITOR_H_ */
