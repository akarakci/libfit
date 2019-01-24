////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of tanh_least_squares_fn and fit_tanh class
////////////////////////////////////////

#ifndef fit_tanh_h_
#define fit_tanh_h_


#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <fit/fit_least_squares_function.h>
#include <fit/fit_function.h>
#include <fit/fit_tanh_init_function.h>

class fit_tanh_init_function;

class tanh_least_squares_fn : public fit_least_squares_function
{
public:
  //: Constructor
	tanh_least_squares_fn(){}
	tanh_least_squares_fn(vnl_vector<double> const& xi, 
								 vnl_vector<double> const& y) : fit_least_squares_function(3, xi, y) {} 
  //: Destructor
	~tanh_least_squares_fn() {}

  //: The main function.
  //  Given the parameter vector x, compute the vector of residuals fx.
  //  fx has been sized appropriately before the call.
  void f(vnl_vector<double> const& params, vnl_vector<double>& residuals);

  void gradf(vnl_vector<double> const& params, vnl_matrix<double>& jacobian);

	
};


class fit_tanh : public fit_function
{
public:
	
	fit_tanh(vnl_vector<double> const& xi, vnl_vector<double> const& y) : fit_function(xi,y)
	{
		this->lsqf_ = new tanh_least_squares_fn;
		this->lsif_ = new fit_tanh_init_function;
		
		tanh_least_squares_fn th(xi,y);
		fit_tanh_init_function ftif(xi,y);

		*(this->lsqf_) = th;
		*(this->lsif_) = ftif;
	}
		
	~fit_tanh()
	{
		delete this->lsqf_;
		delete this->lsif_;
	}
	
	double g(double& x);

};

#endif // fit_tanh_h_
