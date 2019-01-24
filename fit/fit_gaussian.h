////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of gaussian_least_squares_fn and fit_gaussian_init_function
////////////////////////////////////////

#ifndef fit_gaussian_h_
#define fit_gaussian_h_


#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include "fit_least_squares_function.h"
#include "fit_function.h"
#include "fit_gauss_init_function.h"

class fit_gauss_init_function;

class gaussian_least_squares_fn : public fit_least_squares_function
{
public:
	//: Constructor
	gaussian_least_squares_fn(){}
	gaussian_least_squares_fn(vnl_vector<double> const& xi,
						   vnl_vector<double> const& y) : fit_least_squares_function(3, xi, y){}  
	//: Destructor
	~gaussian_least_squares_fn() {}

	//: The main function.
	//  Given the parameter vector x, compute the vector of residuals fx.
	//  fx has been sized appropriately before the call.
	void f(vnl_vector<double> const& gauss_params, vnl_vector<double>& residuals);

	void gradf(vnl_vector<double> const& gauss_params, vnl_matrix<double>& jacobian);
	
};


class fit_gaussian : public fit_function
{
public:
	
	fit_gaussian(vnl_vector<double> const& xi, vnl_vector<double> const& y) : fit_function(xi,y)
	{
		this->lsqf_ = new gaussian_least_squares_fn;
		this->lsif_ = new fit_gauss_init_function;
		
		gaussian_least_squares_fn gs(xi,y);
		fit_gauss_init_function fgsi(xi,y);

		*(this->lsqf_) = gs;
		*(this->lsif_) = fgsi;
	}
		
	~fit_gaussian()
	{
		delete this->lsqf_;
		delete this->lsif_;
	}
		
	double g(double& x);

};



#endif // fit_gaussian_h_
