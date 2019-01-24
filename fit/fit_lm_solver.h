////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_lm_solver class
////////////////////////////////////////

#ifndef fit_lm_solver_h_
#define fit_lm_solver_h_

#include <fit/fit_non_linear_solver.h>
#include <fit/fit_levenberg_marquardt.h>
#include <iostream>

using namespace std;

class fit_lm_solver : public fit_non_linear_solver
{
public:

	virtual string name() {return "vnl_levenberg_marquardt";}
	
	bool solve(fit_function* fn, vnl_vector<double>& x)
	{
		fn->normalize();
		
		fit_least_squares_function* lf = fn->lsqf();
		fit_least_squares_init_function* lfi = fn->lsif();
		
		double n = lf->param_size();
		double k = lf->data_size();
				
		vnl_vector<double> ty(n);
		lfi->init(ty);
		
		fit_levenberg_marquardt levmarq(*lf);
		levmarq.set_verbose(true);
		
		// Set the x-tolerance.  When the length of the steps taken in X (variables)
		// are no longer than this, the minimization terminates.
		levmarq.set_x_tolerance(xtol_);
		
		// Set the epsilon-function.  This is the step length for FD Jacobian.
		levmarq.set_epsilon_function(1);
		
		// Set the f-tolerance.  When the successive RMS errors are less than this,
		// minimization terminates.
		levmarq.set_f_tolerance(ftol_);
		
		// Set the maximum number of iterations
		levmarq.set_max_function_evals(n_iter_);		
		
		vnl_vector<double> params(n), residuals(k);
		
		// Minimize the error and get the best intersection point
		levmarq.minimize(params, *lfi);
		
		x = params;
		
		levmarq.diagnose_outcome();
		
		lf->f(params, residuals);
		
		double norm, mag = residuals.magnitude();
		norm = mag*mag;
		
		cout << "eps = "<< norm << endl;
		
		if(norm>ftol_)
			return false;
		else 
			return true;
	}
				
};



#endif // fit_lm_solver_h_
