#ifndef MNORM_METROPOLIS_H_
#define MNORM_METROPOLIS_H_

#include <sampler/Metropolis.h>

namespace jags {

    class SingletonGraphView;

namespace bugs {

class MNormMetropolis : public Metropolis
{
    SingletonGraphView const *_gv;
    unsigned int _chain;
    double *_mean;
    double *_var;
    double *_prec;
    unsigned int _n;
    unsigned int _n_isotonic;
    double _sump, _meanp;
    double _lstep;
    unsigned int _nstep;
    unsigned int _p_over_target;
public:
    MNormMetropolis(SingletonGraphView const *gv, unsigned int chain);
    ~MNormMetropolis() override;
    void rescale(double p) override;
    void update(RNG *rng) override;
    bool checkAdaptation() const override;
    void getValue(std::vector<double> &value) const override;
    void setValue(std::vector<double> const &value) override;
};

}}

#endif /* MNORM_METROPOLIS_H_ */
