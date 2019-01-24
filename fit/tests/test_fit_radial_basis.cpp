////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the implementation of test_fit_radial_basis()
////////////////////////////////////////

#include <testlib/testlib_test.h>
#include <fit/fit_radial_basis_function.h>
#include <iostream>
using namespace std;

static void test_fit_radial_basis()
{
  vnl_vector<double> xi(6), y(6);
  xi[0]=0; xi[1]=-5; xi[2]=10; xi[3]=5; xi[4]=20; xi[5]=-10;
  y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
  y[5]=0.561348;
	
	cout <<"xi = "<< xi <<", y = "<< y << endl;

	fit_radial_basis_function rbf(xi, y, 3);
	
	vnl_matrix<double> V(3,3);
	
	V = rbf.S();
	
	cout <<"S = \n"<< V << endl;
	
	rbf.normalize();
				
	vnl_matrix<double> M(3,3);
	
	M = rbf.S();
	
	cout <<"S_norm = \n"<< M << endl;
	
	double beta;
	vnl_vector<double> chi(3);
	rbf.params(chi, beta);
	
	cout << "chi = "<< chi <<", beta = "<< beta << endl;
}

TESTMAIN(test_fit_radial_basis);
