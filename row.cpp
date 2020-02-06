#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

main(){
	int i;
	int j;
	int k;
	int n = 100;
	mat A = zeros<mat>(n,n);
	mat B = randu<mat>(n,n);
	mat C = randu<mat>(n,n);
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				A(i,j) += B(i,k)*C(k,j);
				}
			}
		}
	}
/*	
n = 10: row = 0.002, column = 0.002
n = 100: row = 0.027, column = 0.029
n = 1000: row = 27.467, column = 30.902
n = 10000: Dette vil ta mangfoldige timer
*/
