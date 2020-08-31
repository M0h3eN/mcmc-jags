#ifndef DIRICHLET_METROPOLIS_H_
#define DIRICHLET_METROPOLIS_H_

#include <sampler/RWMetropolis.h>

namespace jags {

class GraphView;

namespace bugs {

class DirchMetropolis : public RWMetropolis
{
    GraphView const *_gv;
    unsigned int _chain;
    double _s;
public:
    DirchMetropolis(GraphView const *gv, unsigned int chain);
    void getValue(std::vector<double> &x) const override;
    void setValue(std::vector<double> const &x) override;
    void step(std::vector<double> &x, double size, RNG *rng) const override;
    double logJacobian(std::vector<double> const &x) const override;
    double logDensity() const override;
};

}}

#endif /* DIRICHLET_METROPOLIS_H_ */
