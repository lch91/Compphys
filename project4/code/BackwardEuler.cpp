// Different modules needed to solve this problem
#include <iostream>
#include <fstream>
#include <armadillo>
#include "tridiag.h"

// Commands use to ease syntax
using namespace arma;
using namespace std;

// The function definition
void BackwardEuler(int n, int tsteps, double alpha, double delta_x){
	int i, t; // Iteration counter
	vec b(n), a(n), c(n), v(n), f(n), u(n); // vectors for storing variables
	for(i=1;i<n;i++){f(i)= i*delta_x-1;		// Initial values
		v(i)=i*delta_x-1;}
	v(n-1) = f(n-1) = v(0) = 0;		// Boundary values
	f(0) = 0; 
	// Setting up the tridiagonal matrix
	for(i=0; i < n ; i++){
		b(i) = 1 + 2*alpha;
		a(i) = -alpha;
		c(i) = -alpha;}
	// Solving the system
	for(t=1; t <= tsteps; t++){
		tridiag(a, b, c, f, v, n); // The tridiagonal solver from project 1
		v(0) = v(n-1) = 0;			// New boundary conditions
		for(i=0; i < n; i++){
			f(i) = v(i);		// New initial values
		}
	}
	for(i=0; i < n; i++){
		u(i) = v(i) + 1 - i*delta_x;}	// Finding u from v and u_s
	ofstream myfile;			// Writing everything to file
	myfile.open("BackwardEuler.txt");
	for (i=0; i < n; i++){myfile << u(i) << endl;}
	myfile.close();
}
