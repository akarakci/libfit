////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_linear_solver class
////////////////////////////////////////

#ifndef fit_linear_solver_h_
#define fit_linear_solver_h_

#include <fit/fit_solver.h>


class fit_linear_solver : public fit_solver
{
public:
	
	virtual string type() {return "linear";}
	
};



#endif // fit_linear_solver_h_
