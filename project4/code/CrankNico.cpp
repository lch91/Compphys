// Modules needed for this problem
#include <iostream>
#include <fstream>
#include <armadillo>
#include "tridiag.h"

// Making the syntax easier
using namespace std;
using namespace arma;

// Defining the function
void CrankNico(int n, int tsteps, double alpha, double delta_x){
	int i, t;		// Iteration counters
	vec a(n), b(n), c(n), r(n), v(n), u(n);		// Arrays for storing variables
	for(i=0; i < n; i++){		// Setting up the matrix
		a(i) = c(i) = - alpha;	
		b(i) = 2 + 2*alpha;}
	//Boundary conditions
	r(0) = 0;
	v(0) = v(n-1) = r(n-1) = 0;
	// Initial conditions
	for(i=1;i<n-1;i++){
		r(i) = i*delta_x - 1;
		v(i) = i*delta_x - 1;}
	// Solving the equations
	for(t = 1; t <= tsteps; t++){	// In time
		for(i = 1; i < n-1; i++){	// and space
			r(i) = alpha*v(i-1)+(2-2*alpha)*v(i)+alpha*v(i+1);} // Right hand side of the equation
		r(0) = 0;	// Boundary values
		r(n-1) = 0;
	
	tridiag(a, b, c, r, v, n); // The tridiagonal solver
	// New boundary conditions
	v(0) = 0;
	v(n-1) = 0;
	}
	for(i=0; i < n; i++){
		u(i) = v(i) + 1 - i*delta_x;}		// The actual solution
		// Writing the solution to file
	ofstream myfile;
	myfile.open("CrankNico.txt");
	for (i=0; i<n; i++){myfile << u(i) << endl;}
	myfile.close();
}
