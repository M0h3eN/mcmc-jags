#ifndef FUNC_LENGTH_H_
#define FUNC_LENGTH_H_

#include <function/ScalarVectorFunction.h>

namespace jags {
namespace base {
    
    /**
     * @short Length of a node
     */
    class Length: public ScalarVectorFunction
    {
    public:
	Length();
	double scalarEval(std::vector <double const *> const &args,
			  std::vector<unsigned long> const &lengths)
	    const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
    };

}}

#endif /* FUNC_LENGTH_H_ */
