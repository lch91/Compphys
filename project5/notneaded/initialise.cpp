#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib.h"
#include "header.h"

using namespace std;

void initialise(int& max_trials, int& number_walks, double& move_probability){
	cout << "Number of Monte Carlo trials =";
	cin >> max_trials;
	cout << "Number of attempted walks=";
	cin >> number_walks;
	cout << "Move Probability=";
	cin >> move_probability;}
