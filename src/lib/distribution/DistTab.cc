#include <config.h>
#include <distribution/DistTab.h>

#include <map>

using std::map;
using std::string;
using std::pair;

namespace jags {

    DistTab::DistTab()
	: _dmap(), _nulldist()
    {
	//Required by Solaris Studio, which won't create a default constructor
	//with -std=c++11
    }

    void DistTab::insert (DistPtr const &dist)
    {
	//Insert distribution into map by name and by alias
	string const &dname = dist.name();
	if (!dname.empty() && _dmap.find(dname) == _dmap.end()) {
	    pair<string, DistPtr> dpair(dname, dist);
	    _dmap.insert(dpair);
	}
	string const aname = dist.alias();
	if (!aname.empty() && _dmap.find(aname) == _dmap.end()) {
	    pair<string, DistPtr> dpair(aname, dist);
	    _dmap.insert(dpair);
	}
    }

    DistPtr const &DistTab::find(string const &name) const
    {
	auto p = _dmap.find(name);
	return p == _dmap.end() ? _nulldist : p->second;
    }

    void DistTab::erase(DistPtr const &dist)
    {
	for (auto p = _dmap.begin(); p != _dmap.end(); ++p) {
	    if (p->second == dist) {
		_dmap.erase(p);
		break;
	    }
	}
    }

} //namespace jags
