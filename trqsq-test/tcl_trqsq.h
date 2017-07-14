#include <cstring>

namespace trqsq
{
    inline double* vzero(double *a, int n1)
    {
	//to be documented
	if (n1 <= 0) return 0;
	return (double *)memset(a,0,n1*sizeof(double));
    };


    ////////////////////////////////////////////////////////////////////////////////
    /// trqsq.F -- translated by f2c (version 19970219).
    ///
    /// CERN PROGLIB# F112    TRQSQ           .VERSION KERNFOR  4.15  861204
    /// ORIG. 18/12/74 WH
    ///
    /// See original documentation of CERNLIB package
    /// [F112](https://cern-tex.web.cern.ch/cern-tex/shortwrupsdir/f112/top.html)

    double *tcl_trqsq(const double *q, const double *s, double *r__, int m)
    {
	int indq, inds, imax, i__, j, k, l;
	int iq, ir, is, iqq;
	double sum;

	/* Parameter adjustments */
	--r__;    --s;    --q;

	/* Function Body */
	imax = (m * m + m) / 2;
	vzero(&r__[1], imax);
	inds = 0;
	i__ = 0;

	do {
	    inds += i__;
	    ir = 0;
	    indq = 0;
	    j = 0;

	    do {
		indq += j;
		is = inds;
		iq = indq;
		sum = 0.;
		k = 0;

		do {
		    if (k > i__)  is += k;
		    else          ++is;

		    if (k > j)    iq += k;
		    else        ++iq;

		    sum += s[is] * q[iq];
		    ++k;
		} while (k < m);
		iqq = inds;
		l = 0;

		do {
		    ++ir;
		    if (l > i__)  iqq += l;
		    else          ++iqq;
		    r__[ir] += q[iqq] * sum;
		    ++l;
		} while (l <= j);
		++j;
	    } while (j < m);
	    ++i__;
	} while (i__ < m);

	return 0;
    } /* trqsq_ */

    static const int idx66[6][6] =
    {{ 0, 1, 3, 6,10,15},
	{ 1, 2, 4, 7,11,16},
	{ 3, 4, 5, 8,12,17},
	{ 6, 7, 8, 9,13,18},
	{10,11,12,13,14,19},
	{15,16,17,18,19,20}};
}
