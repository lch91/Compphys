#include <iostream>	// Including modules
#include <armadillo>

using namespace std;
using namespace arma;

int main(){
	// Defining the variables
	int n;
	int i;
	int j;
	n = 100;	// The dimension of the matrices/vectors
	vec x(n);
	double h = 1./(n+1);	// The step length
	mat A = 2*eye<mat>(n,n);	// The matrix we use
	for(i=0; i < n;i++){x[i] = i*h;}	// Filling the x vector
	for(i=0; i < n; i++){		// Filling the matrix
		for(j=0; j < n; j++){
			if(j == i-1){
				A(i,j) = -1;}
			else if(j == i+1){
				A(i,j) = -1;}
			}
		}

	mat L, U;	// Initilazing the matrices we use to solve the problem
	lu(L, U, A);	// The LU-decomposition
	//mat B = L*U;	// Checking if it worked
	vec b(n);	// The vector with the function 
	for(i=0; i < n ;i++){b(i) = pow(h, 2)*100*exp(-10*x(i));}

	vec y = solve(L, b);	// The solution for 
	vec X = solve(U, y);	// the LU-decomposition

	//cout << X << endl;
	
}
