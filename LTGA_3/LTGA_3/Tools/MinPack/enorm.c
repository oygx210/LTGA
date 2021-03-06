#include "cminpack.h"
#include <math.h>
#include "cminpackP.h"

/*
  About the values for rdwarf and rgiant.

  The original values, both in signe-precision FORTRAN source code and in double-precision code were:
#define rdwarf 3.834e-20
#define rgiant 1.304e19
  See for example:
    http://www.netlib.org/slatec/src/denorm.f
    http://www.netlib.org/slatec/src/enorm.f
  However, rdwarf is smaller than sqrt(FLT_MIN) = 1.0842021724855044e-19, so that rdwarf**2 will
  underflow. This contradicts the constraints expressed in the comments below.

  We changed these constants to be sqrt(dpmpar(2))*0.9 and sqrt(dpmpar(3))*0.9, as proposed by the
  implementation found in MPFIT http://cow.physics.wisc.edu/~craigm/idl/fitting.html
*/

#define double_dwarf (1.4916681462400413e-154*0.9)
#define double_giant (1.3407807929942596e+154*0.9)
#define float_dwarf (1.0842021724855044e-19f*0.9f)
#define float_giant (1.8446743523953730e+19f*0.9f)
#define half_dwarf (2.4414062505039999e-4f*0.9f)
#define half_giant (255.93749236874225497222f*0.9f)

#define dwarf(type) _dwarf(type)
#define _dwarf(type) type ## _dwarf
#define giant(type) _giant(type)
#define _giant(type) type ## _giant

#define rdwarf dwarf(double)
#define rgiant giant(double)


double enorm(int n, const double *x)
{
#ifdef USE_CBLAS
    return cblas_dnrm2(n, x, 1);
#else /* !USE_CBLAS */
    /* System generated locals */
    double ret_val, d1;

    /* Local variables */
    int i;
    double s1, s2, s3, xabs, x1max, x3max, agiant, floatn;

/*     ********** */

/*     function enorm */

/*     given an n-vector x, this function calculates the */
/*     euclidean norm of x. */

/*     the euclidean norm is computed by accumulating the sum of */
/*     squares in three different sums. the sums of squares for the */
/*     small and large components are scaled so that no overflows */
/*     occur. non-destructive underflows are permitted. underflows */
/*     and overflows do not occur in the computation of the unscaled */
/*     sum of squares for the intermediate components. */
/*     the definitions of small, intermediate and large components */
/*     depend on two constants, rdwarf and rgiant. the main */
/*     restrictions on these constants are that rdwarf**2 not */
/*     underflow and rgiant**2 not overflow. the constants */
/*     given here are suitable for every known computer. */

/*     the function statement is */

/*       double precision function enorm(n,x) */

/*     where */

/*       n is a positive integer input variable. */

/*       x is an input array of length n. */

/*     subprograms called */

/*       fortran-supplied ... dabs,dsqrt */

/*     argonne national laboratory. minpack project. march 1980. */
/*     burton s. garbow, kenneth e. hillstrom, jorge j. more */

/*     ********** */

    s1 = 0.;
    s2 = 0.;
    s3 = 0.;
    x1max = 0.;
    x3max = 0.;
    floatn = (double) (n);
    agiant = rgiant / floatn;
    for (i = 0; i < n; ++i) {
	xabs = fabs(x[i]);
	if (xabs <= rdwarf || xabs >= agiant) {
            if (xabs > rdwarf) {

/*              sum for large components. */

                if (xabs > x1max) {
                    /* Computing 2nd power */
                    d1 = x1max / xabs;
                    s1 = 1. + s1 * (d1 * d1);
                    x1max = xabs;
                } else {
                    /* Computing 2nd power */
                    d1 = xabs / x1max;
                    s1 += d1 * d1;
                }
            } else {

/*              sum for small components. */

                if (xabs > x3max) {
                    /* Computing 2nd power */
                    d1 = x3max / xabs;
                    s3 = 1. + s3 * (d1 * d1);
                    x3max = xabs;
                } else {
                    if (xabs != 0.) {
                        /* Computing 2nd power */
                        d1 = xabs / x3max;
                        s3 += d1 * d1;
                    }
                }
            }
	} else {

/*           sum for intermediate components. */

            /* Computing 2nd power */
            s2 += xabs * xabs;
        }
    }

/*     calculation of norm. */

    if (s1 != 0.) {
        ret_val = x1max * sqrt(s1 + (s2 / x1max) / x1max);
    } else {
        if (s2 != 0.) {
            if (s2 >= x3max) {
                ret_val = sqrt(s2 * (1. + (x3max / s2) * (x3max * s3)));
            } else {
                ret_val = sqrt(x3max * ((s2 / x3max) + (x3max * s3)));
            }
        } else {
            ret_val = x3max * sqrt(s3);
        }
    }
    return ret_val;

/*     last card of function enorm. */
#endif /* !USE_CBLAS */
} /* enorm_ */

