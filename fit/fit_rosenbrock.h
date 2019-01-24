////////////////////////////////////////
// Ata Karakci
// November 14, 2010
// ENGN2912B
//
// This file contains the specifications of rosenbrock_least_squares_fn class
////////////////////////////////////////

#ifndef fit_rosenbrock_h_
#define fit_rosenbrock_h_

#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_least_squares_function.h>

class fit_rosenbrock : public vnl_least_squares_function
{
public:

	fit_rosenbrock() : vnl_least_squares_function(2, 2, use_gradient) {}
	
	~fit_rosenbrock(){}
	
	void f(vnl_vector<double> const& x, vnl_vector<double>& y)
	{
		y[0] = 10*(x[1] - x[0]*x[0]);
		y[1] = 1 - x[0];
	}

	void gradf(vnl_vector<double> const& x, vnl_matrix<double> &J)
	{
		J[0][0] = -20*x[0]; J[0][1] = 10;
		J[1][0] = -1;		J[1][1] = 0;
	}
};

	
#endif // fit_rosenbrock_h_
