#include <iostream>
#include <armadillo>
#include "offdiag.hpp"
#include "Jacobi_rotate.hpp"

using namespace std;
using namespace arma;

main(){
	int n = 100;
	mat A(n,n);
	double h = 5.0/(n+1);
	mat R = eye<mat>(n,n);
	int i;
	int j;
	double omega = 5.0;
	vec rho(n);
for(i=0; i < n; i++){
	rho(i) = (i+1)*h;
	for(j=0; j < n; j++){
	if(j == i-1){
	A(i,j) = -1./pow(h,2);}
	else if(j == i+1 and j < n){
	A(i,j) = -1./pow(h,2);}
	else if(j == i){
	A(i,j) = 2./pow(h,2) + pow(omega,2)*pow(rho(i),2) + 1./rho(i);}
	}
	}	
	double maxnondiag = 1.0; //The largest element in out matrix that is not on the diagonal
	int maxiter = n*n*n;	// maximum number of iterations
	double tolerance = 1.0E-10;	// Largest nondiagonal element after one rotation
	int iterations = 0;

	while(maxnondiag > tolerance && iterations <= maxiter) // A loop until we have what we want
	{
		int p, q;
		maxnondiag = offdiag(A, &p, &q, n);	// Finding the largest nondiagional element
		jacobi_rotate(A, R, p, q, n);		// The rotation
		iterations ++;
	}
	
double min = 100;
for(i=0; i<n; i++){
	for(j=0; j<n; j++){
		if(A(i,j) < min && i==j){
			min = A(i,j);}}}
cout << min << endl;
}		
