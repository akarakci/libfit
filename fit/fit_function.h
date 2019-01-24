////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_function class
////////////////////////////////////////

#ifndef fit_function_h_
#define fit_function_h_

#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <fit/fit_least_squares_function.h>
#include <fit/fit_least_squares_init_function.h>


class fit_function
{
public:
	fit_function(){}

	fit_function (vnl_vector<double> const& xi, vnl_vector<double> const& y) : xi_(xi), y_(y) {}
	
	virtual ~fit_function(){}
	
	virtual void normalize();
	//pure virtual method:
	virtual double g(double& x)= 0;
	
	fit_least_squares_function* lsqf(){return lsqf_;}
	fit_least_squares_init_function* lsif(){return lsif_;}
	
	// S-matrix to be used for svd fitting:
	virtual vnl_matrix<double> S()
	{
		vnl_matrix<double> M(1,1,0.);
		return M;
	}
	
protected:
	
	vnl_vector<double> xi_;
	vnl_vector<double> y_;
	fit_least_squares_function* lsqf_;
	fit_least_squares_init_function* lsif_;
};



#endif // fit_function_h
