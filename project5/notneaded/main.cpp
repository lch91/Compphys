#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib.h"
#include "header.h"

using namespace std;

main(){
	int max_trials, number_walks;
	double move_probability;
	initialise(max_trials, number_walks, move_probability);
	double *walk_cumulative = new double[number_walks+1];
	double *walk2_cumulative = new double[number_walks+1];
	double *probability = new double [2*(number_walks+1)];
	double timestep = 0.005;
	for(int walks = 1; walks <= number_walks; walks++){
		walk_cumulative[walks] = walk2_cumulative[walks] = 0;}
	for(int walks = 0; walks <= 2*number_walks; walks++){
		probability[walks] = 1;}
	mc_sampling(max_trials, number_walks, move_probability, walk_cumulative, walk2_cumulative, probability, timestep);
	output(max_trials, number_walks, walk_cumulative, walk2_cumulative, probability, timestep);
	delete[] walk_cumulative;
	delete[] walk2_cumulative;
	delete[] probability;
	}
	
