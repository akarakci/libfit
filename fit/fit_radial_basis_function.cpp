////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains the specifications of fit_radial_basis_function class
////////////////////////////////////////

#include "fit_radial_basis_function.h"
#include <iostream>

double radial_basis(vnl_vector<double>& w, vnl_vector<double>& chi, double& beta, double& x)
{
	unsigned n = chi.size();
	double rb = 0;
	for(unsigned i=0; i<n; ++i)
		rb += w[i]*exp(-beta*(x-chi[i])*(x-chi[i]));
	
	return rb;
}		

vnl_matrix<double> fit_radial_basis_function::S()
{
	unsigned n = this->n_;
	double xmin = this->xi_[0], xmax=this->xi_[0];
	
	for(unsigned i=1; i<this->xi_.size(); ++i)
	{
		if(this->xi_[i]<xmin)
			xmin = this->xi_[i];
		
		if(this->xi_[i]>xmax) 
			xmax = this->xi_[i];
	}
	
	//divide the data interval in equal parts:
	double ch = (xmax-xmin)/n, beta = 1.5*ch;
	
	vnl_matrix<double> S_(n+1,n+1);
	
	unsigned sz = this->xi_.size();
	
	unsigned r=0;
	while(r<sz){
		double yr = this->y_[r];
		S_[n][n] += yr*yr;
		++r;}
	
	for(unsigned i=0; i<n; ++i)
	{
		for(unsigned j=0; j<n; ++j)
		{
			double sij=0;

			unsigned k=0;
			while(k<sz){
				double ki = this->xi_[k] - xmin - i*ch;
				double kj = this->xi_[k] - xmin - j*ch;
				sij += exp(-beta*(ki*ki+kj*kj));
				++k;}
			
			S_[i][j] = sij;
		}
		unsigned l=0;
		while(l<sz){
			double li = this->xi_[l] - xmin - i*ch;
			S_[i][n] -= this->y_[l]*exp(-beta*li*li);
			++l;}
		
		S_[n][i] = S_[i][n];
	}
	return S_/n;
}

void fit_radial_basis_function::params(vnl_vector<double>& chi, double& beta)
{
	unsigned n = this->n_;
	double xmin = this->xi_[0], xmax=this->xi_[0];
	
	for(unsigned i=1; i<this->xi_.size(); ++i)
	{
		if(this->xi_[i]<xmin)
			xmin = this->xi_[i];
		
		if(this->xi_[i]>xmax) 
			xmax = this->xi_[i];
	}
	
	chi.fill(xmin);
	
	double ch = (xmax-xmin)/n;
	
	for(unsigned i=0; i<n; ++i)
		chi[i] += i*ch;
	
	beta = 1.5*ch;
}

double fit_radial_basis_function::g(double& x)
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

