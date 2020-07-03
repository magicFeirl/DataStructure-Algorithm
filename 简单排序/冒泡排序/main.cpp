#include <stdio.h>

void exch(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int array[], int size){
    for(int i=0; i<size; i++){
        for(int j=i; j<size-1; j++){
            if(array[j] > array[j+1]){
                exch(&array[j], &array[j+1]);
            }
        }
    }
}

void prt_array(int array[], int size){
    for(int i=0; i<size; i++){
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main(){
    int array[] = {1, 3, 4, 0, 2, -1},
    size = sizeof(array) / sizeof(array[0]);

    bubble_sort(array, size);
    prt_array(array, size);

    return 0;
}
