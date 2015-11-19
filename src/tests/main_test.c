/**
 \file TP3.c
 \brief  Ruzzle
 \author Baptiste et Maxime
 \version 7.0.0
 \date 28 octobre 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/dico.h"
#include "../../include/grille.h"
#include "../../include/struct.h"
#include "./CUnitLocal/include/CUnit/Basic.h"
#include "./CUnitLocal/include/CUnit/CUnit.h"

void test_grille(void){
	CU_ASSERT_EQUAL(2, 2);
}

/**
 \fn int main();
 \brief programme principal
 */
int main(){

CU_pSuite pSuite = NULL;

if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
pSuite = CU_add_suite("Suite_1", 0, 0);
if (!pSuite) { CU_cleanup_registry();
return CU_get_error(); }

if (!CU_add_test(pSuite, "test of fprintf()", test_grille))
{   CU_cleanup_registry();
return CU_get_error();
}
CU_basic_run_tests();
CU_cleanup_registry();
return CU_get_error();
}
