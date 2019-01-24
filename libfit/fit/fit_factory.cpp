////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the implementations of fit_factory class
////////////////////////////////////////

#include <fit/fit_factory.h>
#include <fit/fit_svd_solver.h>
#include <fit/fit_lm_solver.h>
#include <fit/fit_amoeba_solver.h>
#include <fit/fit_tanh.h>
#include <fit/fit_gaussian.h>
#include <fit/fit_radial_basis_function.h>

using namespace std;

bool fit_factory::register_solver(fit_solver* fs)
{
	fs_ = fs;
	if(fs->name() == "vnl_ameoba")
		return true;
	else
		return false;
}

bool fit_factory::register_function(fit_function* ff)
{
	ff_ = ff;
	return true;
}
	
bool fit_factory::fit(vnl_vector<double> const& xi, vnl_vector<double> const& y,
										string const& fn, vnl_vector<double>& x)
{
	bool b = false;
	
	if(fn == "radial basis")
	{
		fit_radial_basis_function rbf(xi, y, 3);
		fit_svd_solver fss;
				
		b = fss.solve(&rbf, x);
		
		vnl_vector<double> chi(3);
		double beta;
		rbf.params(chi, beta);
		
		cout << "chi = "<< chi << endl;
		cout << "beta = "<< beta << endl;
		cout << fss.outcome(b) << endl;
	}
	else if(fn == "tanh")
	{
		fit_tanh th(xi, y);
		
		// use register_solver to choose between amoeba and l-m solvers:
		bool bo = fit_factory::register_solver(fs_);
		if(bo)
		{
			fit_amoeba_solver flm;
			b = flm.solve(&th, x);
			cout << flm.outcome(b) << endl;
		}	
		else
		{
			fit_lm_solver flm;
			b = flm.solve(&th, x);
			cout << flm.outcome(b) << endl;
		}
	}
	else if(fn == "gaussian")
	{
		fit_gaussian gs(xi, y);
		
		bool bo = fit_factory::register_solver(fs_);
		if(bo)
		{
			fit_amoeba_solver flm;
			b = flm.solve(&gs, x);
			cout << flm.outcome(b) << endl;
		}	
		else
		{
			fit_lm_solver flm;
			b = flm.solve(&gs, x);
			cout << flm.outcome(b) << endl;
		}
	}
	else
		cout << "not a valid fit type" << endl;
			
	return b;
}

