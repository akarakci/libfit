////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_radial_basis_function class
////////////////////////////////////////

#ifndef fit_radial_basis_function_h_
#define fit_radial_basis_function_h_

#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <fit/fit_function.h>

class fit_radial_basis_function : public fit_function
{
public:
	
	fit_radial_basis_function(vnl_vector<double> const& xi, vnl_vector<double> const& y,
							  unsigned const& n) : fit_function(xi, y), n_(n){}
		
	vnl_matrix<double> S();
	void params(vnl_vector<double>& chi, double& beta);
	double g(double& x);

private:

	unsigned n_;
};



#endif // fit_radial_basis_function_h_
