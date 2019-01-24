////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_cost_function and fit_amoeba_solver classes
////////////////////////////////////////

#ifndef fit_amoeba_solver_h_
#define fit_amoeba_solver_h_

#include <fit/fit_non_linear_solver.h>
#include <fit/fit_least_squares_function.h>
#include <fit/fit_function.h>
#include <vnl/vnl_cost_function.h>
#include <vnl/algo/vnl_amoeba.h>
#include <iostream>
using namespace std;

class fit_cost_function : public vnl_cost_function
{
public:
	fit_cost_function(fit_least_squares_function& f) : vnl_cost_function(f.get_number_of_unknowns()),
										f_(&f), fx_(vnl_vector<double>(f.get_number_of_residuals())){}

	~fit_cost_function(){}
	
	double f(vnl_vector<double> const& x)
	{
		f_->f(x, fx_);
		double c = fx_.squared_magnitude();
		cout << "c "<< c << endl;
		return c;
	}
	
protected:
	
	vnl_least_squares_function* f_;
	vnl_vector<double> fx_;
};
		
class fit_amoeba_solver : public fit_non_linear_solver
{
public:

	virtual string name() {return "vnl_ameoba";}
	bool solve(fit_function* fn, vnl_vector<double>& x)
	{
		fn->normalize();
		
		fit_least_squares_function* lf = fn->lsqf();
		fit_least_squares_init_function* lfi = fn->lsif();
		
		lfi->init(x);
		
		fit_cost_function fcf(*lf);
		vnl_amoeba amoeba(fcf);
		
		amoeba.set_relative_diameter(1.0);
		amoeba.verbose = true;
		
		amoeba.set_x_tolerance(xtol_);
		amoeba.set_f_tolerance(ftol_);
		amoeba.set_max_iterations(50);
		
		amoeba.minimize(x);
		
		return true;
	}	
};



#endif // fit_amoeba_solver_h_
