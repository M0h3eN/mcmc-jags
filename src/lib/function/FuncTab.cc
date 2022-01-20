#include <config.h>
#include <function/FuncTab.h>
#include <function/LinkFunction.h>

using std::string;
using std::pair;

namespace jags {

    static string const &linkName(FunctionPtr const &func)
    {
	static const string _null = "";
	if (LINK(func)) 
	    return LINK(func)->linkName();
	else
	    return _null;
    }
    
    FuncTab::FuncTab()
	: _fmap(), _lmap(), _nullfun()
    {
	//Required by Solaris Studio, which won't create a default constructor
	//with -std=c++11
    }

    void FuncTab::insert (FunctionPtr const &func)
    {
	//Insert function into map by name and by alias
	string const &fname = func.name();
	if (!fname.empty() && _fmap.find(fname) == _fmap.end()) {
	    pair<string, FunctionPtr> fpair(fname, func);
	    _fmap.insert(fpair);
	}
	string const aname = func.alias();
	if (!aname.empty() && _fmap.find(aname) == _fmap.end()) {
	    pair<string, FunctionPtr> fpair(aname, func);
	    _fmap.insert(fpair);
	}
	//Insert link functions into link map by link name
	string const &lname = linkName(func);
	if (!lname.empty() && _lmap.find(lname) == _lmap.end()) {
	    pair<string, LinkFunction const *> lpair(lname, LINK(func));
	    _lmap.insert(lpair);
	}
    }

    FunctionPtr const &FuncTab::find(string const &name) const
    {
	auto p = _fmap.find(name);
	return p == _fmap.end() ? _nullfun : p->second;
    }

    LinkFunction const * FuncTab::findLink (string const &name) const
    {
	auto p = _lmap.find(name);
	return p == _lmap.end() ? nullptr : p->second;
    }

    void FuncTab::erase(FunctionPtr const &func)
    {
	for (auto p = _fmap.begin(); p != _fmap.end(); ++p) {
	    if (p->second == func) {
		_fmap.erase(p);
		break;
	    }
	}
	if (LINK(func)) {
	    for (auto p = _lmap.begin(); p != _lmap.end(); ++p) {
		if (p->second == LINK(func)) {
		    _lmap.erase(p);
		    break;
		}
	    }
	}
    }

} //namespace jags
