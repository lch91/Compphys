#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

main(){
	int n = 200;
	mat A(n,n);
	double h = 4.4/(n+1);
	int i;
	int j;
	vec rho(n);
	for(i=0; i < n; i++){
		rho(i) = (i+1)*h;
		for(j=0; j < n; j++){
			if(j == i-1){
				A(i,j) = -1./pow(h,2);}
			else if(j == i+1 and j < n){
				A(i,j) = -1./pow(h,2);}
			else if(j == i){
				A(i,j) = 2./pow(h,2) + pow(rho(i),2);}
			}
		}
			
cx_vec eigval;
cx_mat eigvec;
eig_gen(eigval,eigvec, A);
for(i=0; i<n; i++){
	cout << eigval(i) << endl;}
	}
