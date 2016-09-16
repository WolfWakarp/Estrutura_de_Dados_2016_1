#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "lib/tree.h"
#include "CUnit/Basic.h"

bt* bst = NULL;
bt* avl = NULL;

int init_suite_bst_1(void){
	int arr[50] = {75, 447, 1290, 1427, 1954, 2621, 2890, 3034, 3536, 3607, 5123, 5589, 5619, 5647, 5683, 6283, 7034, 7776, 7791, 8798, 9405, 9776, 10355, 11425, 11659, 12045, 12351, 12535, 12825, 12882, 12926, 13329, 13514, 13923, 14419, 14483, 15061, 15486, 15526, 15672, 15746, 16080, 16703, 16912, 17863, 18086, 18110, 19084, 19613, 19957};

	bst = bst_insert_array(bst, arr, 50, 0);
	return 0;
}

int init_suite_avl_1(void){
	int arr[11] = {40, 10, 20, 30, 12, 35, 25, 28, 390, 120, 200};
	avl = bst_insert_array(avl, arr, 11, 1);
	return 0;
}

void test_bst_print(void){

	char s[100000];

	int pos = bst_to_string(bst, s, 0);
	s[pos+1] = '\0';
	CU_ASSERT(strcmp("(75()(447()(1290()(1427()(1954()(2621()(2890()(3034()(3536()(3607()(5123()(5589()(5619()(5647()(5683()(6283()(7034()(7776()(7791()(8798()(9405()(9776()(10355()(11425()(11659()(12045()(12351()(12535()(12825()(12882()(12926()(13329()(13514()(13923()(14419()(14483()(15061()(15486()(15526()(15672()(15746()(16080()(16703()(16912()(17863()(18086()(18110()(19084()(19613()(19957()()))))))))))))))))))))))))))))))))))))))))))))))))))", s) == 0);

}

void test_avl_print(void){

	char s[100000];

	int pos = bst_to_string(avl, s, 0);
	s[pos+1] = '\0';
	CU_ASSERT(strcmp("(35(20(10()(12()()))(28(25()())(30()())))(120(40()())(390(200()())())))", s) == 0);

}

int clean_suite_bst(void){
	bst_free(bst);
	if(bst != NULL) free(bst);
	return 0;
}

int clean_suite_avl(void){
	bst_free(avl);
	if(avl != NULL) free(avl);
	return 0;
}

int main(){
	
	CU_pSuite bst_suite = NULL;
	CU_pSuite avl_suite = NULL;

	/* Inicializando o CUnit registry*/
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Adicionando suite para a BST */
	bst_suite = CU_add_suite("BST_Suite_1", init_suite_bst_1, clean_suite_bst);

	if (NULL == bst_suite) {
    	CU_cleanup_registry();
    	return CU_get_error();
   	}

   	/* Adicionando suite para a AVL */
   	avl_suite = CU_add_suite("AVL_Suite_1", init_suite_avl_1, clean_suite_avl);

   	if (NULL == avl_suite) {
    	CU_cleanup_registry();
    	return CU_get_error();
   	}
   	/* Adicionando os testes */
   	if ((NULL == CU_add_test(bst_suite, "test of bst_to_string()", test_bst_print)) 
   		|| (NULL == CU_add_test(avl_suite, "test of bst_to_string() with avl", test_avl_print)))
   	{
   		CU_cleanup_registry();
  		return CU_get_error();
   	}

   	/* Roda os testes do CUnit */
   	CU_basic_set_mode(CU_BRM_VERBOSE);
   	CU_basic_run_tests();
   	CU_cleanup_registry();

	return CU_get_error();
}
