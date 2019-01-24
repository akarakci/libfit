////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_factory class
////////////////////////////////////////

#ifndef fit_factory_h_
#define fit_factory_h_

#include <string>
#include <fit/fit_function.h>
#include <fit/fit_solver.h>
#include <vnl/vnl_vector.h>

using namespace std;

class fit_factory
{
public:
	
	fit_factory(){}
	~fit_factory(){}
	bool register_solver(fit_solver* fs);
	bool register_function(fit_function* ff);
	bool fit(vnl_vector<double> const& xi, vnl_vector<double> const& y,
			 string const& fn, vnl_vector<double>& x);

private:
	
	fit_solver* fs_;
	fit_function* ff_;
};



#endif // fit_factory_h_