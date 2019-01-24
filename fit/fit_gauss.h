#ifndef fit_gauss_h_
#define fit_gauss_h_
//:
// \file
// \brief Fit a 1-d Gaussian to a set of points y(xi)
// \author J. L. Mundy
// \date July 29, 2007
//

#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_least_squares_function.h>
using namespace std;
class gauss_least_squares_fn : public vnl_least_squares_function
{
 public:
  //: Constructor
  gauss_least_squares_fn(vnl_vector<double> const& xi,
                         vnl_vector<double> const& y) : 
    //    vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::no_gradient), xi_(xi), y_(y){}  
vnl_least_squares_function(3, xi.size(),vnl_least_squares_function::use_gradient), xi_(xi), y_(y){}  
  //: Destructor
  ~gauss_least_squares_fn() {}

  //: The main function.
  //  Given the parameter vector x, compute the vector of residuals fx.
  //  fx has been sized appropriately before the call.
  virtual void f(vnl_vector<double> const& gauss_params,
                 vnl_vector<double>& residuals);

  virtual void gradf(vnl_vector<double> const& gauss_params,
                     vnl_matrix<double>& jacobian);
 protected:
  vnl_vector<double> xi_;
  vnl_vector<double> y_;
};


class fit_gauss
{
 public:

  static bool fit(vnl_vector<double> const& xi,
                  vnl_vector<double> const& y,
                  double& alpha, double& mu, double& sigma);

// new fitting function for gradient descent method:
  static bool fit_gd(vnl_vector<double> const& xi,
				  vnl_vector<double> const& y,
				  double& alpha, double& mu, double& sigma);
};



#endif // fit_gauss_h_
