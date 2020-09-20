#ifndef FUNC_SEQ_H_
#define FUNC_SEQ_H_

#include <function/VectorFunction.h>

namespace jags {
    namespace base {

    /**
     * @short Integer sequence
     *
     * The Seq function implements the infix operator ":" in the BUGS language.
     * The arguments must be integer.
     * <pre>
     * y <- a:b
     * </pre>
     *
     */
    class Seq : public VectorFunction
    {
    public:
	Seq();
	void evaluate(double *value, 
		      std::vector <double const *> const &values,
		      std::vector <unsigned long> const &lengths)
	    const override;
	unsigned long length(std::vector <unsigned long> const &lengths,
			     std::vector <double const *> const &values)
	    const override;
	bool checkParameterLength(std::vector<unsigned long> const &args)
	    const override;
	bool isDiscreteValued(std::vector<bool> const &mask) const override;
	bool checkParameterDiscrete(std::vector<bool> const &mask)
	    const override;
	bool checkParameterFixed(std::vector<bool> const &mask) const override;
	std::string deparse(std::vector<std::string> const &par) const override;
    };

    }
} /* namespace jags */

#endif /* FUNC_SEQ_H_ */
