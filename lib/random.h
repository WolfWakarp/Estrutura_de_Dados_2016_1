#include <time.h>

int random_number(int min, int max);
void random_arr_numbers(int arr[], int size, int min, int max);

int random_number(int min, int max){
	return min + rand()%max;
}

void random_arr_numbers(int arr[], int size, int min, int max){
	int i;

	for(i = 0; i < size; i++){
		arr[i] = random_number(min, max);
	}

}
