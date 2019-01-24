////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_least_squares_function class
////////////////////////////////////////

#ifndef fit_least_squares_function_h_
#define fit_least_squares_function_h_

#include <vnl/vnl_vector.h>
#include <vcl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_least_squares_function.h>
#include <string>

class fit_least_squares_function : public vnl_least_squares_function
{
public:
	fit_least_squares_function() : 
	vnl_least_squares_function(0, 0, vnl_least_squares_function::use_gradient){}

	fit_least_squares_function(unsigned const& n, vnl_vector<double> const& xi,
													 vnl_vector<double> const& y) : 
	vnl_least_squares_function(n, xi.size(), vnl_least_squares_function::use_gradient),
	xi_norm(xi), y_norm(y), n_(n) {} 
	
	virtual ~fit_least_squares_function(){}
	
	virtual void f (vnl_vector<double> const& x, vnl_vector<double>& fx)=0;
	virtual void gradf (vnl_vector<double> const& x, vnl_matrix<double>& jacobian)=0;
	double param_size() {return n_;}
	double data_size() {return xi_norm.size();}
	
protected:
	
	vnl_vector<double> xi_norm;
	vnl_vector<double> y_norm;	
	unsigned n_;
};

	
#endif // fit_least_squares_function_h_
