////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_non_linear_solver class
////////////////////////////////////////

#ifndef fit_non_linear_solver_h_
#define fit_non_linear_solver_h_

#include <fit/fit_solver.h>

class fit_non_linear_solver : public fit_solver
{
public:

	fit_non_linear_solver() : n_iter_(2000), xtol_(1e-8), ftol_(1e-10) {}
	
	virtual string type() {return "non_linear";}
	
	bool retry(unsigned& n_iter, double& xtol, double& ftol)
	{
		this->n_iter_ = n_iter;
		this->xtol_ = xtol;
		this->ftol_ = ftol;
		
		return true;
	}
		
	string outcome(bool& b)
	{
		if(b)
			return "The solver converged";
		else
			return "The solver failed to converge - exceeded iterations or no improvement";
	}
	
protected:
	
	unsigned n_iter_;
	double xtol_;
	double ftol_;
	
};



#endif // fit_non_linear_solver_h_
