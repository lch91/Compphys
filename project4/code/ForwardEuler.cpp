// Importing important modules
#include <iostream>
#include <fstream>
#include <armadillo>

// Making the code easier to write
using namespace std;
using namespace arma;

// Defining the function
void ForwardEuler(int n, int tsteps, double alpha, double delta_x){
	int i, t;	// Iteration integers
	vec v(n), vnew(n), u(n); // Arrays for storing values
	// Boundary conditions
	v(0) = 0;
	vnew(0) = vnew(n-1) = v(n-1) = 0;
	// Initial conditions
	for(i=0;i<n;i++){v(i)= i*delta_x-1;
		vnew(i)=0;}
	for(t=1; t <= tsteps; t++){ // Time loop
	for(i = 1; i < n-1; i++){	// Space loop
		vnew(i+1) = alpha*v(i-1)+(1-2*alpha)*v(i)+alpha*v(i+1);	// The forward Euler method
		}
	for(i = 1; i < n-2; i++){v(i) = vnew(i+1);}	// New initial conditions
		}
	for(i=0; i < n; i++){
		u(i) = vnew(i) + 1 - i*delta_x;}	// The real solution
		// Writing u to file
	ofstream myfile;
	myfile.open("ForwardEuler.txt");
	for (i=0; i<n; i++){myfile << u(i) << endl;}
	myfile.close();
}
