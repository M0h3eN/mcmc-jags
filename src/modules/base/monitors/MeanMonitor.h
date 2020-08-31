#ifndef MEAN_MONITOR_H_
#define MEAN_MONITOR_H_

#include <model/Monitor.h>
#include <model/NodeArraySubset.h>

#include <vector>

namespace jags {
namespace base {

    /**
     * @short Stores running mean of a given Node
     */
    class MeanMonitor : public Monitor {
	NodeArraySubset _subset;
	std::vector<std::vector<double> > _values; // sampled values
	unsigned int _n;
    public:
	MeanMonitor(NodeArraySubset const &subset);
	void update() override;
	std::vector<double> const &value(unsigned int chain) const override;
	std::vector<unsigned long> dim() const override;
	bool poolChains() const override;
	bool poolIterations() const override;
    };

}}

#endif /* MEAN_MONITOR_H_ */
