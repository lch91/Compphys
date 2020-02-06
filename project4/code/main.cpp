// Important modules and the different numerical methods. 
#include <iostream>
#include <armadillo>
#include "CrankNico.h"
#include "BackwardEuler.h"
#include "ForwardEuler.h"

// Making the code easier to rerad and write
using namespace std;
using namespace arma;
// Declaring the function
main(){
	int n = 100, tsteps = 100;//5*n*n; // The number of steps we take in space and time
	double delta_x = 1./n;		// Step length in x-direction
	double delta_t = 1./(5*n*n);	// Time step length
	double alpha = delta_t/pow(delta_x,2);	// Combined step length and time step length
	// Calling the different functions
	ForwardEuler(n, tsteps, alpha, delta_x);
	BackwardEuler(n, tsteps, alpha, delta_x);
	CrankNico(n, tsteps, alpha, delta_x);
}
	
