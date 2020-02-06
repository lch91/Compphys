#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include "constants.h"
#include "planet.h"

using namespace std;

int main() {

	int    i, j, k=0;
	int    iRunID=0, iMethod=0, iNextYr=0, iSet=0, iObjects=0;
	double dTMax, dTStep, dTime=0, dTStepS, dOutput;
	double dDYr=cYr/86400.0;
	double dTemp=1.0;
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
	cout << "Choose system:" << endl;
	cout << " 0: Sun/Earth" << endl;
	cout << " 1: Sun/Earth/Moon" << endl;
	cout << " 2: All planets" << endl;
	cout << " 3: Sun/Earth/Mars/Jupiter With Inc. Jupiter mass" << endl;
	cout << " 4: Sun/Earth with inc. Earth VMin" << endl;
	cout << " 5: All planets + Rocket" << endl;
	cout << " 6: All planets With Inc. Jupiter mass" << endl;
	cout << "Select: ";
	cin  >> iSet;
	cout << endl;
	
	dTStep 	/= dDYr;
	dTStepS  = dTStep*cYr;
	
	cout << "Runtime:" << endl;
	cout << "********" << endl;
	cout << "Time step: " << dTStepS << " seconds" << endl;

	// Setting up the system
	// Data: http://nssdc.gsfc.nasa.gov/planetary/factsheet
	//                             Label     RunID   Aphelion    VMin      Aph Angle  Mass       Size
	Planet *oSun     = new Planet("Sun",     iRunID, 0,          0,        0,         1.9891e30, 6.955e8);
	Planet *oMercury = new Planet("Mercury", iRunID, 69.82e9,    38.86e3,  350,       3.3022e23, 2.4397e6);
	Planet *oVenus   = new Planet("Venus",   iRunID, 108.94e9,   34.79e3,  45,        4.8685e24, 6.0518e6);
	Planet *oEarth   = new Planet("Earth",   iRunID, 152.10e9,   29.29e3,  20,        5.9736e24, 6.3710e6);
	Planet *oMoon    = new Planet("Moon",    iRunID, 152.5055e9, 30.254e3, 20,        7.349e22,  1.7371e6);
	Planet *oMars    = new Planet("Mars",    iRunID, 249.23e9,   21.97e3,  250,       6.4185e23, 3.3895e6);
	Planet *oJupiter = new Planet("Jupiter", iRunID, 816.62e9,   12.44e3,  285,       1.8986e27, 69.911e6);
	Planet *oSaturn  = new Planet("Saturn",  iRunID, 1514.50e9,  9.09e3,   0,         5.6846e26, 58.232e6);
	Planet *oUranus  = new Planet("Uranus",  iRunID, 3003.62e9,  6.49e3,   75,        8.6810e25, 25.362e6);
	Planet *oNeptune = new Planet("Neptune", iRunID, 4545.67e9,  5.37e3,   295,       1.0243e26, 24.622e6);
	Planet *oPluto   = new Planet("Pluto",   iRunID, 7375.93e9,  3.71e3,   295,       1.305e22,  1.195e6);
	Planet *oRocket  = new Planet("Rocket",  iRunID, 152.10e9,   29.29e3,  20,        1e5,       50.0);
	//Planet *oCustom1 = new Planet("Custom1", iRunID, 816.62e9,   12.44e3,  285,       1.8986e30, 69.911e6);
	//Planet *oCustom2 = new Planet("Custom2", iRunID, 7375.93e9,  3.71e3,   295,       1.305e22,  1.195e6);

	switch(iSet) {
		case 0: iObjects = 2;  break;
		case 1: iObjects = 3;  break;
		case 2: iObjects = 10; break;
		case 3: iObjects = 4;  break;
		case 4: iObjects = 2;  break;
		case 5: iObjects = 11; break;
		case 6: iObjects = 10; break;
	}

	Planet **aSystem = new Planet*[iObjects];

	switch(iSet) {
		case 0:
			aSystem[0] = oSun;
			aSystem[1] = oEarth;
			break;
		case 1:
			aSystem[0] = oSun;
			aSystem[1] = oEarth;
			aSystem[2] = oMoon;
			break;
		case 2:
			aSystem[0] = oSun;
			aSystem[1] = oMercury;
			aSystem[2] = oVenus;
			aSystem[3] = oEarth;
			aSystem[4] = oMars;
			aSystem[5] = oJupiter;
			aSystem[6] = oSaturn;
			aSystem[7] = oUranus;
			aSystem[8] = oNeptune;
			aSystem[9] = oPluto;
			break;
		case 3:
			cout << "Jupiter mass factor: ";
			cin  >> dTemp;
			aSystem[0] = oSun;
			aSystem[1] = oEarth;
			aSystem[2] = oMars;
			aSystem[3] = oJupiter;
			oJupiter->Mass *= dTemp;
			cout << endl;
			break;
		case 4:
			cout << "Earth velocity factor: ";
			cin  >> dTemp;
			aSystem[0] = oSun;
			aSystem[1] = oEarth;
			oEarth->VX *= dTemp;
			oEarth->VY *= dTemp;
			cout << endl;
			break;
		case 5:
			aSystem[0]  = oSun;
			aSystem[1]  = oMercury;
			aSystem[2]  = oVenus;
			aSystem[3]  = oEarth;
			aSystem[4]  = oMars;
			aSystem[5]  = oJupiter;
			aSystem[6]  = oSaturn;
			aSystem[7]  = oUranus;
			aSystem[8]  = oNeptune;
			aSystem[9]  = oPluto;
			aSystem[10] = oRocket;
			oRocket->VMin += 30e3;
			oRocket->Aphelion += 8e6;
			break;
		case 6:
			cout << "Jupiter mass factor: ";
			cin  >> dTemp;
			aSystem[0] = oSun;
			aSystem[1] = oMercury;
			aSystem[2] = oVenus;
			aSystem[3] = oEarth;
			aSystem[4] = oMars;
			aSystem[5] = oJupiter;
			aSystem[6] = oSaturn;
			aSystem[7] = oUranus;
			aSystem[8] = oNeptune;
			aSystem[9] = oPluto;
			oJupiter->Mass *= dTemp;
			cout << endl;
			break;
	}

	aSystem[0]->InitSystem(aSystem, iObjects, 0);
	for(i=0; i<iObjects; i++) {
		aSystem[i]->Update(aSystem, i, iObjects);
		//aSystem[i]->Output();
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
				if(k%(int(dOutput/(dTStep*dDYr)))==0) {
					aSystem[i]->Sector(aXPos[i], aYPos[i]);
					aSystem[i]->Output();
				}
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
		double dXTemp, dYTemp;

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
				
				dXTemp = aSystem[i]->XPos;
				dYTemp = aSystem[i]->YPos;

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
				if(k%(int(dOutput/(dTStep*dDYr)))==0) {
					aSystem[i]->Sector(dXTemp, dYTemp);
					aSystem[i]->Output();
				}
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
