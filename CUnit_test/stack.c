#include <stdio.h>
#include <stdlib.h>

struct _Stack 
{
	int index;
	int st[250];
};
typedef struct _Stack Stack;

//Cria uma pilha vazia
Stack* create_stack();
//coloca um item na pilha
void push(Stack *stack, int item);
//tira o item da pilha
int pop(Stack *stack);
//da uma olhada no primeiro item da pilha
int peek(Stack *stack);
// verifica se a pilha está vazia
int is_empty(Stack *stack);

int is_empty(Stack *stack)
{
	return(stack != NULL && stack->index >= 0);
}

Stack* create_stack()
{
	Stack *newStack = (*Stack) malloc(sizeof(Stack));
	newStack->index = -1;
	return newStack;
}
void push(Stack *stack, int item)
{
	stack->st[++stack->index] = item;
	return;
}
