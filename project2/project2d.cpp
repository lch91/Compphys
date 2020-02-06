#include <iostream>
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

main(){
	int n = 100;
	mat A(n,n);
	double h = 5.0/(n+1);
	int i;
	int j;
	double omega = 0.01;
	vec rho(n);
	for(i=0; i < n; i++){
		rho(i) = (i+1)*h;
		for(j=0; j < n; j++){
			if(j == i-1){
				A(i,j) = -1./pow(h,2);}
			else if(j == i+1 and j < n){
				A(i,j) = -1./pow(h,2);}
			else if(j == i){
				A(i,j) = 2./pow(h,2) + pow(omega,2)*pow(rho(i),2);}// + 1./rho(i);}
			}
		}
		
	vec eigval;
	mat eigvec;
	eig_sym(eigval,eigvec, A);
	ofstream myfile;
	myfile.open ("project2exc1w001up.txt");
	
	for(i=0; i<n; i++){
		myfile << eigvec(i,1) << endl;}
		
	myfile.close();
	ofstream myfile1;
	myfile1.open ("project2exc2w001up.txt");
	
	for(i=0; i<n; i++){
		myfile1 << eigvec(i,2) << endl;}
		
	myfile1.close();
}	
