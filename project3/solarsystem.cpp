/*
**  FYS3150 - Project 5
**  ~~~~~~~~~~~~~~~~~~~~~~
**  Solar System Simulator
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include "constants.h"
#include "planet.h"

using namespace std;

int main() {

	int    i, j, k=0, p=0;
	int    iRunID=0, iMethod=0, iNextYr=0;
	double dTMax, dTStep, dTime=0, dTStepS, dOutput;
	double dDYr=cYr/86400.0;
	clock_t tStart, tFinish;
	tStart = clock();

	cout << endl;
	cout << "Input variables:" << endl;
	cout << "****************" << endl;
	cout << "T-Max (years): ";
	cin  >> dTMax;
	cout << "Time step (days): ";
	cin  >> dTStep;
	cout << "Output every (days): ";
	cin  >> dOutput;
	cout << "Run ID: ";
	cin  >> iRunID;
	cout << "Method (0=RK4, 1=EC): ";
	cin  >> iMethod;
	cout << endl;
	
	dTStep 	/= dDYr;
	dTStepS  = dTStep*cYr;
	
	cout << "Runtime:" << endl;
	cout << "********" << endl;
	cout << "Time step: " << dTStepS << " seconds" << endl;

	int iObjects=10;
	// Setting up the system
	// Data: http://nssdc.gsfc.nasa.gov/planetary/factsheet
	Planet **aSystem = new Planet*[iObjects];
	//                       Label     RunID   Aphelion    VMin      Aph Angle  Mass       Size
	aSystem[p] = new Planet("Sun",     iRunID, 0,          0,        0,         1.9891e30, 6.955e8);  p++;
	aSystem[p] = new Planet("Mercury", iRunID, 69.82e9,    38.86e3,  350,       3.3022e23, 2.4397e6); p++;
	aSystem[p] = new Planet("Venus",   iRunID, 108.94e9,   34.79e3,  45,        4.8685e24, 6.0518e6); p++;
	aSystem[p] = new Planet("Earth",   iRunID, 152.10e9,   29.29e3,  20,        5.9736e24, 6.3710e6); p++;
	//aSystem[p] = new Planet("Moon",    iRunID, 152.5055e9, 30.254e3, 0,         7.349e22,  1.7371e6); p++;
	aSystem[p] = new Planet("Mars",    iRunID, 249.23e9,   21.97e3,  250,       6.4185e23, 3.3895e6); p++;
	aSystem[p] = new Planet("Jupiter", iRunID, 816.62e9,   12.44e3,  285,       1.8986e27, 69.911e6); p++;
	aSystem[p] = new Planet("Saturn",  iRunID, 1514.50e9,  9.09e3,   0,         5.6846e26, 58.232e6); p++;
	aSystem[p] = new Planet("Uranus",  iRunID, 3003.62e9,  6.49e3,   75,        8.6810e25, 25.362e6); p++;
	aSystem[p] = new Planet("Neptune", iRunID, 4545.67e9,  5.37e3,   295,       1.0243e26, 24.622e6); p++;
	aSystem[p] = new Planet("Pluto",   iRunID, 7375.93e9,  3.71e3,   295,       1.305e22,  1.195e6);  p++;

	aSystem[0]->InitSystem(aSystem, iObjects, 0);
	for(i=0; i<iObjects; i++) {
		aSystem[i]->Update(aSystem, i, iObjects);
		aSystem[i]->Output();
	}
	
	if(iMethod==0) {

		double *aGamma  = new double[iObjects];
		double *aXPos   = new double[iObjects];
		double *aYPos   = new double[iObjects];
		double *aVX     = new double[iObjects*4];
		double *aVY     = new double[iObjects*4];
		double *aAX     = new double[iObjects*4];
		double *aAY     = new double[iObjects*4];
		double dStep;

		cout << "Time: 0 years";
		while(dTime < dTMax) {
			dTime += dTStep;
			// Save initial data
			for(i=0; i<iObjects; i++) {
				aSystem[i]->Time = dTime;
			  aGamma[i] = 1.0;
				if(i>0) aGamma[i] = aSystem[i]->Gamma(aSystem[0]);
				aXPos[i] = aSystem[i]->XPos;
				aYPos[i] = aSystem[i]->YPos;
				aVX[i*4] = aSystem[i]->VX;
				aVY[i*4] = aSystem[i]->VY;
				aAX[i*4] = aSystem[i]->FX/aSystem[i]->Mass;
				aAY[i*4] = aSystem[i]->FY/aSystem[i]->Mass;
			}
			// Runge-Kutta Step 1-3
	 		for(j=0; j<3; j++) {
				for(i=0; i<iObjects; i++) {
		 			if(j<2) {dStep = aGamma[i]*dTStepS/2.0;} else {dStep = aGamma[i]*dTStepS;};
					aVX[i*4+j+1] = aVX[i*4] + aAX[i*4+j]*dStep;
					aVY[i*4+j+1] = aVY[i*4] + aAY[i*4+j]*dStep;
					aSystem[i]->XPos = aXPos[i] + aVX[i*4+j]*dStep;
					aSystem[i]->YPos = aYPos[i] + aVY[i*4+j]*dStep;
				}
				for(i=0; i<iObjects; i++) {
					aSystem[i]->Update(aSystem, i, iObjects);
					aAX[i*4+j+1] = aSystem[i]->FX/aSystem[i]->Mass;
					aAY[i*4+j+1] = aSystem[i]->FY/aSystem[i]->Mass;
				}
			}
			// Runge-Kutta Step 4
			for(i=0; i<iObjects; i++) {
				aSystem[i]->VX   = aVX[i*4] + aGamma[i]*dTStepS*(aAX[i*4] + 2.0*aAX[i*4+1] + 2.0*aAX[i*4+2] + aAX[i*4+3])/6.0;
				aSystem[i]->VY   = aVY[i*4] + aGamma[i]*dTStepS*(aAY[i*4] + 2.0*aAY[i*4+1] + 2.0*aAY[i*4+2] + aAY[i*4+3])/6.0;
				aSystem[i]->XPos = aXPos[i] + aGamma[i]*dTStepS*(aVX[i*4] + 2.0*aVX[i*4+1] + 2.0*aVX[i*4+2] + aVX[i*4+3])/6.0;
				aSystem[i]->YPos = aYPos[i] + aGamma[i]*dTStepS*(aVY[i*4] + 2.0*aVY[i*4+1] + 2.0*aVY[i*4+2] + aVY[i*4+3])/6.0;
			}
			// Updating system
	 		aSystem[0]->Correct(aSystem, iObjects, 0);
			for(i=0; i<iObjects; i++) {
				aSystem[i]->Update(aSystem, i, iObjects);
				if(k%(int(dOutput/(dTStep*dDYr)))==0) aSystem[i]->Output();
			}
			if(dTime > iNextYr) {
				cout << "\rTime: " << iNextYr << " years";
				fflush(stdout);
				iNextYr++;
			}
			k++;
		}
		cout << endl << endl;

	} else {

		double **aTemp;
		double dGamma;

		aTemp = new double*[iObjects];
		for(i=0; i<iObjects; i++) {
			aTemp[i] = new double[4];
		}

		cout << "Time: 0 years";
		while(dTime < dTMax) {
			dTime += dTStep;
			// Euler-Cromer
			for(i=0; i<iObjects; i++) {
				aSystem[i]->Time = dTime;

			  dGamma = 1;
				if(i>0) dGamma = aSystem[i]->Gamma(aSystem[0]);

				aTemp[i][0] = aSystem[i]->VX + aSystem[i]->FX*dGamma*dTStepS/aSystem[i]->Mass;
				aTemp[i][1] = aSystem[i]->VY + aSystem[i]->FY*dGamma*dTStepS/aSystem[i]->Mass;
				aTemp[i][2] = aSystem[i]->XPos + aTemp[i][0]*dGamma*dTStepS;
				aTemp[i][3] = aSystem[i]->YPos + aTemp[i][1]*dGamma*dTStepS;
			}
			// Updating object's position and velocity
			for(i=0; i<iObjects; i++) {
				aSystem[i]->VX   = aTemp[i][0];
				aSystem[i]->VY   = aTemp[i][1];
				aSystem[i]->XPos = aTemp[i][2];
				aSystem[i]->YPos = aTemp[i][3];
			}
			// Updating system
			for(i=0; i<iObjects; i++) {
				aSystem[i]->Update(aSystem, i, iObjects);
				if(k%(int(dOutput/(dTStep*dDYr)))==0) aSystem[i]->Output();
			}
			if(dTime > iNextYr) {
				cout << "\rTime: " << iNextYr << " years";
				fflush(stdout);
				iNextYr++;
			}
			k++;
		}
		cout << endl << endl;

	}

	cout << endl;
	cout << "Solar System Summary:" << endl;
	cout << "*********************" << endl;
	cout << "    Object:    Aphelion      Perihelion            VMin             VMax     " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	for(i=0; i<iObjects; i++) {
		aSystem[i]->Summary();
	}
	cout << endl;
	
	tFinish = clock();
	cout << "Computation time: " << double(tFinish-tStart)/CLOCKS_PER_SEC << " seconds" << endl << endl;
	
  return 0;
}
