#include <stdio.h>

void exch(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int array[], int size){
    for(int i=1; i<size; i++){ // i 从 1 开始插入
        int temp = array[i], idx = i; // 记录当前元素和下标
        
        // 当 idx > 0 即 idx - 1 合法时且 当前元素小于前一个元素
        // 不断后移直到 temp 找到了合适的位置
        while(idx > 0 && temp < array[idx-1]){
            array[idx] = array[idx-1]; // 整体后移一位
            idx--;
        }
        
        // 插入元素
        array[idx] = temp;
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
    
    insertion_sort(array, size);
    prt_array(array, size);

    return 0;
}
