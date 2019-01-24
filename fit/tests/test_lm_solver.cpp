////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the implementation of test_lm_solver()
////////////////////////////////////////

#include <testlib/testlib_test.h>
#include <fit/fit_lm_solver.h>
#include <fit/fit_gaussian.h>
#include <iostream>
using namespace std;

static void test_lm_solver()
{
	vnl_vector<double> xi(6), y(6), x(3);
	xi[0]=0; xi[1]=-5; xi[2]=10; xi[3]=5; xi[4]=20; xi[5]=-10;
	y[0]=9.23116; y[1]=3.75311; y[2]= 2.78037; y[3]=8.3527; y[4]=0.0153381;
	y[5]=0.561348;
	
	cout <<"xi = "<< xi <<", y = "<< y << endl;

	fit_gaussian gs(xi, y);
				
	fit_lm_solver flm;
	
	bool b = flm.solve(&gs, x);
	
	string s = flm.outcome(b);
	
	cout << s << endl;	
}

TESTMAIN(test_lm_solver);