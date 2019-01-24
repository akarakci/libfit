
  Ata Karakci

---------------------------------------------------------------------------
Included Files:
	readme.txt
	directory: libfit
		CMakelists.txt
		directory: fit
			CMakelists.txt
			fit_gauss.h
		 	fit_gauss.cpp
			fit_gradient_descent.h
			fit_gradient_descent.cpp
			fit_rosenbrock.h
			fit_levenberg_marquardt.h
			fit_least_squares_init_function.h
			fit_gauss_init_function.h
			fit_amoeba_solver.h
			fit_factory.cpp 
			fit_factory.h
			fit_function.cpp
			fit_function.h 
			fit_gauss_init_function.h 
			fit_gaussian.cpp 
			fit_gaussian.h 
			fit_least_squares_function.h 						
			fit_least_squares_init_function.h 					
			fit_linear_solver.h 
			fit_lm_solver.h 
			fit_non_linear_solver.h 
			fit_radial_basis_function.cpp 
			fit_radial_basis_function.h 
			fit_solver.h 
			fit_svd_solver.h 
			fit_tanh_init_function.h 
			fit_tanh.cpp 
			fit_tanh.h
			directory: tests
				CMakelists.txt
				test_driver_gauss.cpp
				test_fit_gauss.cpp
				test_driver_tanh.cpp
				test_fit_tanh.cpp 	
				test_driver_radial_basis.cpp
			 	test_fit_radial_basis.cpp 
				test_driver_lm.cpp
				test_lm_solver.cpp
				test_driver_amoeba.cpp
				test_amoeba_solver.cpp 
				test_driver_svd.cpp 
				test_svd_solver.cpp
				test_driver_fit_factory.cpp
				test_fit_factory_linear.cpp
				test_fit_lm_gauss.cpp
				test_fit_amoeba_gauss.cpp
				test_fit_lm_tanh.cpp
				test_fit_amoeba_tanh.cpp

---------------------------------------------------------------------------


1) fit_least_squares_function class is implemented as an abstract class in order to take advantage of polymorphism.  tanh_least_squares_fn class for

g(x) = a*tanh(x-b) + c

is implement with parameter vector (a,b,c). The Jacobian is constructed.

---------------------------------------------------------------------------

2) fit_tanh_init_function class is implemented. The range of tanh function is c-a < y < c+a, => a_init = (ymax - ymin)/2. Since the function is anti-symmetric about x = b axis b_init = mean_x and it is also anti-symmetric about y = c axis so c_init = mean_y.

---------------------------------------------------------------------------

3) The fit_function base class is implemented as an abstract class in order to take advantage of polymorphism. A virtual method for S() matrix is implemented to be used for radial_basis_functon.

---------------------------------------------------------------------------

4) The fit_radial_basis_functon class is implemented with an unsigned integer member corresponding to the number of weight functions. The function

g(x) = sum(i) w[i]*exp(-b*(x - ch[i])^2) i=1,2,..,n

since the domain is divided into n equal parts ch vector is chosen to be 
 
ch[i] = xmin + i*(xmax-xmin)/n

b = 1.5*(xmax-xmin)/n

A function params(vnl_vector ch, double b) is implemented to obtain ch and b.

To find the parameter vector w[i] , the S matrix is implemented as follows:

For each linear element of the function write:

(f_k)[i] = exp(-b*(x[k] - ch[i])^2) 

f[i][j] = < (f_k)[i]*(f_k)[j] > 

where < > means sum over all k's and divide by n. The S matrix is thus;

S =
     f[0][0]  f[0][1]  …  f[0][n-1]     < y[k]*(f_k)[0] >
      
     f[1][0]  f[1][1]  …  f[1][n-1]     < y[k]*(f_k)[1] >

	.   	.     		.		.
	.	.		.		.
	.	.		.		.

    f[n-1][0]  f[n-1][1] …  f[n-1][n-1]  <y[k]*(f_k)[n-1] >

   <y[k]*(f_k)[0]>  … … … <y[k]*(f_k)[n-1]>    <y[k]*y[k]>

The method g(x) is implemented so that the function fit by normalized data g'(x') is transformed back to g(x):

g(g'(x')) = st.dev_y*g'(x') + mean_y

---------------------------------------------------------------------------

5) The fit_tanh class is implemented by initializing the members of the base class by allocating them on the heap as pointers to tanh_least_squares_fn and fit_tanh_init_function respectively. Then the destructor deletes them.

