/*  This program implements a simple random walk in one dimension with boundary conditions
    equal 1 at x =0 and 0 at x = 1. The random walk is performed using the uniform distribution
    It solves exercise a 
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "lib.h"
using namespace  std;
// output file as global variable
ofstream ofile;  
// prints to screen the results of the calculations  
void  output(int, double, double *, double *);

// Begin of main program   

//int main()
int main(int argc, char* argv[])
{
  char *outfilename;
  // Read in output file, abort if there are too few command-line arguments
  if( argc <= 1 ){
    cout << "Bad Usage: " << argv[0] << 
      " Read also output file on same line, finaltime, number of cycles and walkers" << endl;
    exit(1);
  }
  else{
    outfilename=argv[1];
  }
  ofile.open(outfilename); 

  // Declarations
  long idum = -1;
  const double dt = 0.0001;
  const double l = sqrt(2.0*dt);
  const double FinalTime = atof(argv[2]);
  const double ntimesteps  = FinalTime/dt;
  int MC_cycles, N_walkers;
  int NumberBins = 1000;//(int) 1.0/l +1;
  double Delta_x = 1./((double) NumberBins);
  vector<double> position;
  MC_cycles =  atoi(argv[3]);
  N_walkers = atoi(argv[4]);

  // histograms to hold the solution
  double *hist = new double[NumberBins];
  double *histsquared = new double[NumberBins];
  double *histtemp = new double[NumberBins];
  double *stddev = new double[NumberBins];   
  // initialize arrays
  for (int bin =0; bin < NumberBins; bin++){
    hist[bin] = histsquared[bin] = histtemp[bin] = stddev[bin] = 0;
  }
  // Outer loop over Monte Carlo cycles
  for (int cycle =0; cycle < MC_cycles; cycle++){
    // In the beginning of every cycle, reset to initial population
    position.resize(N_walkers);
    // initialize walker array
    for (int walker =0; walker < N_walkers; walker++) position[walker] = 0.0; 
    // loop over time
    for (int step = 0; step < ntimesteps; step++){
      double prev; 
      int addwalkers = 0;
      // Loop over walkers, they will eventually produce the final histogram
      for (int walker = 0; walker < position.size(); walker++){
	prev = position[walker];  // previous walker position
	// suggest a move for the actual walker, exercise a.
	if (ran2(&idum) > 0.5){
	  position[walker] += 1;
	}
	else { 
	  position[walker] -= 1;
	}
	// implement boundary conditions
	if (position[walker] < Delta_x && prev >= Delta_x ||  position[walker] >=1){
	  position.erase(position.begin()+walker);
	  walker--;
	  continue;
	}
	if (position[walker] >= Delta_x && prev < Delta_x)
	    addwalkers++;  // move away from x=0 to x>0
	  
	    if (position[walker] < 0) 
	      position[walker] = 0; //  moves into wall at x < 0
	  
	    } // end loop over walkers
	// add 1 walker at x=0 for every walker that moved away from zero
	for (int i = 0; i < addwalkers; i++) position.push_back(0.0); 
      } //end time loop

      // set up temporary histogram
      for (int walker = 0; walker < position.size(); walker++)
	histtemp[(int) floor(position[walker]/Delta_x)]++;
    
      for (int bin =0; bin < NumberBins; bin++) { 
	hist[bin] += histtemp[bin];
	histsquared[bin] += histtemp[bin]*histtemp[bin];
	histtemp[bin] = 0;
      }
    } // end loop over Monte Carlo cycles
    // Normalize with number of Monte Carlo cycles
    double NormFactor = 1.0/(MC_cycles);
    for (int bin =0; bin < NumberBins; bin++) { 
      hist[bin] *=   NormFactor;
      histsquared[bin] *= NormFactor;
      stddev[bin] = sqrt(histsquared[bin]-hist[bin]*hist[bin]);
      stddev[bin] *= 1.0/sqrt((double) MC_cycles);
    }
    //  Call output file
    output(NumberBins, Delta_x, hist, stddev);
    ofile.close();  // close output file
    delete [] hist; delete [] histsquared; delete [] histtemp; delete [] stddev;
    return 0;
  }

  // Funtion that prints the histogram and the standard deviation

  void output(int NumberBins, double Delta_x, double *hist, double *std)
  {
    int i;
    double x =0.0;
    for( i=0; i < NumberBins; i++){
      ofile << setiosflags(ios::showpoint | ios::uppercase);
      ofile << setw(15) << setprecision(8) << x;
      ofile << setw(15) << setprecision(8) << hist[i];
      ofile << setw(15) << setprecision(8) << std[i] << endl;
      x += Delta_x;
    }
  }  // end of function output         
