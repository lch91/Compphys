#ifndef _offidag
#define _offdiag
#include <armadillo>

using namespace std;
using namespace arma;

	double offdiag(double **A, int p, int q, int n);
	{
		double max;
		int i; int j;
		for (int i = 0; i < n; ++i)
		{
			for ( int j = i+1; j < n; ++j)
			{
				double aij = fabs(A[i][j]);
				if ( aij > max)
				{
					max = aij; p = i; q = j;
				}
			}
		}
		return max;
	}

#endif
