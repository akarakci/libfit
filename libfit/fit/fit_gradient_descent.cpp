////////////////////////////////////////
// Ata Karakci
// November 14, 2010
// ENGN2912B
//
// This file contains the implementations of fit_gradient_descent class
////////////////////////////////////////

#include "fit_gradient_descent.h"

#include <iostream>
#include <math.h>
#include <vnl/vnl_fastops.h>
#include <vnl/vnl_vector_ref.h>
#include <vnl/vnl_matrix_ref.h>
#include <vnl/vnl_least_squares_function.h>
using namespace std;

// see header
vnl_vector<double> fit_gradient_descent_minimize(vnl_least_squares_function& f,
                                                    vnl_vector<double> const& initial_estimate)
{
  vnl_vector<double> x = initial_estimate;
  fit_gradient_descent gd(f);
  gd.minimize(x);
  return x;
}

// ctor
void fit_gradient_descent::init(vnl_least_squares_function* f)
{
  f_ = f;

  xtol = 1e-8;           // Termination tolerance on X (solution vector)
  maxfev = 4000 * f->get_number_of_unknowns(); // Termination maximum number of iterations.
  ftol = xtol * 0.01;    // Termination tolerance on F (sum of squared residuals)
  gtol = 1e-5;           // Termination tolerance on Grad(F)' * F = 0
  epsfcn = xtol * 0.001; // Step length for FD Jacobian
}

fit_gradient_descent::~fit_gradient_descent()
{
}

bool fit_gradient_descent::minimize(vnl_vector<double>& x)
{
	double lambda = 0.004; //step size is arbitrarily set to a constant
	double tolx=10, tolf=10, maxg=0; //initial values for termination conditions
	unsigned int m = f_->get_number_of_residuals(); // I  Number of residuals, must be > #unknowns
	unsigned int n = f_->get_number_of_unknowns();  // I  Number of unknowns
	vnl_matrix<double> J(m,n); //Jacobian to be
	vnl_vector<double> fx(m), fs(m); //exit and start values of residues
	
	f_->f(x,fs);		//set residues
	f_->gradf(x, J);	//set Jacobian

	cout << "Initial Jacobian and residuals vector:"<< endl;
	cout << "J \n" << J << endl;
	cout << "residuals "<< fs << endl;
	
	unsigned i=0;
	do{
		vnl_vector<double> xold = x;
		f_->f(x,fx);	//set residues
		f_->gradf(x, J);	//set Jacobian
		
		vnl_vector<double> desc = (J.transpose())*fx;

		x -= lambda*desc; // change in variables x -> x - lambda.J'fx
	
		tolx = (x-xold).magnitude(); //terminate if tolx < xtol
		
		tolf = fx.magnitude();  //terminate if tolf < ftol
	
		for (unsigned k=0; k<desc.size(); ++k)
		{
		if(desc[k]>=maxg)
			maxg = desc[k];  //maximum of dot product of ith row of J.transpose and fx
		}
		++i;
	}while(i<maxfev && tolx>xtol && tolf>ftol && maxg>gtol);
	
	cout << "Final Jacobian and residuals vector:"<< endl;
	cout << "J \n" << J << endl;
	cout << "residuals "<< fx << endl;
	
	cout << "fit_gradient_descent: "<< i <<" iterations. "<< endl;
	cout << "RMS error start/end "<< fs.magnitude()/sqrt(m) <<"/"<<fx.magnitude()/sqrt(m)<<endl;
		
	return true;
}

