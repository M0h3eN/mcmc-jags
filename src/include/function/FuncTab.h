#ifndef FUNC_TAB_H_
#define FUNC_TAB_H_

#include <map>
#include <string>

#include <function/FunctionPtr.h>

namespace jags {

/**
 * @short Look-up table for Function objects
 *
 * The FuncTab class provides a means of looking up Functions by their
 * name in the BUGS language.
 *
 * @see Function DistTab 
 */
class FuncTab
{
    std::map<std::string, FunctionPtr> _fmap;
    std::map<std::string, LinkFunction const *> _lmap;
    const FunctionPtr _nullfun;
public:
    /**
     * Constructs a new empty FuncTab
     */
    FuncTab();
    /**
     * Inserts a function into the table. 
     */
    void insert (FunctionPtr const &func);
    /**
     * Finds the inverse of a link function by name
     *
     * @param name Name of the link function
     *
     * @return Pointer to the inverse link function or a NULL pointer
     * if it was not found.
     */
    LinkFunction const *findLink (std::string const &name) const;
    /**
     * Finds a function by name.
     *
     * @param name Name of the function
     *
     * @return a polymorphic function pointer. If the function cannot be
     * found, then the pointer is a null FunctionPtr object.
     */
    FunctionPtr const &find(std::string const &name) const;
    /**
     * Removes a function from the table. 
     */
    void erase(FunctionPtr const &func);
};

} /* namespace jags */

#endif /* FUNC_TAB_H_ */
