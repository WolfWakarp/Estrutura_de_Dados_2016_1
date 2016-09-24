#Todos os seus .c
OBJS	=	encodingTree.c	\
		main.c		\
		priorityQueue.c	\
		reader.c	\
		rep_table.c

#Todos os seus .h
DEPS	=	encodingTree.h	\
		priorityQueue.h	\
		reader.h	\
		rep_table.h

#Seu compilador
CC	=	gcc

#Suas flags
COMPILER_FLAGS	=	-w	\
		       	-std=c11

#Nome do seu executavel
OBJ_NAME	=	Huffman

#Todos os alvos marcados para a compilação
all : $(OBJS)
	$(CC) $(OBJS) $(DEPS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
