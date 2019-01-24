////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_tanh_init_function class
////////////////////////////////////////

#ifndef fit_tanh_init_function_h_
#define fit_tanh_init_function_h_

#include <vnl/vnl_vector.h>
#include <fit/fit_least_squares_init_function.h>
#include <iostream>


class fit_tanh_init_function : public fit_least_squares_init_function
{
public:
	fit_tanh_init_function(){}
	
	fit_tanh_init_function(vnl_vector<double> const& xi, vnl_vector<double> const& y) :
													fit_least_squares_init_function(3, xi, y) {}
	
	~fit_tanh_init_function(){}
		
	void init(vnl_vector<double>& x)
	{
		double meanx = 0, meany = 0, ymin = vnl_numeric_traits<double>::maxval, ymax=-ymin;
		unsigned m = (this->xi_).size();
		for(unsigned i = 0; i<m ; ++i)
		{
			double xm = (this->xi_)[i];
			meanx += xm;
			double ym = (this->y_)[i];
			meany += ym;
			if(y_[i]>ymax) ymax = (this->y_)[i];
			if(y_[i]<ymin) ymin = (this->y_)[i];
		}
		meanx/=m;
		meany/=m;

		x[0] = (ymax-ymin)/2; //half way between ymax and ymin
		x[1] = meanx;  //anti-symmetric about x = xmean
		x[2] = meany;  //also anti-symmetric about y = ymean
		
		std::cout << "Initial parameters: "<< x << std::endl;
	}

	
};

	
#endif // fit_tanh_init_function_h_
