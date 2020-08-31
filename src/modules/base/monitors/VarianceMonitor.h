#ifndef VARIANCE_MONITOR_H_
#define VARIANCE_MONITOR_H_

#include <model/Monitor.h>
#include <model/NodeArraySubset.h>

#include <vector>

namespace jags {
namespace base {

    /**
     * @short Stores running variance of a given Node
     */
    class VarianceMonitor : public Monitor {
	NodeArraySubset _subset;
	std::vector<std::vector<double> > _means;
	std::vector<std::vector<double> > _mms;
	std::vector<std::vector<double> > _variances;
	unsigned int _n;
	
    public:
	VarianceMonitor(NodeArraySubset const &subset);
	void update() override;
	std::vector<double> const &value(unsigned int chain) const override;
	std::vector<unsigned long> dim() const override;
	bool poolChains() const override;
	bool poolIterations() const override;
	};

}}

#endif /* VARIANCE_MONITOR_H_ */
