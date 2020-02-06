#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"

using namespace std;

void output(int max_trials, int number_walks, double *walk_cumulative, double *walk2_cumulative, double *probability, double timestep){
	ofstream ofile("diffusion.dat");
	ofstream probfile("probdiff.dat");
	for(int i = 1; i <= number_walks; i++){
	double xaverage  = walk_cumulative[i]/((double) max_trials);
	double x2average = walk2_cumulative[i]/((double) max_trials);
	double variance = x2average - xaverage*xaverage;
	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setw(6) << i;
	ofile << setw(15) << setprecision(8) << xaverage;
	ofile << setw(15) << setprecision(8) << variance << endl;}
	ofile.close();
	
	double norm = 0.;
	for(int i = -number_walks; i <= number_walks; i++){
		norm += (double) probability[i+number_walks];}
		
	for(int i = 0; i <= number_walks; i++){
		double histogram = probability[i+number_walks]/norm;
		probfile << setiosflags(ios::showpoint | ios::uppercase);
		probfile << setw(6) << i;
		probfile << setw(15) << setprecision(8) << histogram << endl;;}
		
	probfile.close();
	
	}
	
