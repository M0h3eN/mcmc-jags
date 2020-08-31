#ifndef TRACE_MONITOR_H_
#define TRACE_MONITOR_H_

#include <model/Monitor.h>
#include <model/NodeArraySubset.h>

#include <vector>

namespace jags {
    namespace base {

	/**
	 * @short Stores sampled values of a given Node
	 */
	class TraceMonitor : public Monitor {
	    NodeArraySubset _subset;
	    std::vector<std::vector<double> > _values; // sampled values
	  public:
	    TraceMonitor(NodeArraySubset const &subset);
	    void update() override;
	    std::vector<double> const &value(unsigned int chain) const override;
	    std::vector<unsigned long> dim() const override;
	    bool poolChains() const override;
	    bool poolIterations() const override;
	};
	
    }
}

#endif /* TRACE_MONITOR_H_ */
