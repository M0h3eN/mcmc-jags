#include <util/Factory.h>

namespace jags {

    Factory::Factory() : _active(true)
    {
    }

    void Factory::setActive(bool active)
    {
	_active = active;
    }

    bool Factory::isActive() const
    {
	return _active;
    }
}
