#include <testlib/testlib_test.h>
#include <fit/fit_rosenbrock.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <fit/fit_gradient_descent.h>
#include <iostream>
using namespace std;

static void test_fit_rosenbrock()
{
	fit_rosenbrock f;
	
	vnl_vector<double> x(2);
	x[0]=-1; x[1]=2;
	
	cout << "By Gradient Descent:" <<endl;
	
	vnl_vector<double> xgd = x;
	cout << "xi = "<< xgd << endl;
	
	fit_gradient_descent gd(f);
	gd.minimize(xgd);
	cout << "xf = " << xgd << endl; 
	
	cout << endl;

	cout << "By Levenberg-Marquardt:" <<endl;

	vnl_vector<double> xlm = x;
	cout << "xi = "<< xlm << endl;
	
	vnl_levenberg_marquardt lm(f);
	lm.minimize(xlm);
	lm.diagnose_outcome(cout);
	cout << "xf = " << xlm << endl; 

}

TESTMAIN(test_fit_rosenbrock);
