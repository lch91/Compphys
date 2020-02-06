#ifndef mc_sampling_h
#define mc_sampling_h

void initialise(int& max_trials, int& number_walks, double& move_probability);
void output(int max_trials, int number_walks, double *walk_cumulative, double *walk2_cumulative, double *probability, double timestep);
void mc_sampling(int max_trials, int number_walks, double move_probability, double *walk_cumulative, double *walk2_cumulative, double *probability, double timestep);

#endif
