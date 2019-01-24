########################################
# Ata Karakci
# November 28, 2010
# ENGN2912B
#
########################################

# This is libfit/fit/CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

SET(fit_sources fit_amoeba_solver.h fit_factory.cpp fit_factory.h fit_function.cpp fit_function.h fit_gauss_init_function.h fit_gaussian.cpp fit_gaussian.h fit_least_squares_function.h fit_least_squares_init_function.h fit_levenberg_marquardt.h fit_linear_solver.h fit_lm_solver.h fit_non_linear_solver.h fit_radial_basis_function.cpp fit_radial_basis_function.h fit_solver.h fit_svd_solver.h fit_tanh_init_function.h fit_tanh.cpp fit_tanh.h)

ADD_LIBRARY(fit ${fit_sources})
TARGET_LINK_LIBRARIES(fit vnl_algo vnl)

IF( BUILD_TESTING )
  SUBDIRS(tests)
ENDIF( BUILD_TESTING )
