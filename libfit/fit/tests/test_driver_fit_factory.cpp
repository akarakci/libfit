////////////////////////////////////////
// Ata Karakci
// November 28, 2010
// ENGN2912B
//
// This file contains registration of test_fit_factory
////////////////////////////////////////

#include <testlib/testlib_register.h>


DECLARE(test_fit_factory_linear);
DECLARE(test_fit_lm_gauss);
DECLARE(test_fit_amoeba_gauss);
DECLARE(test_fit_lm_tanh);
DECLARE(test_fit_amoeba_tanh);

void
register_tests()
{
	REGISTER(test_fit_factory_linear);
	REGISTER(test_fit_lm_gauss);
	REGISTER(test_fit_amoeba_gauss);
	REGISTER(test_fit_lm_tanh);
	REGISTER(test_fit_amoeba_tanh);
}

DEFINE_MAIN;