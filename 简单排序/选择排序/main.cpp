#include <stdio.h>

void exch(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �� [i+1, N] ��ѡ��һ����С��Ԫ�أ����� i �� k
// ������ [0, i] �ڵ�Ԫ�ؾ���������ˣ��ظ� N �μ��������
void selection_sort(int array[], int size){
    for(int i=0; i<size; i++){
        int k = i;
        
        for(int j=i+1; j<size; j++){
            if(array[j] < array[k]){
                k = j;
            }
        }
        
        exch(&array[i], &array[k]);
    }
}

// �����Ŀ�����ϰ�������Լ�������Щϸ������
void quick_sort(int array[], int l, int r){
    if(l >= r){
        return ;
    }
    
    int x = array[l], li = l - 1, ri = r + 1;
    while(li < ri){
        do li++; while(li < ri && array[li] < x);
        do ri--; while(li < ri && array[ri] > x);
        
        if(li < ri){
            exch(&array[li], &array[ri]);
        }
        
    }
    
    quick_sort(array, l, ri);
    quick_sort(array, ri+1, r);
}

void prt_array(int array[], int size){
    for(int i=0; i<size; i++){
        printf("%d ", array[i]);
    }
    
    printf("\n");
}

int main(){
    int array[] = {1, 3, 4, 0, 2, -1}, size = sizeof(array) / sizeof(array[0]);
    quick_sort(array, 0, size);
    prt_array(array, size);
    
    return 0;
}
