#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
void stack_test() 
{
	Stack *stack;
	stack = create_stack();
  // Check if first param matches with second[2]
	push(stack, 1);
	push(stack, 2);
	push(stack, 3);
	push(stack, 4);
  CU_ASSERT_EQUAL(peek(stack), 4);
  CU_ASSERT_EQUAL(pop(stack), 3); // teste que vai dar errado
  CU_ASSERT_EQUAL(pop(stack), 3);
  CU_ASSERT_EQUAL(pop(stack), 2);
}
int main()
{
	//iniciar o CUnit é necessário sempre iniciar antes de qualquer coisa com o CUnit
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL; // criando um suite para guardar o tipo de teste.
	pSuite = CU_add_suite("stack_test_suite", 0, 0); //adicionando o suite.
	if (NULL == pSuite) { //essa chave é para o victor :D
		// isso aqui está testando se o suite foi adicionado/criado corretamente
 		 CU_cleanup_registry(); /*Só para falar logo isso aqui é para terminar o Cunit, como ja diz pagar 
 		 os registros.*/
  		return CU_get_error();
	}
	// Add the test to the suite
	if (NULL == CU_add_test(pSuite, "stack_test", stack_test)) 
	{
  		CU_cleanup_registry();
  		return CU_get_error();
	}
	//setar os modos básicos de operação CU_BRM_VERBOSE é para mostrar o máximo de detalhes da execução
	CU_basic_set_mode(CU_BRM_VERBOSE); 
	// roda os testes e mostra os detalhes da exercução
   	CU_basic_run_tests();
   return CU_get_error();
}