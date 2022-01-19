#ifndef COUNTER_H_
#define COUNTER_H_

#include <vector>

namespace jags {

    /**
     * @short Mutable index that traverses a BUGS-language "for" loop
     *
     * The Counter class is used to represent counters in "for" loops in the
     * BUGS language. A Counter is a scalar RangeIterator.
     *
     * <pre>
     * for (i in 1:N) {
     * }
     * </pre>
     */
    class Counter 
    {
	const std::vector<unsigned long> _index_range;
	std::vector<unsigned long>::const_iterator _p;
    public:
	/**
	 * Create a counter
	 *
	 * @param index_range The range of possible values that the counter can take.
	 */
	Counter(std::vector<unsigned long> const &index_range);
	/**
	 * Returns the current value of the counter. On construction the counter
	 * takes the first value in the given index range.
	 */
	unsigned long value() const;
	/**
	 * Moves the counter onto the next value
	 */
	void next();
	/**
	 * Returns true if the counter has reached the end of the index range
	 */
	bool atEnd() const;
    };
    
} /* namespace jags */

#endif /* COUNTER_H_ */

