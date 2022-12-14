#ifndef WAIC_MONITOR_FACTORY_H_
#define WAIC_MONITOR_FACTORY_H_

#include <model/MonitorFactory.h>

namespace jags {
    namespace dic {
		
	// Note:  now retired (along with WAICMonitor) - will be removed before next release
	class WAICMonitorFactory : public MonitorFactory
	{
	public:
	    Monitor *getMonitor(std::string const &name, Range const &range,
				BUGSModel *model, std::string const &type,
				std::string &msg) override;
	    std::string name() const override;
	};
    
    }
}

#endif /* WAIC_MONITOR_FACTORY_H_ */
