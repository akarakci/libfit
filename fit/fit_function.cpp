////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the implementation of fit_function::normalize()
////////////////////////////////////////

#include "fit_function.h"
#include <cmath>
#include <iostream>
using namespace std;

void fit_function::normalize()
{
	//find mean and st. dev. of data:
	double mu_x=0, mu_y=0, xsq=0, ysq=0;
	unsigned m = this->xi_.size();
	for(unsigned i=0; i<m; ++i)
	{
		double x = this->xi_[i], y = this->y_[i];
		mu_x += x; mu_y += y;
		xsq += x*x; ysq += y*y;
	}
	mu_x/=m; mu_y/=m; xsq/=m; ysq/=m;
	double sd_x = sqrt(xsq - mu_x*mu_x);
	double sd_y = sqrt(ysq - mu_y*mu_y);
	
	//normalize:
	for(unsigned i=0; i<m; ++i)
	{
		this->xi_[i] = (this->xi_[i]-mu_x)/sd_x;
		this->y_[i] = (this->y_[i]-mu_y)/sd_y;
	}	
	
	cout <<"xi_norm = "<< xi_ << endl;
	cout <<"y_norm = "<< y_ << endl;
}

