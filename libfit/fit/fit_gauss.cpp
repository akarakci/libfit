#include <cmath>
#include <iostream>
#include "fit_gauss.h"
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <fit/fit_gradient_descent.h>


static double gauss(double alpha, double mu, double sigma, double x)
{
  double arg = (x-mu)/sigma;
  return alpha*exp(-arg*arg/2);
}


void gauss_least_squares_fn::f(vnl_vector<double> const& gauss_params,
                               vnl_vector<double>& residuals)
{
  double alpha = gauss_params[0];
  double mu = gauss_params[1];
  double sigma = gauss_params[2];
  for(unsigned i = 0; i<residuals.size(); ++i)
      residuals[i] = y_[i]-gauss(alpha, mu, sigma, xi_[i]);
//  cout << "gauss params " << gauss_params << endl;
//  cout << "residuals "  << residuals << endl << endl;
}

void gauss_least_squares_fn::gradf(vnl_vector<double> const& gauss_params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned m = jacobian.rows();
  double alpha = gauss_params[0];
  double mu = gauss_params[1];
  double sigma = gauss_params[2];
  double sigma_2 = 1/(sigma*sigma);
  double sigma_3 = sigma_2/sigma;
  for(unsigned r = 0; r<m; ++r)
    {
      double d = xi_[r]-mu;
      jacobian[r][0]=-gauss(1.0,mu,sigma,xi_[r]);
      jacobian[r][1]=-gauss(alpha,mu,sigma,xi_[r])*d*sigma_2;
      jacobian[r][2]=-gauss(alpha,mu,sigma,xi_[r])*d*d*sigma_3;
    }
//  cout << "J \n " << jacobian << endl << endl;
}

static  void initial_values(vnl_vector<double> const& xi,
               vnl_vector<double> const& y, vnl_vector<double>& gauss_params)
{
  double mean = 0, xsq = 0, ymax = -vnl_numeric_traits<double>::maxval;
  unsigned m = xi.size();
  for(unsigned i = 0; i<m ; ++i)
    {
      double x = xi[i];
      mean += x;
      xsq += x*x;
      if(y[i]>ymax) ymax = y[i];
    }
  mean/=m;
  double var = xsq - m*mean*mean;
  gauss_params[0] = ymax;
  gauss_params[1] = mean;
  gauss_params[2] = sqrt(var/m);
}

bool fit_gauss::fit(vnl_vector<double> const& xi,
                    vnl_vector<double> const& y,
                    double& alpha, double& mu, double& sigma)
{
    gauss_least_squares_fn glsf(xi, y);
    vnl_levenberg_marquardt levmarq(glsf);
    levmarq.set_verbose(true);

  // Set the x-tolerance.  When the length of the steps taken in X (variables)
  // are no longer than this, the minimization terminates.
  levmarq.set_x_tolerance(1e-10);
 
  // Set the epsilon-function.  This is the step length for FD Jacobian.
  levmarq.set_epsilon_function(1);
 
  // Set the f-tolerance.  When the successive RMS errors are less than this,
  // minimization terminates.
  levmarq.set_f_tolerance(1e-10);
 
  // Set the maximum number of iterations
  levmarq.set_max_function_evals(1000);

  vnl_vector<double> gauss_params(3);

  initial_values(xi, y, gauss_params);

  // Minimize the error and get the best intersection point
  levmarq.minimize(gauss_params);

  levmarq.diagnose_outcome();

  alpha = gauss_params[0];
  mu = gauss_params[1];
  sigma = gauss_params[2];
  return true;

}

bool fit_gauss::fit_gd(vnl_vector<double> const& xi,
				   vnl_vector<double> const& y,
				   double& alpha, double& mu, double& sigma)
{
    gauss_least_squares_fn glsf(xi, y);
    fit_gradient_descent fgd(glsf);
	
	vnl_vector<double> gauss_params(3);
	
	initial_values(xi, y, gauss_params);
	
	// Minimize the error and get the best intersection point
	fgd.minimize(gauss_params);
		
	alpha = gauss_params[0];
	mu = gauss_params[1];
	sigma = gauss_params[2];
	return true;
	
}


