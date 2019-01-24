////////////////////////////////////////
// Ata Karakci
// November 14, 2010
// ENGN2912B
//
// This file contains the specifications of fit_gauss_init_function class
////////////////////////////////////////

#ifndef fit_gauss_init_function_h_
#define fit_gauss_init_function_h_

#include <vnl/vnl_vector.h>
#include "fit_least_squares_init_function.h"
#include <iostream>


class fit_gauss_init_function : public fit_least_squares_init_function
{
public:
	fit_gauss_init_function(){}
	
	fit_gauss_init_function(vnl_vector<double> const& xi, vnl_vector<double> const& y) :
														fit_least_squares_init_function(3, xi, y) {}
	
	~fit_gauss_init_function(){}
		
//same as implemented in fit_gauss.cpp
	void init(vnl_vector<double>& x)
	{
		double mean = 0, xsq = 0, ymax = -vnl_numeric_traits<double>::maxval;
		unsigned m = (this->xi_).size();
		for(unsigned i = 0; i<m ; ++i)
		{
			double xm = (this->xi_)[i];
			mean += xm;
			xsq += xm*xm;
			if((this->y_)[i]>ymax) ymax = (this->y_)[i];
		}
		mean/=m;
		double var = xsq - m*mean*mean;
		x[0] = ymax; // maximum of data y
		x[1] = mean; // mean of xi
		x[2] = sqrt(var/m); // st. dev. of xi
		
		std::cout << "Initial parameters: "<< x << std::endl;
	}
	
};

	
#endif // fit_gauss_init_function_h_
