#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

main(){
	int i;
	int j;
	int k;
	int n = 1000;
	mat A = zeros<mat>(n,n);
	mat B = randu<mat>(n,n);
	mat C = randu<mat>(n,n);
	for(j=0; j<n; j++){
		for(i=0; i<n; i++){
			for(k=0; k<n; k++){
				A(i,j) += B(i,k)*C(k,j);
				}
			}
		}
	//cout << A << endl;
	}
