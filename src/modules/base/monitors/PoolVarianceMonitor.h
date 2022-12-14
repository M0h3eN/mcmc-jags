#ifndef POOLVARIANCE_MONITOR_H_
#define POOLVARIANCE_MONITOR_H_

#include <model/Monitor.h>
#include <model/NodeArraySubset.h>

#include <vector>

namespace jags {
namespace base {

    /**
     * @short Stores running variance (pooled between chains) of a given Node
     */
    class PoolVarianceMonitor : public Monitor {
	NodeArraySubset _subset;
	std::vector<double> _means;
	std::vector<double> _mms;
	std::vector<double> _variances;
	unsigned int _n;
	
    public:
	PoolVarianceMonitor(NodeArraySubset const &subset);
	void update() override;
	std::vector<double> const &value(unsigned int chain) const override;
	std::vector<unsigned long> dim() const override;
	bool poolChains() const override;
	bool poolIterations() const override;
	};

}}

#endif /* POOLVARIANCE_MONITOR_H_ */
