////////////////////////////////////////
// Ata Karakci
// November 14, 2010
// ENGN2912B
//
// This file contains the specifications of fit_levenberg_marquardt class
////////////////////////////////////////

#ifndef fit_levenberg_marquardt_h_
#define fit_levenberg_marquardt_h_

#include <vnl/vnl_vector.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include "fit_least_squares_init_function.h"

class fit_levenberg_marquardt : public vnl_levenberg_marquardt
{
public:
	
	//ctor
	fit_levenberg_marquardt(vnl_least_squares_function& f) : vnl_levenberg_marquardt(f) {}
	
	~fit_levenberg_marquardt(){}
	
	bool minimize(vnl_vector<double>& x, fit_least_squares_init_function& x0)
	{
		x0.init(x);
		return vnl_levenberg_marquardt::minimize(x);
	}
	
};

	
#endif // fit_levenberg_marquardt_h_
