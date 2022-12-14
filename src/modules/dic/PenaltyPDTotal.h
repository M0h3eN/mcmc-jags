#ifndef PENALTY_PD_TOTAL_H_
#define PENALTY_PD_TOTAL_H_

#include <model/Monitor.h>
#include <graph/Node.h>
#include <rng/RNG.h>

#include <vector>

namespace jags {
namespace dic {

    class PenaltyPDTotal : public Monitor {
	protected:
	std::vector<Node const *> const _nodes;
	std::vector<RNG *> _rngs;
	unsigned int _nrep;
	unsigned long _nchain;
	std::vector<double> _values;
	std::vector<unsigned long> const _dim;
	double _scale_cst;

	// Protected constructor for use by PenaltyPOPTTotal:
	PenaltyPDTotal(std::vector<Node const *> const &nodes,
		  std::string const &monitor_name,
		  std::vector<RNG *> const &rngs,
		  unsigned int nrep, double scale);

	public:
	PenaltyPDTotal(std::vector<Node const *> const &nodes,
		  std::string const &monitor_name,
		  std::vector<RNG *> const &rngs,
		  unsigned int nrep);

	~PenaltyPDTotal() override;
	std::vector<unsigned long> dim() const override;
	std::vector<double> const &value(unsigned int chain) const override;
	bool poolChains() const override;
	bool poolIterations() const override;
	void update() override;
	};

}}

#endif /* PENALTY_PD_TOTAL_H_ */
