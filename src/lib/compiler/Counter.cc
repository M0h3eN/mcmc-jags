#include <config.h>
#include <compiler/Counter.h>

#include <stdexcept>
#include <string>

using std::logic_error;

namespace jags {
 
    Counter::Counter(std::vector<unsigned long> const &index_range)
	: _index_range(index_range), _p(_index_range.begin())
    {
	
    }
    
    void Counter::next()
    {
	++_p;
    }

    unsigned long Counter::value() const
    {
	return *_p;
    }

    bool Counter::atEnd() const
    {
	return _p == _index_range.end();
    }

} //namespace jags
