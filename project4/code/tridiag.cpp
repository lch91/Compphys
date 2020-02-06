// Modules needed
#include <iostream>
#include <armadillo>

// Shorten syntax
using namespace std;
using namespace arma;

// The function
void tridiag(vec a, vec b, vec c, vec f, vec &v, int n){
	int i; // Iteration counter
	double btemp;	// Temporary diagonal
	vec temp(n);	// Temporary answer
	btemp = b(0);	// Initial b
	v(0) = f(0)/btemp;	// Initial value
	
	// Decomposition and forward substitution
	for(i=1; i < n; i++){
		temp(i) = c(i-1)/btemp;
		btemp = b(i) - a(i)*temp(i);
		v(i) = (f(i) - a(i)*v(i-1))/btemp;
	}
	for(i=n-2; i>=0 ; i--){
		v(i) -= temp(i+1)*v(i+1); //Backward substitution
	}
	return;
}
