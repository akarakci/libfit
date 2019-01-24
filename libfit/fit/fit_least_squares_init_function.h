////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_least_squares_init_function class
////////////////////////////////////////

#ifndef fit_least_squares_init_function_h_
#define fit_least_squares_init_function_h_

#include <vnl/vnl_vector.h>

class fit_least_squares_init_function
{
public:
	fit_least_squares_init_function(){}
	
	fit_least_squares_init_function(unsigned const& n,
									vnl_vector<double> const& xi,
									vnl_vector<double> const& y) : n_(n), xi_(xi), y_(y) {}
	
	virtual ~fit_least_squares_init_function(){}
	
	virtual void init(vnl_vector<double>& x)=0;
	
protected:
	
	unsigned n_;
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
};

	
#endif // fit_least_squares_init_function_h_
