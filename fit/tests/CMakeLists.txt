########################################
# Ata Karakci
#
########################################

# This is libfit/fit/tests/CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

ADD_EXECUTABLE( test_fit_gauss
  # Driver source and utilities
  test_driver_gauss.cpp

  # The tests
  test_fit_gauss.cpp)

ADD_EXECUTABLE( test_fit_tanh
  # Driver source and utilities
  test_driver_tanh.cpp

  # The tests
  test_fit_tanh.cpp)

ADD_EXECUTABLE( test_fit_radial_basis
  # Driver source and utilities
  test_driver_radial_basis.cpp

  # The tests
  test_fit_radial_basis.cpp)

ADD_EXECUTABLE( test_lm_solver
  # Driver source and utilities
  test_driver_lm.cpp

  # The tests
  test_lm_solver.cpp)

ADD_EXECUTABLE( test_amoeba_solver
  # Driver source and utilities
  test_driver_amoeba.cpp

  # The tests
  test_amoeba_solver.cpp)

ADD_EXECUTABLE( test_svd_solver
  # Driver source and utilities
  test_driver_svd.cpp

  # The tests
  test_svd_solver.cpp)

ADD_EXECUTABLE( test_fit_factory
  # Driver source and utilities
  test_driver_fit_factory.cpp

  # The tests
  test_fit_factory_linear.cpp
  test_fit_lm_gauss.cpp
  test_fit_amoeba_gauss.cpp
  test_fit_lm_tanh.cpp
  test_fit_amoeba_tanh.cpp)

TARGET_LINK_LIBRARIES(test_fit_gauss fit vnl vul testlib)
TARGET_LINK_LIBRARIES(test_fit_tanh fit vnl vul testlib)
TARGET_LINK_LIBRARIES(test_fit_radial_basis fit vnl vul testlib)
TARGET_LINK_LIBRARIES(test_lm_solver fit vnl vul testlib)
TARGET_LINK_LIBRARIES(test_amoeba_solver fit vnl vul testlib)
TARGET_LINK_LIBRARIES(test_svd_solver fit vnl_algo vnl vul testlib)
TARGET_LINK_LIBRARIES(test_fit_factory fit vnl_algo vnl vul testlib)


ADD_TEST (test_fit_gauss test_amoeba_solver test_fit_radial_basis test_fit_tanh test_svd_solver test_lm_solver test_fit_factory)
