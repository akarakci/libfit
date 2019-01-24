////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of gaussian_least_squares_fn and fit_gaussian class
////////////////////////////////////////

#include <cmath>
#include <iostream>
#include "fit_gaussian.h"
#include "fit_levenberg_marquardt.h"
#include <iostream>
using namespace std;

static double gauss(double alpha, double mu, double sigma, double x)
{
	double arg = (x-mu)/sigma;
	return alpha*exp(-arg*arg/2);
}

void gaussian_least_squares_fn::f(vnl_vector<double> const& gauss_params,
                               vnl_vector<double>& residuals)
{
	double alpha = gauss_params[0];
	double mu = gauss_params[1];
	double sigma = gauss_params[2];
	
	for(unsigned i = 0; i<residuals.size(); ++i)
		residuals[i] = (this->y_norm)[i]-gauss(alpha, mu, sigma, (this->xi_norm)[i]);
	cout << "gauss params " << gauss_params << endl;
	cout << "residuals "  << residuals << endl << endl;
}

void gaussian_least_squares_fn::gradf(vnl_vector<double> const& gauss_params,
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
		double d = (this->xi_norm)[r]-mu;
		jacobian[r][0]=-gauss(1.0,mu,sigma,(this->xi_norm)[r]);
		jacobian[r][1]=-gauss(alpha,mu,sigma,(this->xi_norm)[r])*d*sigma_2;
		jacobian[r][2]=-gauss(alpha,mu,sigma,(this->xi_norm)[r])*d*d*sigma_3;
    }
	cout << "J \n " << jacobian << endl << endl;
}

double fit_gaussian::g(double& x)
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




