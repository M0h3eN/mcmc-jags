#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>

namespace jags {
    
    /**
     * @short Abstract base class for Factory objects
     */
    class Factory {
	bool _active;
    public:
	/**
	 * Constructs a new Factory in an active state.
	 */
	Factory();
	virtual ~Factory();
	/**
	 * Sets the factory to an active or inactive state. Inactive
	 * factories are ignored by the compiler.
	 *
	 * @param active Boolean flag. If true then the factory is set
	 * to actove, otherwise inactive.
	 */
	void setActive(bool active);
	/**
	 * Indicates whether the factory is in an active state.
	 */
	bool isActive() const;
	/**
	 * Returns the name of the factory.
	 */
	virtual std::string name() const = 0;
    };
    
} /* namespace jags */

#endif /* FACTORY_H_ */
