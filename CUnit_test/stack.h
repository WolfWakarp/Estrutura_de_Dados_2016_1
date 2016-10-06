#include <stdio.h>
#include <stdlib.h>
/* Estrutura de dados pilha com array Autor Carlos Pinheiro */

struct _Stack 
{
	int index;
	int st[250];
};
typedef struct _Stack Stack;

//Cria uma pilha vazia com no maximo 250 itens
Stack* create_stack();
//coloca um item na pilha
void push(Stack *stack, int item);
//tira o item da pilha se vazia returna -987984
int pop(Stack *stack);
//da uma olhada no primeiro item da pilha se vazia returna -987984
int peek(Stack *stack);
// verifica se a pilha está vazia
int is_empty(Stack *stack);

int is_empty(Stack *stack)
{
	return(stack == NULL || stack->index < 0);
}

Stack* create_stack()
{
	Stack *newStack = (Stack*) malloc(sizeof(Stack));
	newStack->index = -1;
	return newStack;
}
void push(Stack *stack, int item)
{
	if(stack->index == 249)
	{
		printf("It's full,sorry\n");
		return;
	}	
	stack->st[++stack->index] = item;
	return;
}

int peek(Stack *stack)
{
	if(!is_empty(stack)) return stack->st[stack->index];
	else
	{
		printf("está vazia\n");
		return -1;
	}
}
int pop(Stack *stack)
{
	if(!is_empty(stack)) return stack->st[stack->index--];
	else
	{
		printf("está vazia\n");
		return -987984;
	}
}