////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of tanh_least_squares_fn and fit_tanh class
////////////////////////////////////////

#include <cmath>
#include <iostream>
#include "fit_tanh.h"
#include "fit_levenberg_marquardt.h"
#include <iostream>
using namespace std;


void tanh_least_squares_fn::f(vnl_vector<double> const& params, vnl_vector<double>& residuals)
{
  double alpha = params[0];
  double mu = params[1];
  double beta = params[2];
  for(unsigned i = 0; i<residuals.size(); ++i)
      residuals[i] = (this->y_norm)[i] - alpha*tanh((this->xi_norm)[i] - mu) - beta;
  cout << "parameters " << params << endl;
  cout << "residuals "  << residuals << endl << endl;
}

void tanh_least_squares_fn::gradf(vnl_vector<double> const& params,
                                   vnl_matrix<double>& jacobian)
{
  unsigned m = jacobian.rows();
  double alpha = params[0];
  double mu = params[1];
  for(unsigned r = 0; r<m; ++r)
    {
      double d = (this->xi_norm)[r]-mu;
      jacobian[r][0]=-tanh((this->xi_norm)[r] - mu);
      jacobian[r][1]=alpha*(1-tanh(d)*tanh(d));
      jacobian[r][2]=-1;
    }
  cout << "J \n " << jacobian << endl << endl;
}


double fit_tanh::g(double& x)
{
	double mu_y=0, ysq=0;
	unsigned m = (this->y_).size();
	for(unsigned i=0; i<m; ++i)
	{
		double y = (this->y_)[i];
		mu_y += y;
		ysq += y*y;
	}
	mu_y/=m; ysq/=m;
	double sd_y = sqrt(ysq - mu_y*mu_y);
	
	return sd_y*x + mu_y;
}

