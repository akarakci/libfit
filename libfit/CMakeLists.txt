########################################
# Ata Karakci
# November 28, 2010
# ENGN2912B
#
########################################

# This is libfit/CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

PROJECT(libfit)

FIND_PACKAGE(VXL)

IF(VXL_FOUND)
  # include the standard VXL stuff
  SET(VXL_PROVIDE_STANDARD_OPTIONS 1)
  INCLUDE(${VXL_CMAKE_DIR}/UseVXL.cmake)
  INCLUDE_DIRECTORIES(${karakci_SOURCE_DIR})

  SUBDIRS(fit)

ENDIF(VXL_FOUND)

