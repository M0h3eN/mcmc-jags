#ifndef NA_INF_H_
#define NA_INF_H_

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * A quiet NaN used to indicate missing data. Note that this value
     * is merely a place holder for missing values. Unlike the R
     * language, there is no expectation that functions acting on
     * missing values will propagate missing (NA) values.
     *
     * Since JAGS_NA is not a number, a test for numeric equality will
     * always return false. Use jags_isna to test whether a value is
     * JAGS_NA.
     */
     extern const double JAGS_NA;
    /**
     * A quiet NaN distinct from JAGS_NA.
     */
     extern const double JAGS_NAN;
    /**
     * Positive infinity.
     */
     extern const double JAGS_POSINF;
    /**
     * Negative infinity.
     */
    extern const double JAGS_NEGINF;

    /**
     * Returns 1 if the argument is identical to JAGS_NA and 0 otherwise
     */
    int jags_isna(double);

#ifdef __cplusplus
}
#endif

#endif
