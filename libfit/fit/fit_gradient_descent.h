////////////////////////////////////////
// Ata Karakci
// November 14, 2010
// ENGN2912B
//
// This file contains the specifications of fit_gradient_descent class
////////////////////////////////////////

#ifndef fit_gradient_descent_h_
#define fit_gradient_descent_h_

#include <vcl_iosfwd.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_vector_fixed.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_nonlinear_minimizer.h>

class vnl_least_squares_function;

class fit_gradient_descent : public vnl_nonlinear_minimizer
{
 public:

  //: Initialize with the function object that is to be minimized.
  fit_gradient_descent(vnl_least_squares_function& f) { init(&f); }

  ~fit_gradient_descent();

  bool minimize(vnl_vector<double>& x);
	
  bool minimize(vnl_vector_fixed<double,2>& x) { vnl_vector<double> y=x.extract(2); bool b=minimize(y); x=y; return b; }
  bool minimize(vnl_vector_fixed<double,3>& x) { vnl_vector<double> y=x.extract(3); bool b=minimize(y); x=y; return b; }
  bool minimize(vnl_vector_fixed<double,4>& x) { vnl_vector<double> y=x.extract(4); bool b=minimize(y); x=y; return b; }
	
 protected:

  vnl_least_squares_function* f_;

  void init(vnl_least_squares_function* f);

};

//: Find minimum of "f", starting at "initial_estimate", and return.
vnl_vector<double> fit_gradient_descent_minimize(vnl_least_squares_function& f,
                                                    vnl_vector<double> const& initial_estimate);


#endif // fit_gradient_descent_h_
