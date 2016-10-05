#include <stdlib.h>
#include <string.h>

typedef struct bt{
	int value;
	struct bt *right;
	struct bt *left;
}bt;

/* Cria a bst */
bt* bst_create(int value);

/* Insere na bst um valor. */
bt* bst_insert(bt* bst, int value, int balance);

/* Insere na bst um array de valores. */
bt* bst_insert_array(bt* bst, int arr[], int size, int balance);

/* Busca um valor na bst e retorna o número de comparações */
int bst_search(bt* bst, int value);

/* Limpa a binary tree */
void bst_free(bt* bst);

/*ve se ela é uma avl, se sim retorna 1, caso não retorna 0*/
int is_it_an_avl(bt *bst);

/* Imprime a bst */
void bst_print(bt* bst);

/* Cria uma arvore vazia*/
bt* create_empty_tree();

/* Retorna se a árvore está vazia */
int bst_is_empty(bt* bst);

/* Compara dois inteiros e verifica o maior */
int max(int a, int b);

/* Altura da arvore */
int bst_height(bt* bst);

/* Fator de balanceamento */
int balance_factor(bt* bst);

/* Rotacionar a arvore */
bt* bst_rotate_left(bt* bst);

/*voce manda uma binaria completa e volta uma avl*/
bt* balance_everything(bt * bst);

bt* bst_rotate_right(bt* bst);

bt* create_empty_tree(){
	return NULL;
}

int bst_is_empty(bt* bst){
	return (bst == NULL);
}

bt* bst_create(int value){
	bt* bst = (bt*)malloc(sizeof(bt));
	bst->value = value;
	bst->left = NULL;
	bst->right = NULL;

	return bst;
}

bt* bst_rotate_left(bt* bst){
	bt* subtree_root = create_empty_tree();
	
	if(!bst_is_empty(bst) && !bst_is_empty(bst->right)){
		subtree_root = bst->right;
		bst->right = subtree_root->left;
		subtree_root->left = bst;
	}

	return subtree_root;	
}

bt* bst_rotate_right(bt* bst){
	bt* subtree_root = create_empty_tree();
	
	if(!bst_is_empty(bst) && !bst_is_empty(bst->left)){
		subtree_root = bst->left;
		bst->left = subtree_root->right;
		subtree_root->right = bst;
	}

	return subtree_root;	
}

bt* bst_balance(bt* bst){
	int bf = balance_factor(bst);
	if(bf == 2){
			if(balance_factor(bst->left) == -1){
				bst->left = bst_rotate_left(bst->left);
			}
			bst = bst_rotate_right(bst);
	}else if(bf == -2){
			if(balance_factor(bst->right) == 1){
				bst->right = bst_rotate_right(bst->right);
			}
			bst = bst_rotate_left(bst);		
	}		
	return bst;
}

bt* bst_insert(bt* bst, int value, int balance){
	if(bst == NULL){
		bst = bst_create(value);
	}else if(bst->value > value){
		bst->left = bst_insert(bst->left, value, balance);
		//não necessário                                    ////mudança
		if(balance){
			bst = bst_balance(bst);
		}
	}else{
		bst->right = bst_insert(bst->right, value, balance);
		//não necessário                                    ////mudança
		if(balance){
			bst = bst_balance(bst);
		}
	}
	return bst;
}

bt* bst_insert_array(bt* bst, int arr[], int size, int balance){

	int i;

	for(i = 0; i < size; i++){
		bst = bst_insert(bst, arr[i], balance);
	}

	return bst;
}

int bst_search(bt* bst, int value){

	if(bst == NULL) return 0;
	if(bst->value == value) return 1;
	if(bst->value < value) return ((bst_search(bst->right, value)) + 1);

	return ((bst_search(bst->left, value)) + 1);
}

void bst_free(bt* bst){
	if(bst == NULL){
		bst_free(bst->left);
		bst_free(bst->right);
		free(bst);
	}
}

void bst_print(bt* bst){
	printf("(");
	if(bst != NULL){
		printf("%d", bst->value);
		bst_print(bst->left);
		bst_print(bst->right);
	}
	printf(")");
}

int bst_to_string(bt* bst, char* s, int pos){
	s[pos] = '(';
	if(bst != NULL){
		char aux[100];
		snprintf(aux, sizeof(aux), "%d", bst->value);
		int i;
		for(i = 0; i < strlen(aux); i++){
			pos++;
			s[pos] = aux[i];
		}
		pos = bst_to_string(bst->left, s, pos+1);
		pos = bst_to_string(bst->right, s, pos+1);
	}
	s[pos+1] = ')';
	return pos+1;
}

int max(int a, int b){
	return ((a > b) ? a : b);
}

int bst_height(bt* bst){
	if(bst_is_empty(bst)){
		return -1;	
	}else{
		return 1 + max(bst_height(bst->left), bst_height(bst->right));	
	}
}

int balance_factor(bt* bst){
	if(bst == NULL) return 0; //mudança para caso seja null.
	else return bst_height(bst->left) - bst_height(bst->right);
}