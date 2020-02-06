//#ifndef _offdiag
//#define _offdiag
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double offdiag(mat A, int p, int q, int n)
{
	double max = 0.0;
	int i, j;
	for(int i = 0; i < n; ++i){
		for(int j = i+1; j < n; ++j){
			double aij = fabs(A(i,j));
			if ( aij > max)
			{
				max = aij; p = i; q = j;
			}
		}
	}
	return max;
}

//#endif
