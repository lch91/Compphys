#include <fstream>
#include "CPhys.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace CPhys;

int main(int argc, const char *argv[])
{	
	int walkers = 10000;
	double prob=0.25, time=5.0, dt=0.001, start=0, end=1;
	Walker walker = MonteCarlo::getWalker(walkers, prob, time, dt, start, end);
	walker.useGauss(false); // Works only with start1d()
	walker.start2D();
	walker.output();
}

