#ifndef DENSITY_TOTAL_H_
#define DENSITY_TOTAL_H_

#include <model/Monitor.h>
#include <graph/Node.h>

#include <vector>

#include "DensityEnums.h"

namespace jags {
    namespace dic {
	
   	/**
   	 * @short Stores trace of total (sum or product) of density/log density/deviance for a given set of Nodes
	 *
	 * Note that this class is used by both NodeDensityMonitorFactory and ObsStochDensMonitorFactory
   	 */
   	class DensityTotal : public Monitor {
 	  protected:
   	    std::vector<Node const *> const _nodes;
   	    std::vector<std::vector<double> > _values; // total density/log density/deviance corresponding to sampled values
		DensityType const _density_type;  // enum is defined in model/Monitor.h
		std::vector<unsigned long> const _dim;
		unsigned int const _nchain;
   	  public:
   	    DensityTotal(std::vector<Node const *> const &nodes, std::vector<unsigned long> const &dim, 
				DensityType const density_type, std::string const &monitor_name);
   	    void update() override;
   	    std::vector<double> const &value(unsigned int chain) const override;
   	    std::vector<unsigned long> dim() const override;
   	    bool poolChains() const override;
   	    bool poolIterations() const override;
   	};
	
}
}

#endif /* DENSITY_TOTAL_H_ */
