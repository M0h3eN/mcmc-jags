#include <config.h>
#include <compiler/CounterTab.h>

#include <string>

using std::vector;
using std::pair;
using std::string;

namespace jags {

    CounterTab::CounterTab()
    {
    }

    CounterTab::~CounterTab()
    {
	unsigned long n = _table.size();
	for (unsigned int i = 0; i < n; i++) {
	    popCounter();
	}
    }

    Counter * CounterTab::pushCounter(string const &name, vector<unsigned long> const &index_range)
    {
	Counter *counter = new Counter(index_range);
	pair<string, Counter*> cpair(name, counter);
	_table.push_back(cpair);
	return counter;
    }

    void CounterTab::popCounter()
    {
	pair<string, Counter *>  &topcpair = _table.back();
	delete topcpair.second;
	_table.pop_back();
    }

    Counter *CounterTab::getCounter(string const &name) const
    {
	for (auto p = _table.begin(); p != _table.end(); ++p) {
	    if (name == p->first)
		return p->second;
	}
	return nullptr;
    }

    vector<unsigned long> CounterTab::counterValues() const
    {
	vector<unsigned long> indices;
	for (auto p = _table.begin(); p != _table.end(); ++p) {
	    indices.push_back(p->second->value());
	}
	return indices;
    }
    
} //namespace jags
