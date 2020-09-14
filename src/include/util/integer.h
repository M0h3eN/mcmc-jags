#ifndef UTIL_INTEGER_H_
#define UTIL_INTEGER_H_

namespace jags {

    /**
     * Integers from 1 to JAGS_BIGINT can be represented exactly in
     * a double precision float.
     */
    extern const unsigned long JAGS_BIGINT;
    
    /**
     * Checks whether the given double is within a small numerical
     * tolerance of an exact integer.
     */
    bool checkInteger(double);
    /**
     * Rounds the given value to the nearest integer and returns an
     * int. Values outside the range INT_MIN to INT_MAX are truncated
     * to INT_MIN (if lower) or INT_MAX (if higher).
     */
    int asInteger(double);
    /**
     * Rounds the nearest integer and returns an unsigned long. Values
     * outside the range 0 to JAGS_BIGINT are truncated to 0 (if
     * lower) or JAGS_BIGINT (if higher).
     */
    unsigned long asULong(double);

} /* namespace jags */

#endif /* UTIL_INTEGER_H_ */
