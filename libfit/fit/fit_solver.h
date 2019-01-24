////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_solver class
////////////////////////////////////////

#ifndef fit_solver_h_
#define fit_solver_h_

#include <string>
#include <fit/fit_function.h>

using namespace std;

class fit_solver
{
public:

	fit_solver(){}
	~fit_solver(){}
	virtual string type() =0;
	virtual string name() = 0;
	virtual bool solve(fit_function* fn, vnl_vector<double>& x) = 0;
	virtual bool retry(unsigned& n_iter, double& xtol, double& ftol){return true;}
	virtual string outcome(bool& b) = 0;
	
};



#endif // fit_solver_h_
