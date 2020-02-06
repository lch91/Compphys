#include <iostream>
#include <armadillo>
#include "offdiag.hpp"
#include "Jacobi_rotate.hpp"

using namespace std;
using namespace arma;

main(){
	int n = 200;
	mat A(n,n);
	double h = 4.4/(n+1);
	mat R = eye<mat>(n,n);
	int i;
	int j;
	vec rho(n);
	for(i=0; i < n; i++){
		rho(i) = (i+1)*h;
		for(j=0; j < n; j++){
			if(j == i-1){
				A(i,j) = -1./pow(h,2);}
			else if(j == i+1 and j < n){
				A(i,j) = -1./pow(h,2);}
			else if(j == i){
				A(i,j) = 2./pow(h,2) + pow(rho(i),2);}
			}
		}
		
double maxnondiag = 1.0;
int maxiter = n*n*n;
double tolerance = 1.0E-10;
int iterations = 0;

while(maxnondiag > tolerance && iterations <= maxiter)
{
	int p, q;
	maxnondiag = offdiag(A, &p, &q, n);
	jacobi_rotate(A, R, p, q, n);
	iterations ++;
}
cout << iterations << endl;
int max = 15;
	for(i=0; i<n; i++){
		if(A(i + i*n) < max){
			cout << A(i + i*n) << endl;}}
}		
