#include <iostream>	//including modules I might need
#include <cmath>
#include <fstream>

using namespace std;	// preventing me from writing std:: all the time

int main(){
	// Declaring all numbers and variables
	int n;
	int i;
	double h;
	n = 100;
	double b[n];
	double a[n];
	double c[n];
	double v[n];
	double f[n];
	double x[n];
	double u[n];
	//double eps[n];
	double btemp;
	double temp[n];
	double y;
	double z;
	
	for(i=0; i < n ; i++){
		// The different diagonals in the matrix
		b[i] = 2.0; 
		a[i] = -1.0;
		c[i] = -1.0;
	}

	h = 1./(n+1);		// The step-length
	btemp = b[0];		// The temporary b's in the solver
		// The initial values
	x[0] = 0*h;
	f[0] = pow(h, 2.0)*100*exp(-10*x[0]);	
	v[0] = f[0]/btemp;	

	for(i=1; i < n; i++){
		x[i] = i*h;	// Different points where we calculate the derivatives
		f[i] = pow(h,2.0)*100*exp(-10*x[i]);	// The function we consider	
		temp[i] = c[i-1]/btemp;			// The forward substitution
		btemp = b[i] -a[i]*temp[i];		// 
		v[i] = (f[i] - a[i]*v[i-1])/btemp;	// The numerical solution
		u[i] = 1-(1-exp(-10))*x[i]-exp(-10*x[i]);	// The exact solution
		//eps[i] = log10(abs((v[i]-u[i])/u[i]));// The relative error
	}
	for(i=n-1; i>=0 ; i--){
		v[i] -= temp[i+1]*v[i+1];	// The backward substitution
	}
	/*ofstream myfile;	// Writing the results to file 
	myfile.open ("project.txt", ios::out | ios::app);
	y = 0;
	for(i=0; i<n; i++){
		// The largest relative error value
		z = abs(eps[i]);
		if (z > y){
			y = z;
		}
		//cout << v[i] << endl;
		//myfile << v[i] << endl;
	}
	myfile << y << endl;
	myfile.close(); */
}

/* n = 10: 0.015 for project1, 0.018 for LUdecomp
   n = 100: 0.013 for project1, 0.019 for LUdecomp
   n = 1000: 0.014 for project1, 0.365 for LUdecomp
   n = 10000: 0.215s for project1, 4min30.182s for LUdecomp
   n = 100000: 0.254s for project1, fancy segmentation fault
*/
