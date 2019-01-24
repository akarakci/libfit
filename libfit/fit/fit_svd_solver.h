////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_svd_solver class
////////////////////////////////////////

#ifndef fit_svd_solver_h_
#define fit_svd_solver_h_

#include <fit/fit_linear_solver.h>
#include <vnl/algo/vnl_svd.h>
#include <iostream>

using namespace std;

class fit_svd_solver : public fit_linear_solver
{
public:

	virtual string name() {return "vnl_svd";}
	
	bool solve(fit_function* fn, vnl_vector<double>& x)
	{
		fn->normalize();
		vnl_matrix<double> S = fn->S();
		unsigned n = S.rows();
		
		vnl_svd<double> svd(S);
		vnl_matrix<double> V = svd.V();
		x = V.get_column(n-1);
				
		vnl_vector<double> f = S*x;
		double norm = dot_product(x,f);
		cout << "parameters are "<< x << endl;
		cout << "residuals is " << norm << endl;
				
		svd.zero_out_absolute();
		unsigned r = svd.rank();
		cout << "rank is "<< r << endl;
		
		if(r > n-2 && norm < 0.1)
			return true;
		else
			return false;
	}
		
	string outcome(bool& b)
	{
		if(b)
			return "Linear function is fit by svd";
		else
			return "The solver failed to fit linear function - no unique solution is found";
	}
		   
	
};



#endif // fit_svd_solver_h_
