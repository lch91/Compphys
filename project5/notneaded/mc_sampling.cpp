#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib.h"
#include "header.h"
using namespace std;
double gaussian_deviate(long *);

void mc_sampling(int max_trials, int number_walks, double move_probability, double *walk_cumulative, double *walk2_cumulative, double *probability, double timestep){
	long idum;
	idum=-1;
	//double l = sqrt(2*timestep);
arne:	for(int trial=1; trial <= max_trials; trial++){
		int position = 0;
		//double k = gaussian_deviate(&idum);
		for(int walks = 1; walks <= number_walks; walks++){
			if(ran0(&idum) <= move_probability){
				position += -1;}
			else{
				position -= 1;}
			if(position < 0) goto arne;
			
			walk_cumulative[walks] += position;//*l*k;
			walk2_cumulative[walks] += position*position;//*l*k*l*k;
			probability[position+number_walks] += 1;
			}
		}
	}
				