A test case for fit_tanh is implemented in test_fit_tanh.cpp. An instance of the class is created from a data set. The data is normalized. The functions which returns to the members of the base class are called. From the pointer to fit_least_squares_init_function init methods called to initialize the parameter vector. Parameters, residuals and the jacobian is obtained by fit_least_squares_function::f and fit_least_squares_function::gradf. 
---------------------------------------------------------------------------

6) The fit_gaussian class is implemented by initializing the members of the base class by allocating them on the heap as pointers to gauss_least_squares_fn and fit_gauss_init_function respectively. Then the destructor deletes them.

A test case for fit_gaussian is implemented in test_fit_gauss.cpp a similar way as test_fit_tanh.cpp.

---------------------------------------------------------------------------

7) The fit_solver base class is implemented as an abstract class with all of its methods being purely virtual.

---------------------------------------------------------------------------

8) The fit_linear_solver base class is implemented as a subclass of fit_solver with type() method returning the string "linear". Since it's other methods inherited from fit_solver are still purely virtual fit_linear_solver is also an abstract class.

---------------------------------------------------------------------------

9) The fit_non_linear_solver base class is implemented as a subclass of fit_solver with type() method returning the string "non_linear". It's members are initialized to default values. The retry method sets the values of the members. outcome method is implemented to return the success or failure message. Since it's name() methods inherited from fit_solver is still purely virtual fit_non_linear_solver is also an abstract class.

---------------------------------------------------------------------------

10) The fit_svd_solver class is implemented as a subclass of fit_linear_solver with name() method returning "vnl_svd". The solve method uses vnl_svd to obtain the parameters by passing the pointer to a fit_function. If fit fails (resulting eps vector has a magnitude greater than a specified value) than solve() method returns false, and outcome method prints failure message. 

A test case for fit_svd_solver is implemented in test_svd_solver.cpp in a similar way as before.

---------------------------------------------------------------------------

11) The fit_lm_solver class is implemented as a subclass of fit_non_linear_solver with name() method returning "vnl_levenberg_marquardt". The solve method passes the pointer to a fit_function which is used to call fit_least_squares_function and fit_least_squares_init_function by using lsqf() and lsif() method of the fit_function. fit_levenberg_marquardt is used for minimization to obtain the parameters. If fit fails (resulting eps vector has a magnitude greater than a specified value) than solve() method returns false, and outcome method prints failure message. 

A test case for fit_lm_solver is implemented in test_svd_solver.cpp in a similar way as before.

---------------------------------------------------------------------------

12) The fit_amoeba_solver class is implemented as a subclass of fit_non_linear_solver with name() method returning "vnl_amoeba". The solve method passes the pointer to a fit_function which is used to call fit_least_squares_function and fit_least_squares_init_function by using lsqf() and lsif() method of the fit_function. fit_cost_fuction passes lsqf_  to be used to create vnl_amoeba instanse which is used for minimization to obtain the parameters. If fit fails (resulting eps vector has a magnitude greater than a specified value) than solve() method returns false, and outcome method prints failure message. 

A test case for fit_lm_solver is implemented in test_svd_solver.cpp in a similar way as before.

---------------------------------------------------------------------------

13) fit_factory class is implemented with members fit_solver* and fit_function*

register_fuction method passes a pointer to a fit_function and initializes fit_factory member. 

register_solver passes a pointer to a fit_solver and initializes fit_factory member. It ales checks if the name() method of the fit_solver return "vnl_amoeba" or not to be used later.

---------------------------------------------------------------------------

14) The fit() method of fit_factory is implemented as follows:

the input string can be "radial basis", "tanh" or "gaussian" otherwise method returns the message "not a valid fit type"

for "radial basis" fit_radial_basis_function instance is created and solve() method of fit_svd_solver is used.

for "tanh" fit_tanh instance is created and if register_solver returns the name "vnl_amoeba" minimization is obtain by creating an instance of fit_amoeba_solver, otherwise minimization is obtained by creating an instance of fit_lm_solver.

similar procedure follows for "gaussian" in which case an instance of fit_gaussian is created first.

---------------------------------------------------------------------------

14) The test case for fit_factory is implemented for linear case in test_fit_factory_linear.cpp, for gaussian fit by levenberg_marquardt in test_fit_lm_gauss.cpp, for gaussian fit by amoeba in test_fit_amoeba_gauss.cpp, for tanh by levenberg_marquardt in test_fit_lm_tanh.cpp, and finally for tanh by amoeba in test_fit_amoeba_tanh.cpp. All 5 tests passes successfully except levenberg_marquardt fitting of tanh failed to converge.

