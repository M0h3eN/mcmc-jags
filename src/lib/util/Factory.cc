#include <util/Factory.h>

namespace jags {

    Factory::Factory() : _active(true)
    {
    }

    Factory::~Factory()
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
